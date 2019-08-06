#include "sensor_thread.h"
#include "sensor_api.h"
#include "sensor_thread_entry.h"
#include "Ram.h"


#define C_FILTER_ORDER  2


uint16_t u16100msCnt;
uint16_t u16Pulses;
uint16_t  u16PulsesAverage;
uint16_t au16PulsesArray[2];
bool bfMainTickElapsed = false;
int u16TickCnt = C_MAIN_TICK_MS;
timer_size_t counts = 0;

// Prueba ADC
void sensor_thread_entry(void)
{
    g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart(g_adc0.p_ctrl);
    g_timer2.p_api->open (g_timer2.p_ctrl, g_timer2.p_cfg);
    g_timer2.p_api->start (g_timer2.p_ctrl);
    g_timer2.p_api->reset(g_timer2.p_ctrl);
    g_external_irq10.p_api->open(g_external_irq10.p_ctrl,g_external_irq10.p_cfg);
    while (1)
    {
        /******************************************************/
        /*       READ INPUTS                                  */
        /******************************************************/
        g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);
        /******************************************************/
        /*       INSERT CODE HERE                             */
        /******************************************************/

          if(C_FILTER_ORDER > 1)
            {
              u16ADC_Filtered = (u16ADC_Data + (C_FILTER_ORDER - 1) * u16ADC_Filtered) / C_FILTER_ORDER;
            }
          else
            {
              u16ADC_Filtered = u16ADC_Data;
            }
//Parametrización de ADC con PWM
        u16PwmPercent = 100-((100 * u16ADC_Data) / 255);
        FN_bfPerformTick();
        write_message_sensor();
        tx_thread_sleep (1);
    }
}

void button_callback_SW5(external_irq_callback_args_t *p_args)
{
    u16Pulses++;
}

bool FN_bfPerformTick(void)
{
  g_timer2.p_api->counterGet(g_timer2.p_ctrl, &counts);

  if(counts > (COUNTS_PER_MILLISECOND))
    {
      // Reset the timer to 0
      g_timer2.p_api->reset(g_timer2.p_ctrl);

      u16TickCnt++;
      if(u16TickCnt >= C_MAIN_TICK_MS)
        {
          u16TickCnt = 0;
          bfMainTickElapsed = true;
        }

      u16100msCnt++;
      if(u16100msCnt >= 100)
          {
               u16100msCnt = 0;
               au16PulsesArray[0] = au16PulsesArray[1];
               au16PulsesArray[1] = u16Pulses;
               u16Pulses = 0;
               u16PulsesAverage = (au16PulsesArray[0] + au16PulsesArray[1])/2;
          }
    }

  return bfMainTickElapsed;
}



void write_message_sensor(){
    errorBuffSensor = g_sf_message0.p_api->bufferAcquire (g_sf_message0.p_ctrl, &pPostBufferSensor,
                                                          &acquireCfgSensor, TX_WAIT_FOREVER);
    if (errorBuffSensor == SSP_SUCCESS)
    {
        pDataPayloadSensor = (sensor_payload_t *) pPostBufferSensor; //cast buffer to our payload
        pDataPayloadSensor->header.event_b.class = SF_MESSAGE_EVENT_CLASS_ADC; //set the event class
        pDataPayloadSensor->header.event_b.class_instance = 0; //set the class instance
        pDataPayloadSensor->header.event_b.code = SF_MESSAGE_EVENT_ADC; //set the message type
        g_sf_message0.p_api->post (g_sf_message0.p_ctrl, (sf_message_header_t *) pDataPayloadSensor,
                                   &post_cfgSensor, &errPostSensor, TX_WAIT_FOREVER); //post the message
    }
}

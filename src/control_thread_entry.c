#include "control_thread.h"
#include "control_api.h"
#include "speed_api.h"
#include "control_thread_entry.h"
#include "Ram.h"



void control_thread_entry(void)
{
    /* TODO: add your own code here */

    g_timer1.p_api->open (g_timer1.p_ctrl, g_timer1.p_cfg);
    g_timer1.p_api->start (g_timer1.p_ctrl);

    while (1)
    {
        /******************************************************/
        /*       READ INPUTS                                  */
        /******************************************************/
          read_message_control();
        /******************************************************/
        /*       INSERT CODE HERE                             */
        /******************************************************/


          g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, u16PwmPercent, TIMER_PWM_UNIT_PERCENT, 1);

          write_message_control();
          tx_thread_sleep (1);
    }
}

/* Control Thread entry function */
void write_message_control(){
    errorBuffControl = g_sf_message0.p_api->bufferAcquire (g_sf_message0.p_ctrl, &pPostBufferControl,
                                                           &acquireCfgControl, TX_NO_WAIT);
    if (errorBuffControl == SSP_SUCCESS)
    {
        pDataPayloadControl = (speed_payload_t *) pPostBufferControl; //cast buffer to our payload
        pDataPayloadControl->header.event_b.class = SF_MESSAGE_EVENT_CLASS_PWM; //set the event class
        pDataPayloadControl->header.event_b.class_instance = 1; //set the class instance
        pDataPayloadControl->header.event_b.code = SF_MESSAGE_EVENT_PWM; //set the message type
        g_sf_message0.p_api->post (g_sf_message0.p_ctrl, (sf_message_header_t *) pDataPayloadControl,
                                   &post_cfgControl, &errPostControl, TX_NO_WAIT); //post the message
    }
}

void read_message_control(){
    g_sf_message0.p_api->pend (g_sf_message0.p_ctrl, &control_thread_message_queue, &pSensorDataHeader, TX_NO_WAIT); //if a message has been posted to the queue, store its address in pSensorDataHeader

    if (pSensorDataHeader->event_b.class_code == SF_MESSAGE_EVENT_CLASS_CONTROL) //if the message is the right kind
    {
        pSensorDataPayload = (control_payload_t *) pSensorDataHeader; //cast the received message to the custom type
        //store the sensor information in some buffers, this part is application dependent
        if (pSensorDataPayload->header.event_b.code == SF_MESSAGE_EVENT_NEW_DATA) //if the message event is the right kind
        {
            activate_flag = pSensorDataPayload->activate;
            speed_value = pSensorDataPayload->set_point;
            feedback_value=pSensorDataPayload->feedback;
            g_sf_message0.p_api->bufferRelease (g_sf_message0.p_ctrl, pSensorDataHeader,
                                                SF_MESSAGE_RELEASE_OPTION_NONE);
        }
    }
}

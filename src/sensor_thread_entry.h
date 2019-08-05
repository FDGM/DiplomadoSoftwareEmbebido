/*
 * sensor_thread_entry.h
 *
 *  Created on: 11/03/2019
 *      Author: uriel
 */

#ifndef SENSOR_THREAD_ENTRY_H_
#define SENSOR_THREAD_ENTRY_H_

    //Message init
          //sending sensordata init
          sf_message_header_t * pPostBufferSensor; //pointer for the buffer that must be acquired
          sf_message_acquire_cfg_t acquireCfgSensor = {.buffer_keep =false}; //do not keep the buffer, other threads need it
          ssp_err_t errorBuffSensor; //place for error codes from buffer acquisition to go
          sf_message_post_err_t errPostSensor; //place for posting error codes to go
          sf_message_post_cfg_t post_cfgSensor =
          {
            .priority = SF_MESSAGE_PRIORITY_NORMAL, //normal priority
            .p_callback = NULL //no callback needed
          };
          sensor_payload_t * pDataPayloadSensor; //pointer to the receiving message payload
          void write_message_sensor();

#define C_MAIN_TICK_MS  10
#define COUNTS_PER_MILLISECOND  (120E6 / 1000)
extern bool FN_bfPerformTick(void);
#endif /* SENSOR_THREAD_ENTRY_H_ */

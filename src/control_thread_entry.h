/*
 * control_thread_entry.h
 *
 *  Created on: 11/03/2019
 *      Author: uriel
 */

#ifndef CONTROL_THREAD_ENTRY_H_
#define CONTROL_THREAD_ENTRY_H_

timer_size_t u8DutyCycle;
ioport_level_t led_0_level = IOPORT_LEVEL_HIGH;
int P_MOD4 = 1;
static int speed_value=0;
static bool activate_flag=false;
int feedback_value=0;

sf_message_header_t * pSensorDataHeader; //pointer to the message header
control_payload_t * pSensorDataPayload; //pointer to the message payload
//Message init
      //sending sensordata init

      sf_message_header_t * pPostBufferControl; //pointer for the buffer that must be acquired
      sf_message_acquire_cfg_t acquireCfgControl = {.buffer_keep =false}; //do not keep the buffer, other threads need it
      ssp_err_t errorBuffControl; //place for error codes from buffer acquisition to go
      sf_message_post_err_t errPostControl; //place for posting error codes to go
      sf_message_post_cfg_t post_cfgControl =
      {
        .priority = SF_MESSAGE_PRIORITY_NORMAL, //normal priority
        .p_callback = NULL //no callback needed
      };
      speed_payload_t * pDataPayloadControl; //pointer to the receiving message payload
      void write_message_control();
      void read_message_control();
#endif /* CONTROL_THREAD_ENTRY_H_ */

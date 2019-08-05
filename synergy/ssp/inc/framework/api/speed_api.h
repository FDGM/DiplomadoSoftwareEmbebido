/*
 * speed_api.h
 *
 *  Created on: 07/03/2019
 *      Author: uriel
 */

#ifndef SSP_INC_FRAMEWORK_API_SPEED_API_H_
#define SSP_INC_FRAMEWORK_API_SPEED_API_H_

#include "sf_message_api.h" //this is a message, so the message api is needed


typedef struct speed_payload
{
    sf_message_header_t     header;     ///< Required header for messaging framework.
    int                 speed_value;          ///< sensor value.
} speed_payload_t; //This name is specified in "Event Class" properties as "Payload Type"

#endif /* SSP_INC_FRAMEWORK_API_SPEED_API_H_ */

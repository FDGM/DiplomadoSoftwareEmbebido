/*
 * sensor_api.h
 *
 *  Created on: 09/02/2019
 *      Author: uriel
 */

#ifndef SSP_INC_FRAMEWORK_API_SENSOR_API_H_
#define SSP_INC_FRAMEWORK_API_SENSOR_API_H_

#include "sf_message_api.h" //this is a message, so the message api is needed


typedef struct sensor_payload
{
    sf_message_header_t     header;     ///< Required header for messaging framework.
    int                 sensor_value;          ///< sensor value.
} sensor_payload_t; //This name is specified in "Event Class" properties as "Payload Type"

#endif /* SSP_INC_FRAMEWORK_API_SENSOR_API_H_ */


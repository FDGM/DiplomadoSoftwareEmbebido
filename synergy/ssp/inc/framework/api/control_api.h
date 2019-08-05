/*
 * control_api.h
 *
 *  Created on: 03/03/2019
 *      Author: uriel
 */

#ifndef SSP_INC_FRAMEWORK_API_CONTROL_API_H_
#define SSP_INC_FRAMEWORK_API_CONTROL_API_H_

#include "sf_message_api.h" //this is a message, so the message api is needed

typedef struct control_payload
{
    sf_message_header_t     header;     ///< Required header for messaging framework.
    bool                 activate;          ///< sensor value.
    int                     set_point;
    int                     feedback;
} control_payload_t; //This name is specified in "Event Class" properties as "Payload Type"
#endif /* SSP_INC_FRAMEWORK_API_CONTROL_API_H_ */

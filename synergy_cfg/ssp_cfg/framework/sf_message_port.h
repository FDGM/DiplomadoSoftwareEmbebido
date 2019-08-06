/* generated messaging header file - do not edit */
#ifndef SF_MESSAGE_PORT_H_
#define SF_MESSAGE_PORT_H_
typedef enum e_sf_message_event_class
{
    SF_MESSAGE_EVENT_CLASS_TOUCH, /* Touch */
    SF_MESSAGE_EVENT_CLASS_ADC, /* ADC */
    SF_MESSAGE_EVENT_CLASS_CONTROL, /* CONTROL */
    SF_MESSAGE_EVENT_CLASS_PWM, /* PWM */
} sf_message_event_class_t;
typedef enum e_sf_message_event
{
    SF_MESSAGE_EVENT_UNUSED, /* Unused */
    SF_MESSAGE_EVENT_NEW_DATA, /* New Data */
    SF_MESSAGE_EVENT_ADC, /* ADC */
    SF_MESSAGE_EVENT_PWM, /* PWM */
} sf_message_event_t;
extern TX_QUEUE main_thread_message_queue;
extern TX_QUEUE control_thread_message_queue;
#endif /* SF_MESSAGE_PORT_H_ */

/* generated messaging source file - do not edit */
#include "sf_message.h"
#ifndef SF_MESSAGE_CFG_QUEUE_SIZE
#define SF_MESSAGE_CFG_QUEUE_SIZE (16)
#endif
TX_QUEUE main_thread_message_queue;
static uint8_t queue_memory_main_thread_message_queue[SF_MESSAGE_CFG_QUEUE_SIZE];
TX_QUEUE control_thread_message_queue;
static uint8_t queue_memory_control_thread_message_queue[SF_MESSAGE_CFG_QUEUE_SIZE];
static sf_message_subscriber_t main_thread_message_queue_0_1 =
{ .p_queue = &main_thread_message_queue, .instance_range =
{ .start = 0, .end = 1 } };
static sf_message_subscriber_t control_thread_message_queue_2_2 =
{ .p_queue = &control_thread_message_queue, .instance_range =
{ .start = 2, .end = 2 } };
static sf_message_subscriber_t *gp_group_SF_MESSAGE_EVENT_CLASS_TOUCH[] =
{ &main_thread_message_queue_0_1, };
static sf_message_subscriber_list_t g_list_SF_MESSAGE_EVENT_CLASS_TOUCH =
{ .event_class = SF_MESSAGE_EVENT_CLASS_TOUCH, .number_of_nodes = 1, .pp_subscriber_group =
          gp_group_SF_MESSAGE_EVENT_CLASS_TOUCH };
static sf_message_subscriber_t *gp_group_SF_MESSAGE_EVENT_CLASS_SENSOR[] =
{ &main_thread_message_queue_0_1, };
static sf_message_subscriber_list_t g_list_SF_MESSAGE_EVENT_CLASS_SENSOR =
{ .event_class = SF_MESSAGE_EVENT_CLASS_ADC, .number_of_nodes = 1, .pp_subscriber_group =
          gp_group_SF_MESSAGE_EVENT_CLASS_SENSOR };
static sf_message_subscriber_t *gp_group_SF_MESSAGE_EVENT_CLASS_CONTROL[] =
{ &main_thread_message_queue_0_1, &control_thread_message_queue_2_2, };
static sf_message_subscriber_list_t g_list_SF_MESSAGE_EVENT_CLASS_CONTROL =
{ .event_class = SF_MESSAGE_EVENT_CLASS_CONTROL, .number_of_nodes = 2, .pp_subscriber_group =
          gp_group_SF_MESSAGE_EVENT_CLASS_CONTROL };
static sf_message_subscriber_t *gp_group_SF_MESSAGE_EVENT_CLASS_SPEED[] =
{ &main_thread_message_queue_0_1, &control_thread_message_queue_2_2, };
static sf_message_subscriber_list_t g_list_SF_MESSAGE_EVENT_CLASS_SPEED =
{ .event_class = SF_MESSAGE_EVENT_CLASS_PWM, .number_of_nodes = 2, .pp_subscriber_group =
          gp_group_SF_MESSAGE_EVENT_CLASS_SPEED };
sf_message_subscriber_list_t *p_subscriber_lists[] =
{ &g_list_SF_MESSAGE_EVENT_CLASS_TOUCH, &g_list_SF_MESSAGE_EVENT_CLASS_SENSOR, &g_list_SF_MESSAGE_EVENT_CLASS_CONTROL,
  &g_list_SF_MESSAGE_EVENT_CLASS_SPEED, NULL };
void g_message_init(void);
void g_message_init(void)
{
    tx_queue_create (&main_thread_message_queue, (CHAR *) "Main Thread Message Queue", 1,
                     &queue_memory_main_thread_message_queue, sizeof(queue_memory_main_thread_message_queue));
    tx_queue_create (&control_thread_message_queue, (CHAR *) "Control Thread Message Queue", 1,
                     &queue_memory_control_thread_message_queue, sizeof(queue_memory_control_thread_message_queue));
}


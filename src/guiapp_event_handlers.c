#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include "guiapp_event_handlers.h"
#include "main_thread.h"

extern GX_WINDOW_ROOT *p_window_root;

static UINT show_window(GX_WINDOW *p_new, GX_WIDGET *p_widget, bool detach_old);
static void update_numeric(GX_WIDGET *p_widget, GX_RESOURCE_ID id, int numeric);

bool flag_activate = false;

UINT window1_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process (widget, event_ptr);

    switch (event_ptr->gx_event_type)
    {
        case GX_EVENT_PEN_UP:
            show_window ((GX_WINDOW *) &window3, (GX_WIDGET *) widget, true);
        break;
        default:
            result = gx_window_event_process (widget, event_ptr);
        break;
    }
    return result;
}

UINT window2_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process (widget, event_ptr);

    switch (event_ptr->gx_event_type)
    {
        case GX_SIGNAL(BTN_BACK, GX_EVENT_CLICKED):
            show_window ((GX_WINDOW *) &window3, (GX_WIDGET *) widget, true);
        break;
        default:
            result = gx_window_event_process (widget, event_ptr);
        break;
    }
    return result;
}

UINT window3_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process (widget, event_ptr);

    switch (event_ptr->gx_event_type)
    {
        case GX_SIGNAL(BTN_ABOUT, GX_EVENT_CLICKED):
            show_window ((GX_WINDOW *) &window2, (GX_WIDGET *) widget, true);
        break;
        default:
            result = gx_window_event_process (widget, event_ptr);
        break;
    }
    return result;
}

static UINT show_window(GX_WINDOW *p_new, GX_WIDGET *p_widget, bool detach_old)
{
    UINT err = GX_SUCCESS;

    if (!p_new->gx_widget_parent)
    {
        err = gx_widget_attach(p_window_root, p_new);
    }
    else
    {
        err = gx_widget_show(p_new);
    }

    gx_system_focus_claim(p_new);

    GX_WIDGET *p_old = p_widget;
    if (p_old && detach_old)
    {
        if (p_old != (GX_WIDGET *) p_new)
        {
            gx_widget_detach(p_old);
        }
    }

    return err;
}

static void update_numeric(GX_WIDGET *p_widget, GX_RESOURCE_ID id, int numeric)
{
    GX_NUMERIC_PROMPT *p_prompt = NULL;

    ssp_err_t err = gx_widget_find(p_widget, (USHORT )id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET ** )&p_prompt);
    if (TX_SUCCESS == err)
    {
        _gxe_numeric_prompt_value_set (p_prompt, numeric);
    }
}

void update_duty_cycle(int duty_cycle)
{
    update_numeric ((GX_WIDGET *) &window3, PR_DUTY_CYCLE, duty_cycle);
}

void update_speed(int speed)
{
    update_numeric ((GX_WIDGET *) &window3, PR_SPEED, speed);
}

void update_setpoint(int setpoint)
{
    update_numeric ((GX_WIDGET *) &window3, PR_SET_POINT, setpoint);
}



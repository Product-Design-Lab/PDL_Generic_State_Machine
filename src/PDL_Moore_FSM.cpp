#include "PDL_Moore_FSM.h"

PDL_Moore_FSM::PDL_Moore_FSM(const PDL_Moore_FSM::transition_t *transitions, uint8_t num_transitions, PDL_Moore_FSM::state_t initial_state)
    : transitions(transitions), num_transitions(num_transitions), current_state(initial_state)
{
    event_queue = xQueueCreate(10, sizeof(PDL_Moore_FSM::event_t));
}

void PDL_Moore_FSM::init()
{
    xTaskCreate(task, "FSM", 1024, this, 1, &task_handle);
}

void PDL_Moore_FSM::handle_event(PDL_Moore_FSM::event_t event)
{
    xQueueSend(event_queue, &event, portMAX_DELAY);
}

PDL_Moore_FSM::state_t PDL_Moore_FSM::get_current_state() const
{
    return current_state;
}

void PDL_Moore_FSM::task(void *fsm)
{
    static_cast<PDL_Moore_FSM *>(fsm)->task_loop();
}

void PDL_Moore_FSM::task_loop()
{
    event_t event;
    while (1)
    {
        if (xQueueReceive(event_queue, &event, portMAX_DELAY))
        {
            for (uint8_t i = 0; i < num_transitions; i++)
            {
                if (transitions[i].start_state == current_state && transitions[i].event == event)
                {
                    if (transitions[i].action)
                    {
                        transitions[i].action();
                    }
                    current_state = transitions[i].end_state;
                    break;
                }
            }
        }
    }
}

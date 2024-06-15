#pragma once

#include "Arduino.h"
#include "freeRTOS.h"
#include "task.h"
#include "queue.h"

class PDL_Moore_FSM
{
public:
    using state_t = uint8_t;
    using event_t = uint8_t; // equivalent to input
    using action_t = void (*)(void);
    
    typedef struct
    {
        state_t start_state;
        event_t event;
        state_t end_state;
        action_t action;
    } transition_t;

    PDL_Moore_FSM(const transition_t *transitions, uint8_t num_transitions, state_t initial_state);

    // start the FSM task
    void init();

    // event is added to a queue
    void handle_event(event_t event);

    state_t get_current_state() const;

private:
    const transition_t *transitions;
    uint8_t num_transitions;
    state_t current_state;

    QueueHandle_t event_queue;
    TaskHandle_t task_handle;

    static void task(void *fsm);

    void task_loop();

};

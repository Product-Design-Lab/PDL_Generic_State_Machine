#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h> // Include Arduino base library for Serial and other functionalities

// Define state action function type
typedef void (*StateAction_t)();

// Define states
enum State_t {
    STATE_INIT,
    STATE_RUNNING,
    STATE_STOPPED,
    STATE_ERROR,
    STATE_MAX_STATES // For boundary checking
};

// Define events
enum Event_t {
    EVENT_START,
    EVENT_STOP,
    EVENT_ERROR_OCCURED,
    EVENT_RESET,
    EVENT_MAX_EVENTS // For boundary checking
};

// Define the state transition structure
typedef struct {
    State_t currentState;
    Event_t event;
    State_t nextState;
} StateTransition_t;

// Function prototypes for actions
void InitAction();
void RunningAction();
void StoppedAction();
void ErrorAction();

#endif // CONFIG_H

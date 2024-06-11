#ifndef PDL_GENERIC_STATE_MACHINE_H
#define PDL_GENERIC_STATE_MACHINE_H

#include "config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

class StateMachine {
public:
    StateMachine(StateAction_t* actions, StateTransition_t* transitions, int numStates, int numTransitions, uint32_t stackSize, UBaseType_t taskPriority);
    ~StateMachine();

    void sendEvent(Event_t event);
    void registerAction(State_t state, StateAction_t action);
    void registerTransition(const StateTransition_t& transition);

private:
    State_t currentState;
    StateAction_t* actions;
    StateTransition_t* transitions;
    int numStates;
    int numTransitions;
    QueueHandle_t eventQueue;          // Ensure this is declared
    TaskHandle_t stateMachineTask;     // Ensure this is declared

    static void stateMachineTaskFunction(void* params); // Declare as static
    void processEvent(Event_t event);
    int findTransitionIndex(State_t state, Event_t event) const;
};

#endif // PDL_GENERIC_STATE_MACHINE_H

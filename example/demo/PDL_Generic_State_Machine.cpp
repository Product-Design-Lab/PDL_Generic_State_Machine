#include "PDL_Generic_State_Machine.h"

StateMachine::StateMachine(StateAction_t* actions, StateTransition_t* transitions, int numStates, int numTransitions, uint32_t stackSize, UBaseType_t taskPriority) {
    currentState = STATE_INIT;
    this->actions = actions;
    this->transitions = transitions;
    this->numStates = numStates;
    this->numTransitions = numTransitions;
    eventQueue = xQueueCreate(10, sizeof(Event_t));
    xTaskCreate(stateMachineTaskFunction, "StateMachineTask", stackSize, this, taskPriority, &stateMachineTask);
}

StateMachine::~StateMachine() {
    vTaskDelete(stateMachineTask);
    vQueueDelete(eventQueue);
}

void StateMachine::sendEvent(Event_t event) {
    xQueueSend(eventQueue, &event, portMAX_DELAY);
}

void StateMachine::stateMachineTaskFunction(void* params) {
    StateMachine* sm = static_cast<StateMachine*>(params);
    Event_t event;
    while (true) {
        if (xQueueReceive(sm->eventQueue, &event, portMAX_DELAY) == pdPASS) {
            sm->processEvent(event);
        }
    }
}

void StateMachine::processEvent(Event_t event) {
    int transitionIndex = findTransitionIndex(currentState, event);
    if (transitionIndex != -1) { // Check if a valid transition is found
        currentState = transitions[transitionIndex].nextState; // Transition to the next state
        if (actions[currentState]) { // If there's an action associated with the new state, execute it
            actions[currentState](); // Execute the action associated with the state
        }
    }
}

int StateMachine::findTransitionIndex(State_t currentState, Event_t event) const {
    for (int i = 0; i < numTransitions; i++) {
        // Check if the current state and the event match the transition entry
        if (transitions[i].currentState == currentState && transitions[i].event == event) {
            return i; // Return the index of the transition
        }
    }
    return -1; // Return -1 if no transition is found
}


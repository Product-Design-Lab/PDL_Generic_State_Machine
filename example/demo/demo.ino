#include "PDL_Generic_State_Machine.h"
#include <Adafruit_TinyUSB.h> // Include the TinyUSB library for USB Serial

StateAction_t actions[STATE_MAX_STATES] = {InitAction, RunningAction, StoppedAction, ErrorAction};
StateTransition_t transitions[] = {
    {STATE_INIT, EVENT_START, STATE_RUNNING},
    {STATE_RUNNING, EVENT_STOP, STATE_STOPPED},
    {STATE_STOPPED, EVENT_RESET, STATE_INIT},
    {STATE_ERROR, EVENT_RESET, STATE_INIT}
};

StateMachine* sm;

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for the serial port to connect. Necessary for native USB

    sm = new StateMachine(actions, transitions, STATE_MAX_STATES, sizeof(transitions)/sizeof(transitions[0]), 1024, 1);
    sm->sendEvent(EVENT_RESET); // Send initial event if needed
}

void loop() {
    // Check if serial data is available
    if (Serial.available() > 0) {
        int incomingByte = Serial.read(); // Read the incoming byte

        switch(incomingByte) {
            case 's': // Suppose 's' starts the machine
                sm->sendEvent(EVENT_START);
                break;
            case 't': // Suppose 't' stops the machine
                sm->sendEvent(EVENT_STOP);
                break;
            case 'e': // Suppose 'e' triggers an error
                sm->sendEvent(EVENT_ERROR_OCCURED);
                break;
            case 'r': // Suppose 'r' resets the state machine
                sm->sendEvent(EVENT_RESET);
                break;
            default:
                // Handle unknown characters or define additional cases
                Serial.println("Received unknown command");
                break;
        }
    }
}


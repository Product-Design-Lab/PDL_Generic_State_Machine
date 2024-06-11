#include "config.h"
#include <Arduino.h>  // for Serial

void InitAction() {
    Serial.println("Initializing...");
}

void RunningAction() {
    Serial.println("System Running...");
}

void StoppedAction() {
    Serial.println("System Stopped.");
}

void ErrorAction() {
    Serial.println("Error Occurred!");
}

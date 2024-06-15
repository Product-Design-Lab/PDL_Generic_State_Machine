#pragma once

#include "PDL_Moore_FSM.h"

typedef enum 
{
    OFF,
    RED,
    GREEN,
    YELLOW
} TrafficLightState;

typedef enum 
{
    TIMER_EXPIRED,
    BUTTON_PRESSED
} TrafficLightEvent;

void turn_red();
void turn_green();
void turn_yellow();

const PDL_Moore_FSM::transition_t traffic_light_transitions[] = {
    {OFF, TIMER_EXPIRED, RED, turn_red},
    {RED, TIMER_EXPIRED, GREEN, turn_green},
    {GREEN, TIMER_EXPIRED, YELLOW, turn_yellow},
    {YELLOW, TIMER_EXPIRED, RED, turn_red},
    {RED, BUTTON_PRESSED, OFF, nullptr},
    {GREEN, BUTTON_PRESSED, OFF, nullptr},
    {YELLOW, BUTTON_PRESSED, OFF, nullptr}
};

class TrafficLight : public PDL_Moore_FSM
{
public:
    TrafficLight() : PDL_Moore_FSM(traffic_light_transitions, sizeof(traffic_light_transitions) / sizeof(PDL_Moore_FSM::transition_t), OFF) {}
};

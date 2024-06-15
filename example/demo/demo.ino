#include "traffic_light.h"
#include "PDL_Moore_FSM.h"
#include "Adafruit_TinyUSB.h"

TrafficLight traffic_light;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        delay(1);
    }
    
    traffic_light.init();
}

void loop()
{
    if (Serial.available())
    {
        switch (Serial.read())
        {
        case 't':
            traffic_light.handle_event(TIMER_EXPIRED);
            break;
        case 'b':
            traffic_light.handle_event(BUTTON_PRESSED);
            break;
        default:
            break;
        }

        while (Serial.available())
        {
            Serial.read();
        }
    }
}

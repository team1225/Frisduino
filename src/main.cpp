#include <Arduino.h>
#include <XBOXRECV.h>
#include <Timer.h>

#include "Map.h"
#include "RelayMotor.h"
#include "OneWayMotor.h"

USB Usb;
XBOXRECV Xbox(&Usb);

Timer timer;
int8_t timer_id_safety;

RelayMotor aim(PIN_AIM_UP, PIN_AIM_DOWN);
OneWayMotor firingAction(PIN_FIRING_ACTION);
OneWayMotor acceleratingRail(PIN_ACCELERATING_RAIL);

void setup()
{
    pinMode(PIN_SAFETY_LIGHT, OUTPUT);
    digitalWrite(PIN_SAFETY_LIGHT, HIGH); // Turn on the safety LED to tell users that the robot is on, but disconnected

    if (Usb.Init() == -1) {
        while (1); // halt execution without a USB board or device
    }

    while (!(Xbox.Xbox360Connected[0])) {
        delay(500); // Wait half-second incriments until the controller connects
    }

    timer_id_safety = timer.oscillate(PIN_SAFETY_LIGHT, PERIOD_SAFETY_LIGHT, HIGH); // Blink safety LED to alert users the robot is active
}

void loop()
{
    Usb.Task();

    /*
     * The XBOXRECV Library supports up to 4 controllers, but we only use the first,
     * check controller connection with Xbox.Xbox360Connected[0] and
     * use 0 as the last argument when querying input
     */

    if (Xbox.Xbox360Connected[0]) {

        if (Xbox.getButtonPress(L1, 0)) {
            aim.Set(Direction::Bwd);
        } else if (Xbox.getButtonPress(R1, 0)) {
            aim.Set(Direction::Fwd);
        } else {
            aim.Set(Direction::Stop);
        }
    }
    else {
        // Receiver not connected
        aim.Off();
        firingAction.Off();
        acceleratingRail.Off();
        timer.stop(timer_id_safety);
        while (1); // halt execution when the controller disconnects, restart the arduino to continue
    }
}

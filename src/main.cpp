#include <Arduino.h>
#include <XBOXRECV.h>
#include <Timer.h>

#include "Map.h"
#include "RelayMotor.h"
#include "OneWayMotor.h"

USB Usb;
XBOXRECV Xbox(&Usb);

Timer timer;
int8_t timer_id_safety = -1;
int8_t timer_id_fire_delay = -1;

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

// decalire fire() and finish(), defined below loop()
extern void fire();
extern void finish();

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

        if (Xbox.getButtonPress(A, 0)) {
            if (timer_id_fire_delay == -1) {
                // timer is not running
                acceleratingRail.Go();
                timer_id_fire_delay = timer.after(PERIOD_FIRE_DELAY, fire);
            }
            // else, timer is running and command held, do nothing
        } else if (timer_id_fire_delay != -1) {
            // button dropped within fire_delay, stop
            acceleratingRail.Stop();
            timer.stop(timer_id_fire_delay);
            timer_id_fire_delay = -1;
        }
    }
    else {
        // Receiver not connected
        if (timer_id_safety != -1) {
            timer.stop(timer_id_safety);
            timer_id_safety = -1;
        }
        digitalWrite(PIN_SAFETY_LIGHT, HIGH);
        if (timer_id_fire_delay != -1) {
            timer.stop(timer_id_fire_delay);
            timer_id_fire_delay = -1;
        }
        aim.Off();
        firingAction.Off();
        acceleratingRail.Off();
        timer.stop(timer_id_safety);
        while (1); // halt execution when the controller disconnects, restart the arduino to continue
    }

    timer.update(); // Run timer events
}


void fire() {
    firingAction.Go();
    timer_id_fire_delay = -1;
    timer.after(PERIOD_FINISH_DELAY, finish);
}

void finish() {
    firingAction.Stop();
    acceleratingRail.Stop();
}

#include <Arduino.h>
#include <XBOXRECV.h>
#include <Timer.h>

#include "Map.h"
#include "RelayMotor.h"
#include "OneWayMotor.h"

USB Usb;
XBOXRECV Xbox(&Usb);

RelayMotor aim(PIN_AIM_UP, PIN_AIM_DOWN);
OneWayMotor firingAction(PIN_FIRING_ACTION);
OneWayMotor acceleratingRail(PIN_ACCELERATING_RAIL);

void setup()
{
    if (Usb.Init() == -1) {
        while (1); // halt
    }
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
    }
}

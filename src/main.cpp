#include <Arduino.h>
#include <XBOXRECV.h>
#include "RelayMotor.h"

#define AIM_UP 7
#define AIM_DOWN 8

USB Usb;
XBOXRECV Xbox(&Usb);

RelayMotor aim(AIM_UP, AIM_DOWN);

void setup() {
	if (Usb.Init() == -1) {
		while (1); // halt
	}
}

void loop() {
	// put your main code here, to run repeatedly:
	Usb.Task();

	if (Xbox.XboxReceiverConnected) {
		for (uint8_t i = 0; i < 4; i++) {
			if (Xbox.Xbox360Connected[i]) {

				if (Xbox.getButtonPress(L1, i)) {
					 aim.Set(Direction::Bwd);
				}
				else if (Xbox.getButtonPress(R1, i)) {
					aim.Set(Direction::Fwd);
				}
				else {
					aim.Set(Direction::Stop);
				}
			}
		}
	}
	// Receiver not connected
	aim.Off();
}
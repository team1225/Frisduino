#include <Arduino.h>
#include <XBOXRECV.h>

#define AIM_UP 7
#define AIM_DOWN 8

USB Usb;
XBOXRECV Xbox(&Usb);

void setup() {
  pinMode(AIM_UP, OUTPUT);
  pinMode(AIM_DOWN, OUTPUT);
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
          digitalWrite(AIM_UP, LOW);
          digitalWrite(AIM_DOWN, HIGH);
        }
        else if (Xbox.getButtonPress(R1, i)) {
          digitalWrite(AIM_UP, HIGH);
          digitalWrite(AIM_DOWN, LOW);
        }
        else {
          digitalWrite(AIM_UP, LOW);
          digitalWrite(AIM_DOWN, LOW);
        }

      }
    }
  }
}

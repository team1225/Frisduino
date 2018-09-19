# Gorilla Frisduino
Arduino + Xbox + 2014 Frisbee Robots = Gorilla Frisduino

## Project Info
- Arduino controlled frizbee robot for demos
- Removes need for CRio and Pre-2015 DriverStation

## Status
- [ ] Programming
  - [x] Xbox input working
  - [ ] Motor controller abstraction
    - [x] Relay
    - [ ] PWM
  - [ ] Arcade Drive abstraction
- [ ] Rewiring (After feature parody)
  - [x] Remove CRio and other legacy components
  - [x] Strip existing wiring
  - [x] Reorganize existing components
  - [x] Install new components
  - [x] NEATLY rewire
- [ ] Demo!

## Development
- [PlatformIO](https://platformio.org/platformio-ide) on [VS Code](https://code.visualstudio.com)
  - Using libraries:
    - USB-Host-Shield-20 (id=59)
    - Timer (id=75)
  - On platforms:
    - Arduino Uno

## Hardware
- Arduino Uno
- USB Host Sheild
- Wireless Xbox Adapter
- Xbox 360 Controller
- Our 2014 robot, sans CRio
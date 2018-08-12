#include "OneWayMotor.h"
#include <Arduino.h>

OneWayMotor::OneWayMotor(int pin_fwd) {
	m_pin_fwd = pin_fwd;
	pinMode(m_pin_fwd, OUTPUT);
	digitalWrite(m_pin_fwd, LOW);
}

OneWayMotor::~OneWayMotor() {
        digitalWrite(m_pin_fwd, LOW);
}

void OneWayMotor::Go() {
	digitalWrite(m_pin_fwd, HIGH);
}

void OneWayMotor::Stop() {
	digitalWrite(m_pin_fwd, LOW);
}

void OneWayMotor::Off() {
	digitalWrite(m_pin_fwd, LOW);
}

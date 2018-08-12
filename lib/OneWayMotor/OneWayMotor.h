#ifndef ONEWAYMOTOR_H
#define ONEWAYMOTOR_H
/*
 * class OneWayMotor(PinFwd)
 *  Class to control a one way Relay Motor controler
 *
 * void Go()
 *  Function to have the motor start moving
 *
 * void Stop()
 *  Function to have the motor stop moving
 *
 * void Off()
 *  Function to kill the motor controller,
 *  for motor safety
 *
 */

class OneWayMotor {
	private:
		int m_pin_fwd;

	public:
		OneWayMotor(int pin_fwd);
		~OneWayMotor();

		void Go();
                void Stop();
		void Off();
};

#endif

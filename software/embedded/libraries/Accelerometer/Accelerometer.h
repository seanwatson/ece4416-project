/*
 * File: Accelerometer.h
 * Author: Sean Watson
 * Description: Accelerometer library for ECE4416 project
 *
 */

#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

#include <Arduino.h>
#include <math.h>

class Accelerometer{

	public:
		Accelerometer(const byte x_pin, const byte y_pin, const byte z_pin);
		void take_reading(float* const readings) const;
        void take_reading_angle(float* const readings) const;

		const int& x_zero();
		const int& y_zero();
		const int& z_zero();

	private:
		const byte _x_pin;
		const byte _y_pin;
		const byte _z_pin;

		int _x_zero;
		int _y_zero;
		int _z_zero;

};

#endif

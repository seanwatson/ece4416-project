/*
 * File: Accelerometer.h
 * Author: Sean Watson
 * Description: Accelerometer library for ECE4416 project
 *
 */

#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

#include <Arduino.h>

class Accelerometer{

	public:
		Accelerometer(const byte x_pin, const byte y_pin, const byte z_pin);
		float* take_reading(float* const readings);
		void set_neutral_position();
		void calibrate();
		void test();

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

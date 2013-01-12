/*
 * File: Accelerometer.cpp
 * Author: Sean Watson
 * Description: Implementation file for Accelerometer library
 *
 */

#include "Accelerometer.h"

Accelerometer::Accelerometer(const byte x_pin, const byte y_pin, const byte z_pin):
	_x_pin(x_pin),
	_y_pin(y_pin),
	_z_pin(z_pin)
{
	//set_neutral_position();
	//calibrate();
}

float* Accelerometer::take_reading(float* const readings){

	readings[0] = analogRead(_x_pin);
	readings[1] = analogRead(_y_pin);
	readings[2] = analogRead(_z_pin);

	return readings;
}

void Accelerometer::set_neutral_position(){
	
	// TODO: take multiple readings and do an average
	
	float readings[3];
	take_reading(readings);

	_x_zero = readings[0];
	_y_zero = readings[1];
	_z_zero = readings[2];

}

void Accelerometer::calibrate(){

}

void Accelerometer::test(){

}

const int& Accelerometer::x_zero(){
	return _x_zero;
}

const int& Accelerometer::y_zero(){
	return _y_zero;
}

const int& Accelerometer::z_zero(){
	return _z_zero;
}

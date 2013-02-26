/*
 * File:    Accelerometer.cpp
 * Author:  Sean Watson
 * Date:    Feb 2013
 * 
 * Description: Implementation file for Accelerometer library
 *
 * Copyright (c) 2013 Sean Watson
 * Licensed under the MIT license
 *
 */

#include "Accelerometer.h"

Accelerometer::Accelerometer(const byte x_pin, const byte y_pin, const byte z_pin):
	_x_pin(x_pin),
	_y_pin(y_pin),
	_z_pin(z_pin)
{
}

void Accelerometer::take_reading(float* const readings) const{

	readings[0] = analogRead(_x_pin);
	readings[1] = analogRead(_y_pin);
	readings[2] = analogRead(_z_pin);
}

void Accelerometer::take_reading_angle(float* const readings) const{
    
    // Take a reading
    take_reading(readings);

    // Convert the readings to G
    for(int i = 0; i < 3; ++i){
        readings[i] = ((readings[i] * VOLTAGE / ADC_STEPS) - (VOLTAGE / 2)) / 0.33;
    }

    // Calculate the angles in degrees
    float x_angle = atan(readings[0] / sqrt((readings[1] * readings[1])
                    + (readings[2] * readings[2]))) * 180 / PI;
    
    float y_angle = atan(readings[1] / sqrt((readings[0] * readings[0])
                    + (readings[2] * readings[2]))) * 180 / PI;
    
    float z_angle = atan(sqrt((readings[0] * readings[0])
                    + (readings[1] * readings[1])) / readings[2]) * 180 / PI;

    // Store the readings
    readings[0] = x_angle;
    readings[1] = y_angle;
    readings[2] = z_angle;
}
    

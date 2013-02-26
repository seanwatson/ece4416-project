/*
 * File:    Accelerometer.h
 * Author:  Sean Watson
 * Date:    Feb 2013
 *
 * Description: Accelerometer library for ECE4416 project
 *
 * Copyright (c) 2013 Sean Watson
 * Licensed under the MIT license
 *
 */

#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

#include <Arduino.h>
#include <math.h>

#define VOLTAGE     3.3     // Device voltage
#define ADC_STEPS   1023    // Steps in device ADC

/**
 *
 * \class Accelerometer
 * \author Sean Watson
 *
 * ECE 4416
 * Engineering Final Project
 *
 * \brief Accelerometer library for ECE 4416 project.
 *
 * Provides methods for reading sensor values from a
 * 3-axis accelerometer and processing the readings
 */
class Accelerometer{

	public:

        /**
         * Constructor.
         *
         * \param x_pin Pin that is connected to the x-axis sensor
         * \param y_pin Pin that is connected to the y-axis sensor
         * \param z_pin Pin that is connected to the z-axis sensor
         */
		Accelerometer(const byte x_pin, const byte y_pin, const byte z_pin);

        /**
         * Takes a reading of each axis from the accelerometer and
         * returns the raw readings
         *
         * \param readings An array of 3 floats in which to store the readings
         */
		void take_reading(float* const readings) const;

        /**
         * Takes a reading of each axis from the accelerometer and
         * returns the angles from each axis to the acceleration vector
         *
         * \param An array of 3 floats in which to store the angles
         */
        void take_reading_angle(float* const readings) const;

	private:
		const byte _x_pin;
		const byte _y_pin;
		const byte _z_pin;

};

#endif // _ACCELEROMETER_H_

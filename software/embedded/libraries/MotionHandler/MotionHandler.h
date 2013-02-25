/*
 * File:    MotionHandler.h
 * Author:  Sean Watson
 * Date:    Feb 2013
 *
 * Description: Takes accelerometer readings, deciphers the motion,
 * 		        and transmits the detected motion codes
 */

#ifndef _MOTION_HANDLER_H_
#define _MOTION_HANDLER_H_

#include <Arduino.h>
#include <HardwareSerial.h>
#include <math.h>

#include "Accelerometer.h"
#include "Motion.h"

#define MAX_MOTIONS 10  // Maximum number of distinct motions allowed
#define TOLERANCE   10  // Tolerance in degrees + or - for a match to an axis

/**
 *
 * \class MotionHandler
 * \author Sean Watson
 *
 * ECE 4416
 * Engineering Final Project
 *
 * \brief Handles the user's motion by taking accelerometer readings and decoding them
 *
 * Takes a reading from the accelerometer and tries to match it to one of the motions
 * it has been set up to detect. If a match is found the matched motion's code is
 * transmitted.
 */
class MotionHandler{

	public:

        /**
         * Constructor.
         *
         * \param accel The accelerometer to take readings from
         * \param output The Serial device to write matched codes to
         */
		MotionHandler(const Accelerometer* const accel, HardwareSerial* const output);
		
        /**
         * Takes a reading, tries to match it to all of the detectable motions,
         * and transmits the matched code if one is found.
         */
        void process() const;

        /**
         * Adds a motion to the list of motions that this handler will
         * attempt to match.
         *
         * \param mot The motion to try and detect
         */
		void add_motion(const Motion& mot);

	private:
		const Accelerometer* const _accel;  // Accelerometer to take readings from
		HardwareSerial* const _output;      // Serial device to write matched codes to
		const Motion* _motions[MAX_MOTIONS];// List of motions to try and match
		int _num_motions;                   // Counter for number of motions

};

#endif // _MOTION_HANDLER_H_

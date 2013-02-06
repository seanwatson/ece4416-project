/*
 * File: MotionHandler.h
 * Author: Sean Watson
 * Description: Takes accelerometer readings, deciphers the motion,
 * 		and transmits the detected motion codes
 *
 */

#ifndef _MOTION_HANDLER_H_
#define _MOTION_HANDLER_H_

#include <Arduino.h>
#include <HardwareSerial.h>
#include <math.h>
#include "Accelerometer.h"
#include "Motion.h"

#define MAX_MOTIONS 10
#define TOLERANCE   10

class MotionHandler{

	public:
		MotionHandler(Accelerometer* accel, HardwareSerial* output);
		void process() const;
		void add_motion(const Motion&  mot);

	private:
		Accelerometer* _accel;
		HardwareSerial* _output;
		const Motion* _motions[10];
		int _num_motions;

};

#endif

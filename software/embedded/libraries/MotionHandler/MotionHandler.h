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
//#include <HardwareSerial.h>
#include <USBAPI.h>
#include <math.h>
#include "Accelerometer.h"
#include "Motion.h"

#define MAX_MOTIONS 10
#define TOLERANCE   10

class MotionHandler{

	public:
		MotionHandler(Accelerometer* accel, HardwareSerial* output);
		MotionHandler(Accelerometer* accel, Serial_* output);
		void process();
		void add_motion(Motion*  mot);

	private:
		Accelerometer* _accel;
		HardwareSerial* _output;
		//Serial_* _output;
		Motion* _motions[10];
		int _num_motions;

};

#endif

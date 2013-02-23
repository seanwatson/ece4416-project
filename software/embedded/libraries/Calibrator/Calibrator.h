/*
 * File: Calibrator.h
 * Author: Sean Watson
 * Description: Listens for calibration commands from the
 *              client and stores the values in EEPROM
 *
 */

#ifndef _CALIBRATOR_H_
#define _CALIBRATOR_H_

#include <HardwareSerial.h>
#include <EEPROM.h>
#include "Accelerometer.h"

#define CALIB_COMMAND   '+'
#define OFFSET          128

class Calibrator{

	public:
		Calibrator(Accelerometer* accel, HardwareSerial* input);
		void process() const;

	private:
		Accelerometer* _accel;
		HardwareSerial* _input;

};

#endif

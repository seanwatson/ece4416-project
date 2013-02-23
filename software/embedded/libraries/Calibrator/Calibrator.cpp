/*
 * File: Calibrator.cpp
 * Author: Sean Watson
 * Description: Implementation file for Calibrator library
 *
 */

#include "Calibrator.h"

Calibrator::Calibrator(Accelerometer* accel, HardwareSerial* input):
	_accel(accel),
	_input(input)
{
}

void Calibrator::process() const{

    if(_input->available() >= 2){
        unsigned first = _input->read();
        unsigned second = _input->read();

        if(first == CALIB_COMMAND){

            // Take a reading
            float readings[3];
            _accel->take_reading_angle(readings);

            // Calculate the index
            unsigned index = (second - '1') * 3;

            // Store the values
            EEPROM.write(index, readings[0] + OFFSET);
            EEPROM.write(index + 1, readings[1] + OFFSET);
            EEPROM.write(index + 2, readings[2] + OFFSET);

        }
    }
	
}


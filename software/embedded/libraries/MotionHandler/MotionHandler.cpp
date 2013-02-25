/*
 * File:    MotionHandler.cpp
 * Author:  Sean Watson
 * Date:    Feb 2013
 *
 * Description: Implementation file for MotionHandler library
 */

#include "MotionHandler.h"

MotionHandler::MotionHandler(const Accelerometer* const accel, HardwareSerial* const output):
	_accel(accel),
	_output(output),
	_num_motions(0)
{
}

void MotionHandler::process() const{

    // Vars to store angles of each motion as its checked
    static int mx, my, mz;

	// Take a reading
	static float readings[3];
	_accel->take_reading_angle(readings);
    
    // Loop through all of the detectable motions
	for(int i = 0; i < _num_motions; ++i){
		mx = _motions[i]->x();
		my = _motions[i]->y();
		mz = _motions[i]->z();

        // Check if the reading matches the motion
        if(readings[0] > mx - TOLERANCE && readings[0] < mx + TOLERANCE &&
		   readings[1] > my - TOLERANCE && readings[1] < my + TOLERANCE &&
		   readings[2] > mz - TOLERANCE && readings[2] < mz + TOLERANCE){
			_output->print(_motions[i]->code());
		}
	}
}

void MotionHandler::add_motion(const Motion& mot){

    // Check if there is still space in the list
	if(_num_motions < MAX_MOTIONS){

        // Add the motion to the list
		_motions[_num_motions] = &mot;
		++_num_motions;
	}
}

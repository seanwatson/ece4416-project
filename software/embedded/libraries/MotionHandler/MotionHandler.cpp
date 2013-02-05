/*
 * File: MotionHandler.cpp
 * Author: Sean Watson
 * Description: Implementation file for MotionHandler library
 *
 */

#include "MotionHandler.h"

//MotionHandler::MotionHandler(Accelerometer* accel, Serial_* output):
MotionHandler::MotionHandler(Accelerometer* accel, HardwareSerial* output):
	_accel(accel),
	_output(output),
	_num_motions(0)
{
}

void MotionHandler::process(){

	// Take a reading
	float readings[3];
	_accel->take_reading(readings);

	float& x = readings[0];
	float& y = readings[1];
	float& z = readings[2];

	// Convert the readings to G
	for(int i = 0; i < 3; ++i){
		readings[i] = ((readings[i] * 3.3 / 1023) - 1.65) / 0.33;
	}

	// Calculate the angles in degrees
	float x_angle = atan(x / sqrt((y * y) + (z * z))) * 180 / 3.14159;
	float y_angle = atan(y / sqrt((x * x) + (z * z))) * 180 / 3.14159;
	float z_angle = atan(sqrt((x * x) + (y * y)) / z) * 180 / 3.14159;
/*
    x_angle = abs(x_angle);
    y_angle = abs(y_angle);
    z_angle = abs(z_angle);
*/	
	// Match the reading to a motion
	for(int i = 0; i < _num_motions; ++i){
		int mx = _motions[i]->x();
		int my = _motions[i]->y();
		int mz = _motions[i]->z();
	/*
        _output->print(mx);
	    _output->print("; ");
	    _output->print(my);
	    _output->print("; ");
	    _output->println(mz);
    */
		if(x_angle > mx - TOLERANCE && x_angle < mx + TOLERANCE &&
		   y_angle > my - TOLERANCE && y_angle < my + TOLERANCE &&
		   z_angle > mz - TOLERANCE && z_angle < mz + TOLERANCE){
			_output->print(_motions[i]->code());
		}
	}

/*
	// Send the motion's code
	_output->print(x_angle);
	_output->print(", ");
	_output->print(y_angle);
	_output->print(", ");
	_output->println(z_angle);
*/
}

void MotionHandler::add_motion(Motion* mot){

	if(_num_motions < MAX_MOTIONS){
		_motions[_num_motions] = mot;
		++_num_motions;
	}
}

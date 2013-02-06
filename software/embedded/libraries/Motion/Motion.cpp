/*
 * File: Motion.cpp
 * Author: Sean Watson
 * Description: A generic motion
 *
 */

#include "Motion.h"

Motion::Motion(int code, int x_deg, int y_deg, int z_deg):
	_code(code),
	_x(x_deg),
	_y(y_deg),
	_z(z_deg)
{
}

const int& Motion::code() const{
	return _code;
}

const int& Motion::x() const{
	return _x;
}

const int& Motion::y() const{
	return _y;
}

const int& Motion::z() const{
	return _z;
}


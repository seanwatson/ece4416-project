#include "Motion.h"

Motion::Motion(int code, int x_deg, int y_deg, int z_deg):
	_code(code),
	_x(x_deg),
	_y(y_deg),
	_z(z_deg)
{
}

const int& Motion::code(){
	return _code;
}

const int& Motion::x(){
	return _x;
}

const int& Motion::y(){
	return _y;
}

const int& Motion::z(){
	return _z;
}


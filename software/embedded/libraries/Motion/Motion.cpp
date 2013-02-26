/*
 * File:    Motion.cpp
 * Author:  Sean Watson
 * Date:    Feb 2013
 * 
 * Description: Implementation of Motion Library
 *
 * Copyright (c) 2013 Sean Watson
 * Licensed under the MIT license
 *
 */

#include "Motion.h"

Motion::Motion(const int code, int x_deg, int y_deg, int z_deg):
	_code(code),
	_x(x_deg),
	_y(y_deg),
	_z(z_deg)
{
}

Motion::Motion(const int code):
    _code(code)
{
    unsigned index = (code - 1) * 3;

    _x = static_cast<int>(EEPROM.read(index)) - OFFSET;
    _y = static_cast<int>(EEPROM.read(index + 1)) - OFFSET;
    _z = static_cast<int>(EEPROM.read(index + 2)) - OFFSET;
}

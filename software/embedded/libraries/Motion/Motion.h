/*
 * File: Motion.h
 * Author: Sean Watson
 * Description: A generic motion
 *
 */

#ifndef _MOTION_H_
#define _MOTION_H_

class Motion{

	public:
		Motion(int code, int x_deg, int y_deg, int z_deg);
		const int& code();
		const int& x();
		const int& y();
		const int& z();

	private:
		int _code;
		int _x;
		int _y;
		int _z;

};

#endif

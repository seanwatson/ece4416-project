/*
 * File: Motion.h
 * Author: Sean Watson
 * Date: Feb 2013
 *
 *
 * Description: A data structure for storing motions that
 *              can be detected by a MotionHandler
 */

#ifndef _MOTION_H_
#define _MOTION_H_

#include <EEPROM.h>

// Offset bytes are stored in EEPROM with
#define OFFSET  128

/**
 *
 * \class Motion
 * \author Sean Watson
 *
 * ECE 4416
 * Engineering Final Project
 *
 * \brief A data structure for storing motions.
 *
 * Stores the angles from the x, y, and z axis to the acceleration
 * vector that are needed to constitute a match for the motion.
 */
class Motion{

	public:

        /**
         * Constructor.
         *
         * \param code The code to be transmitted when the motion is matched
         * \param x_deg The angle from the x axis to acceleration vector
         * \param y_deg The angle from the y axis to acceleration vector
         * \param z_deg The angle from the z axis to acceleration vector
         */
		Motion(const int code, int x_deg, int y_deg, int z_deg);
        
        /**
         * Constructor. This constructor loads the angles from EEPROM rather
         * than having them passed explicitly. Note, this can only be used
         * after loading the EEPROM using the calibration tool.
         *
         * \param code The code to be transmitted when the motion is matched
         */
        Motion(const int code);

        /**
         * Gets the code
         *
         * \return The motion's code
         */
		inline int code() const { return _code; }
        
        /**
         * Gets the x angle
         *
         * \return The motion's x angle
         */
		inline int x() const { return _x; }

        /**
         * Gets the y angle
         *
         * \return The motion's y angle
         */
		inline int y() const { return _y; }
        
        /**
         * Gets the z angle
         *
         * \return The motion's z angle
         */
		inline int z() const { return _z; }

	private:
		const int _code;
		int _x;
		int _y;
		int _z;

};

#endif  // _MOTION_H_

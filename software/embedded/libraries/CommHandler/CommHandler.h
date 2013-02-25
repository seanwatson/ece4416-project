/*
 * File: CommHandler.h
 * Author: Sean Watson
 * Date: Feb 2013
 *
 * Description: Handles incoming communication by reading
 *              received data and preforming corresponding
 *              operations like connection state changes and
 *              calibration.
 *
 */

#ifndef _COMMHANDLER_H_
#define _COMMHANDLER_H_

#include <HardwareSerial.h>
#include <EEPROM.h>
#include "Accelerometer.h"

#define CALIB_CMD   '+'
#define CONN_CMD    '%'
#define HB_CMD      'H'

#define CONN_STATE      'C'
#define DISCONN_STATE   'D'

class CommHandler{

    public:
        CommHandler(Accelerometer* accel, HardwareSerial* input);
        void process();
        bool connected() const;

    private:
        void calibrate();
        void manage_conn();

        Accelerometer* _accel;
        HardwareSerial* _input;
        bool _connected;
};

#endif

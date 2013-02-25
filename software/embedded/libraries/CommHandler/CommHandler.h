/*
 * File:    CommHandler.h
 * Author:  Sean Watson
 * Date:    Feb 2013
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

// Commands that can be received
#define CALIB_CMD   '+'
#define CONN_CMD    '%'
#define HB_CMD      'H'

// State change flags
#define CONN_STATE      'C'
#define DISCONN_STATE   'D'

// Offset to apply to values in EEPROM
#define OFFSET  128

/**
 *
 * \class CommHandler
 * \author Sean Watson
 *
 * ECE 4416
 * Engineering Final Project
 *
 * \brief Handles incoming communication from the client.
 *
 * Handles incoming communication by reading received data and
 * preforming operations like connection state changes and
 * calibration
 */
class CommHandler{

    public:

        /**
         * Constructor.
         *
         * \param accel An accelerometer to take calibration readings from
         * \param input The serial device to listen for communication on
         */
        CommHandler(const Accelerometer* const accel, HardwareSerial* const input);

        /**
         * Listens for incoming communication. When bytes are detected it
         * reads them and preforms the requested actions.
         */
        void process();

        /**
         * Gets the current connection state.
         *
         * \return True if connected, false otherwise
         */
        inline bool connected() const { return _connected; }

    private:

        /**
         * Handler for a calibration command. Reads the motion code to
         * be calibrated, takes an accelerometer reading, and stores
         * that reading as the match value for the code.
         */
        void calibrate() const;

        /**
         * Connection handler. Manages connect and disconnect commands
         * from the bluetooth module as well as heart beats from the 
         * client to maintain the proper connection state.
         */
        void manage_conn();

        const Accelerometer* const _accel;  // Accelerometer to take calibration readings from
        HardwareSerial* const _input;       // Serial device to listen for communication on
        bool _connected;                    // Connection state. True if connected, false otherwise
};

#endif  // _COMMHANDLER_H_

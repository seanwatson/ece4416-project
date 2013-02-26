/*
 * File:    CommHandler.cpp
 * Author:  Sean Watson
 * Date:    Feb 2013
 *
 * Description: Implementation of CommHandler library
 *
 * Copyright (c) 2013 Sean Watson
 * Licensed under the MIT license
 *
 */


#include "CommHandler.h"

CommHandler::CommHandler(const Accelerometer* const accel, HardwareSerial* const input):
    _accel(accel),
    _input(input),
    _connected(false)
{
}

void CommHandler::process(){

    static unsigned char cmd;   // Static because this is called very frequently

    // Check if there are any bytes available
    if(_input->available()){

        // Read the first byte
        cmd = _input->read();

        // Determine which command is coming
        switch(cmd){

            // Calibration command
            case CALIB_CMD:
                calibrate();
                break;
            
            // Connection state management command
            case CONN_CMD:
                manage_conn();
                break;

            // Heart beat command
            case HB_CMD:
                _connected = true;
                break;
                
            default:
                // ERROR condition, unknown command
                break;
        }
    }
}

void CommHandler::calibrate() const{

    char code, success;

    // Read one byte, timeout after a second
    success = _input->readBytes(&code, 1);

    // Validate the read
    if(success && code >= '1' && code <= '9'){
        
        // Take an accelerometer reading
        float readings[3];
        _accel->take_reading_angle(readings);

        // Calculate the index
        unsigned index = (code - '1') * 3;

        // Store the values
        EEPROM.write(index, readings[0] + OFFSET);
        EEPROM.write(index + 1, readings[1] + OFFSET);
        EEPROM.write(index + 2, readings[2] + OFFSET);
    }
    else{
        // ERROR condition, didn't get code byte or invalid code
    }
}

void CommHandler::manage_conn(){

    char state[10], success;

    // Read bytes, timeout after a second
    success = _input->readBytes(state, 7);

    // Check that all bytes were read
    if(success == 7){

        // Check if it is a connect command
        if(state[0] == CONN_STATE){
            _connected = true;  // Now device is connected
        }
        // Check if it is a disconnect command
        else if(state[0] == DISCONN_STATE){

            // Toggle the state
            _connected = false;

            // Read in the 3 more bytes to clear the buffer
            success = _input->readBytes(state, 3);
            
            // Make sure we got them
            if(success != 3){
                //ERROR condition, expected more bytes
            }
        }
        else{
            // ERROR condition, unknown connection command
        }
    }
    else{
        // ERROR condition, didn't get expected number of bytes
    }
}


/*
 * File: CommHandler.cpp
 * Author: Sean Watson
 * Date: Feb 2013
 *
 * Description: Implementation of CommHandler
 *
 */


#include "CommHandler.h"

CommHandler::CommHandler(Accelerometer* accel, HardwareSerial* input):
    _accel(accel),
    _input(input),
    _connected(false)
{
}

void CommHandler::process(){

    if(_input->available()){
        unsigned char cmd = _input->read();

        switch(cmd){

            case CALIB_CMD:
                calibrate();
                break;
            
            case CONN_CMD:
                manage_conn();
                break;

            default:
                // ERROR condition
                // TODO: something error handlingish
                break;
        }
    }
}

bool CommHandler::connected() const {
    return _connected;
}

void CommHandler::calibrate(){

    char code, success;

    // Read one byte, timeout after a second
    success = _input->readBytes(&code, 1);

    // Validate the read
    if(success && code >= '1' && code <= '9'){
        
        // Take a reading
        float readings[3];
        _accel->take_reading_angle(readings);

        // Calculate the index
        unsigned index = (code - '1') * 3;

        // Store the values
        EEPROM.write(index, readings[0] + 128);
        EEPROM.write(index + 1, readings[1] + 128);
        EEPROM.write(index + 2, readings[2] + 128);
    }
    else{
        // ERROR condition
        // TODO: something to inform of error
    }
}

void CommHandler::manage_conn(){

    char state[10], success;

    // Read one byte, timeout after a second
    success = _input->readBytes(state, 7);

    if(success == 7){

        if(state[0] == CONN_STATE){
            _connected = true;
            _input->write('0');
        }
        else if(state[0] == DISCONN_STATE){

            // Toggle the state
            _connected = false;

            // Read in the 3 more bytes
            success = _input->readBytes(state, 3);
            
            // Make sure we got them
            if(success != 3){
                //ERROR condition
                // TODO: something to inform of error
            }
        }
        else{
            // ERROR condition
            // TODO: something
        }
    }
    else{
        // ERROR condition
        // TODO: something
    }
}


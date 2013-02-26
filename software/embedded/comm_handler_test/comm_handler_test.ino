/*********************************************************
* 
* File:     comm_handler_test.ino
* Author:   Sean Watson
* Date:     Feb 2013
*
* Description: Test code for connection and disconnection
*              commands. Prints state changes.
*
* Copyright (c) 2013 Sean Watson
* Licensed under the MIT license
*
**********************************************************/

#include <EEPROM.h>

#include <Accelerometer.h>
#include <CommHandler.h>

#define X_PIN   A0
#define Y_PIN   A1
#define Z_PIN   A2

HardwareSerial* bluetooth = &Serial1;

Accelerometer accel(X_PIN, Y_PIN, Z_PIN);
CommHandler comm_h(&accel, bluetooth);

boolean conn = comm_h.connected();

void setup(){

  // Setup the serial hardware
  bluetooth->begin(115200);
  Serial.begin(115200);
}

void loop(){
  
  // Process and communication
  comm_h.process();
  
  // Check if the communication state changed
  if(conn != comm_h.connected()){
    conn = comm_h.connected();      // Store the new state
    
    // Print which state change just happened
    if(conn){
      Serial.println("Connected!");
    }
    else{
      Serial.println("Disconnected!");
    }
  }
}




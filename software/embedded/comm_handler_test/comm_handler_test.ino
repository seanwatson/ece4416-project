#include <EEPROM.h>

#include <Accelerometer.h>
#include <MotionHandler.h>
#include <Motion.h>
#include <CommHandler.h>

#define X_PIN   A0
#define Y_PIN   A1
#define Z_PIN   A2

HardwareSerial* bluetooth = &Serial1;

Accelerometer accel(X_PIN, Y_PIN, Z_PIN);
CommHandler comm_h(&accel, bluetooth);

boolean conn = comm_h.connected();

void setup(){
  bluetooth->begin(115200);
  Serial.begin(115200);
}

void loop(){
  
  comm_h.process();
  
  if(conn != comm_h.connected()){
    conn = comm_h.connected();
    if(conn){
      Serial.println("Connected!");
    }
    else{
      Serial.println("Disconnected!");
    }
  }
}




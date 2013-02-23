#include <EEPROM.h>

#include <Accelerometer.h>
#include <MotionHandler.h>
#include <Motion.h>
#include <Calibrator.h>

#define X_PIN   A0
#define Y_PIN   A1
#define Z_PIN   A2

HardwareSerial* bluetooth = &Serial1;

Accelerometer accel(X_PIN, Y_PIN, Z_PIN);
MotionHandler handler(&accel, bluetooth);
Calibrator calibrator(&accel, bluetooth);

Motion forwardMotion(1);
Motion rightMotion(2);
Motion backwardMotion(3);
Motion leftMotion(4);
Motion fastForwardMotion(5);
Motion fastRightMotion(6);
Motion fastBackwardMotion(7);
Motion fastLeftMotion(8);

void setup(){
  bluetooth->begin(115200);
  handler.add_motion(forwardMotion);
  handler.add_motion(rightMotion);
  handler.add_motion(backwardMotion);
  handler.add_motion(leftMotion);
  handler.add_motion(fastForwardMotion);
  handler.add_motion(fastRightMotion);
  handler.add_motion(fastBackwardMotion);
  handler.add_motion(fastLeftMotion);
}

void loop(){
  
  handler.process();
  calibrator.process();
  
  delay(10);
}




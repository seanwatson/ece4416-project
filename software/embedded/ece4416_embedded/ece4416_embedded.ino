#include <Accelerometer.h>
#include <MotionHandler.h>
#include <Motion.h>

#define X_ZERO  504
#define Y_ZERO  500
#define Z_ZERO  533

#define X_PIN   A0
#define Y_PIN   A1
#define Z_PIN   A2

Serial_* usb = &Serial;
HardwareSerial* bluetooth = &Serial1;

Accelerometer accel(X_PIN, Y_PIN, Z_PIN);
MotionHandler handler(&accel, bluetooth);

Motion forwardMotion(1, -55, 0, 55);
Motion rightMotion(2, -50, -36, -80);
Motion backwardMotion(3, -55, 0, -55);
Motion leftMotion(4, -60, 25, -80);

void setup(){
  usb->begin(115200);
  bluetooth->begin(115200);
  accel.set_neutral_position();
  handler.add_motion(&forwardMotion);
  handler.add_motion(&rightMotion);
  handler.add_motion(&backwardMotion);
  handler.add_motion(&leftMotion);
}

void loop(){
  
  handler.process();
  
  delay(10);
}




#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
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
MotionHandler motion_h(&accel, bluetooth);
CommHandler comm_h(&accel, bluetooth);

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
  add_motions();
  setup_wdt();
  disable_periphs();
}

void loop(){
  
  comm_h.process();
  
  // Check if the device is connected
  if(comm_h.connected()){
    // Connected, take a reading
    motion_h.process();
    delay(10);
  }
  else{
    // Not connected, sleep
    sleep();
    delay(1000);
  }  
}

void disable_periphs(){
  power_spi_disable();
  power_timer2_disable();
  power_twi_disable();  
}

void setup_wdt(){
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);
  
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  /* set new watchdog timeout prescaler value */
  //WDTCSR = 1<<WDP0 | 1<<WDP3;           /* 8.0 seconds */
  WDTCSR = 1<<WDP3;                     /* 4.0 seconds */
  //WDTCSR = 1<<WDP0 | 1<<WDP1 | 1<<WDP2; /* 2.0 seconds */
  //WDTCSR = 1<<WDP1 | 1<<WDP2;           /* 1.0 second */
  //WDTCSR = 1<<WDP0 | 1<<WDP2;           /* 0.5 seconds */
  //WDTCSR = 1<<WDP2;                     /* 0.25 seconds */
  //WDTCSR = 1<<WDP0 | 1<<WDP1;           /* 128 ms */
  //WDTCSR = 1<<WDP1;                     /* 64 ms */
  //WDTCSR = 1<<WDP0;                     /* 32 ms */
  
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
}

void add_motions(){
  motion_h.add_motion(forwardMotion);
  motion_h.add_motion(rightMotion);
  motion_h.add_motion(backwardMotion);
  motion_h.add_motion(leftMotion);
  motion_h.add_motion(fastForwardMotion);
  motion_h.add_motion(fastRightMotion);
  motion_h.add_motion(fastBackwardMotion);
  motion_h.add_motion(fastLeftMotion);
}

void sleep(){
  power_adc_disable();  // Disable the ADC
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();      // Enable sleep mode
  sleep_mode();        // Enter sleep (awakes on wdt and continues)
  sleep_disable();     // Disable sleep mode
  power_adc_enable();  // Re-enable the ADC
}

ISR(WDT_vect){
  
}




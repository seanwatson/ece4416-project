/*********************************************************
* 
* File:     ece4416_embedded.ino
* Author:   Sean Watson
* Date:     Feb 2013
*
* Description: Main embedded code for ECE 4416 project.
*              Manages the connection state and preforms
*              the necessary ADC for detecting motions
*
**********************************************************/

// AVR libraries for sleeping
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

// Arduino libraries
#include <EEPROM.h> // Used for reading calibrated angles from EEPROM

// Custom libraries
#include <Accelerometer.h>
#include <MotionHandler.h>
#include <Motion.h>
#include <CommHandler.h>

// Accelerometer pins
#define X_PIN   A0
#define Y_PIN   A1
#define Z_PIN   A2

// Sampling rates (ms)
#define ACCEL_RATE  10
#define SLEEP_RATE  1000

#define BT_BAUD 115200


// Setup peripherals
HardwareSerial* bluetooth = &Serial1;
Accelerometer accel(X_PIN, Y_PIN, Z_PIN);

// Setup handlers
MotionHandler motion_h(&accel, bluetooth);
CommHandler comm_h(&accel, bluetooth);

// Setup motions
Motion forwardMotion(1);
Motion rightMotion(2);
Motion backwardMotion(3);
Motion leftMotion(4);
Motion fastForwardMotion(5);
Motion fastRightMotion(6);
Motion fastBackwardMotion(7);
Motion fastLeftMotion(8);

void setup(){
  bluetooth->begin(BT_BAUD);// Start communication with BT module
  add_motions();            // Add motions to detect
  setup_wdt();              // Setup watchdog timer for sleep mode
  disable_periphs();        // Disable unused peripherals to save power
}

void loop(){
  
  // Process any incoming communications
  comm_h.process();
  
  // Check if the device is connected
  if(comm_h.connected()){
    
    // Connected, take a reading
    motion_h.process();

    // Limit sampling rate
    delay(ACCEL_RATE);
  }
  else{
    
    // Not connected, sleep
    sleep();

    // Stay awake for a period of time to detect communications
    delay(SLEEP_RATE);
  }  
}

// Disables unused peripherals for power saving
void disable_periphs(){
  power_spi_disable();
  power_timer2_disable();
  power_twi_disable();  
}

// Sets up the watchdog timer to wake the device from sleep
void setup_wdt(){
  
  // Clear the reset flag.
  MCUSR &= ~(1<<WDRF);
  
  // This allows WDT configuration for 4 clocks
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  // Set new watchdog timeout
  //WDTCSR = 1<<WDP0 | 1<<WDP3;           // 8.0 seconds
  WDTCSR = 1<<WDP3;                     // 4.0 seconds
  //WDTCSR = 1<<WDP0 | 1<<WDP1 | 1<<WDP2; // 2.0 seconds
  //WDTCSR = 1<<WDP1 | 1<<WDP2;           // 1.0 second
  //WDTCSR = 1<<WDP0 | 1<<WDP2;           // 0.5 seconds 
  //WDTCSR = 1<<WDP2;                     // 0.25 seconds
  //WDTCSR = 1<<WDP0 | 1<<WDP1;           // 128 ms 
  //WDTCSR = 1<<WDP1;                     // 64 ms 
  //WDTCSR = 1<<WDP0;                     // 32 ms 
  
  // Enable the WDT interrupt
  WDTCSR |= _BV(WDIE);
}

// Adds motions to detect
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

// Puts the MCU into a power saving sleep mode
void sleep(){
  power_adc_disable();  // Disable the ADC for more power saving
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Complete power down
  sleep_enable();      // Enable sleep mode

  sleep_mode();        // Enter sleep (awakes on wdt and continues)
  
  sleep_disable();     // Disable sleep mode
  power_adc_enable();  // Re-enable the ADC
}

// Define WDT interrupt routine
ISR(WDT_vect){
  // Do nothing
}




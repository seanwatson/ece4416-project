/*********************************************************
* 
* File:     bluetooth_loader.ino
* Author:   Sean Watson
* Date:     Feb 2013
*
* Description: Sketch to quickly program the bluetooth
*              module with the corrent firmware settings
*
**********************************************************/

void setup(){
  
  // Start communication
  Serial1.begin(115200);
  
  // Get into command mode
  while(Serial1.available() < 1){
    Serial1.write("$$$");
  }
  
  // Change name
  Serial1.write("SN,ProjectDevBoard\r");
  delay(250);
  
  // Change inquiry window for power saving
  Serial1.write("SI,0012\r");
  delay(250);
  
  // Change page window for power saving
  Serial1.write("SJ,0012\r");
  delay(250);
  
  // Change configuration timer to off
  Serial1.write("ST,0\r");
  delay(250);
  
  // Change status string for connect and disconnect events
  Serial1.write("SO,%\r");
  delay(250);
  
  // Enable deep-sleep, 20s SNIFF mode for power saving
  Serial1.write("SW,8FFF\r");
  delay(250);
  
  // Enable 2s off, 6s on low power connection
  Serial1.write("S|,0206\r");
  delay(250);
  
  // Reduce TX power to 0db for power saving
  Serial1.write("SY,FFF8\r");
  delay(250);
  
  // Disable all GPIO ports for power saving
  Serial1.write("S%,1000\r");
  delay(250);
  
  // Reset the module for new settings to take effect
  Serial1.write("R,1\r");
  
}

void loop() {}

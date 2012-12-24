/*********************************************************
* Forwards any serial communication over USB through to
* the Bluetooth module and vice versa
**********************************************************/

int usb_baud = 115200;  // USB baud rate
int bt_baud = 115200;   // Bluetooth baud rate

void setup(){
  
  // Setup the serial channels
  Serial.begin(usb_baud);
  Serial1.begin(bt_baud);
}

void loop(){
  
  // Forward USB to Bluetooth
  if(Serial.available()){
    Serial1.write(Serial.read());
  }
  
  // Forward Bluetooth to USB
  if(Serial1.available()){
    Serial.write(Serial1.read());
  }
}

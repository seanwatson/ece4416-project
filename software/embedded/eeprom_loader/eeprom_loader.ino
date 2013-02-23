#include <EEPROM.h>

void setup(){
  
 unsigned offset = 128;
 
 // forward
 EEPROM.write(0, -70 + offset);
 EEPROM.write(1, 0 + offset);
 EEPROM.write(2, 70 + offset);

 // right
 EEPROM.write(3, -60 + offset);
 EEPROM.write(4, -25 + offset);
 EEPROM.write(5, -80 + offset);

 // backward
 EEPROM.write(6, -70 + offset);
 EEPROM.write(7, 0 + offset);
 EEPROM.write(8, -70 + offset);

 // left
 EEPROM.write(9, -70 + offset);
 EEPROM.write(10, 10 + offset);
 EEPROM.write(11, -80 + offset);

 // fast forward
 EEPROM.write(12, -55 + offset);
 EEPROM.write(13, 0 + offset);
 EEPROM.write(14, 55 + offset);

 // fast right
 EEPROM.write(15, -50 + offset);
 EEPROM.write(16, -36 + offset);
 EEPROM.write(17, -80 + offset);

 // fast backward
 EEPROM.write(18, -55 + offset);
 EEPROM.write(19, 0 + offset);
 EEPROM.write(20, -55 + offset);

 // fast left
 EEPROM.write(21, -60  + offset);
 EEPROM.write(22, 25  + offset);
 EEPROM.write(23, -80  + offset); 
  
}


void loop(){
  
}



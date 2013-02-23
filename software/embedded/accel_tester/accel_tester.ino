#define X A0
#define Y A1
#define Z A2

float x, y, z, total;

void setup(){
  Serial.begin(115200);
  //pinMode(11, OUTPUT);
  //digitalWrite(11, HIGH);
}

void loop(){
  
  // Raw readings
  x = (float)analogRead(X);
  y = (float)analogRead(Y);
  z = (float)analogRead(Z);
  
  // Readings as voltages
  x = x / 1023.0 * 3.3;
  y = y / 1023.0 * 3.3;
  z = z / 1023.0 * 3.3;
  
  // Readings as +- voltages
  x = x - 1.65;
  y = y - 1.65;
  z = z - 1.65;
  
  // Readings as g
  x = x / 0.33;
  y = y / 0.33;
  z = z / 0.33;
  
  // Readings as angles
  float x2 = atan(x / sqrt((y * y) + (z * z))) * 180 / PI;
  float y2 = atan(y / sqrt((x * x) + (z * z))) * 180 / PI;
  float z2 = atan(sqrt((x * x) + (y * y)) / z) * 180 / PI;
  
  
  //total = sqrt((x*x) + (y*y) + (z*z));
  
  Serial.print(x2);
  Serial.print(", ");
  Serial.print(y2);
  Serial.print(", ");
  Serial.println(z2);
  //Serial.print(z);
  //Serial.print(", ");
  //Serial.println(total);
  
  delay(100);
}

#define X A0
#define Y A1
#define Z A2

int x, y, z;

void setup(){
  Serial.begin(115200);
}

void loop(){
  x = analogRead(X);
  y = analogRead(Y);
  z = analogRead(Z);
  
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.println(z);
  
  delay(100);
}

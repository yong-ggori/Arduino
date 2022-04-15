#include <HardwareSerial.h> 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int HighScore = 10, LastScore =5;
  boolean state = true;

  Serial.println((String)HighScore+"&"+LastScore+"&"+state);
  
  Serial.print("Data recieved : ");
  Serial.println(Serial.read());
  delay(200);
}

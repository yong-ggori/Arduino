#include <SoftwareSerial.h>

SoftwareSerial ble(4, 5);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ble.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(ble.available()){//블루투스로 받는 값이 있으면
    Serial.write(ble.read());
  }
  if(Serial.available()){
    ble.write(Serial.read());
  }
}

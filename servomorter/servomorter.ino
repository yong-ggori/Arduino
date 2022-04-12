#include <Servo.h>
Servo myServo;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  myServo.attach(11);//서보모터 제어할 핀 번호
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analog_in = analogRead(A0);
  int val = map(analog_in, 0, 1023, 0, 180);//서보모터는 0~180도 제어 가능
  Serial.println(val);
  myServo.write(val);
}

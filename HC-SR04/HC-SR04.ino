//#include "pitches.h"

int trig = 2;
int echo = 3;
int buzzer = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, OUTPUT);
  delayMicroseconds(10);//10마이크로 세컨드 딜레이, 10마이크로 세컨드 만큼 HIGH 유지
  digitalWrite(trig, LOW);
  //int dis = pulseIn(echo, HIGH);//거리 측정
  int dis = pulseIn(echo, HIGH)*340/2/10000; //cm 단위로 바꿈

  if(dis > 200){
    dis = 0;
  }

  digitalWrite(buzzer, HIGH);
  delay(dis*5);
  digitalWrite(buzzer, LOW);
  delay(dis*5);

//  if(dis < 18){
//    sing(1);
//  }
  
  Serial.println(dis);
  delay(100);
}

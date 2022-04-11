void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){// 수신된게 있을때만 다음 실행
    int data = Serial.read();
    if(data == 49){ //1이 입력되면, 1의 아스키 코드 49
  for(int i = 0; i< 255; i++){ //PWM 제어 ?
    analogWrite(11, i);
    delay(30);
  }
    }
    else if(data == 50){
      digitalWrite(11, HIGH);
      delay(100);
      digitalWrite(11, LOW);
      delay(100);
      digitalWrite(11, HIGH);
      delay(100);
      digitalWrite(11, LOW);
      delay(100);
    }
    else if(data == 51){
      digitalWrite(11, LOW);
    }
    Serial.println(data);
  }
}

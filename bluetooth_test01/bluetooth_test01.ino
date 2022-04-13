#include <SoftwareSerial.h>

SoftwareSerial ble(4, 5);//RX/TX
String myStr = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ble.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(ble.available()){//블루투스로 받는 값이 있으면
    char mychar = (char)ble.read();
    myStr += mychar;
    //Serial.println(myStr, DEC);//입력문자 아스키 코드 확인해 보기 위함으로 10진수로 출력
    delay(5);
  }
  if(!myStr.equals("")){
    Serial.println(myStr);
    if(myStr == "ledon\r\n")//시리얼 통신으로 문자 넘기기 위해서 
                            //커서 위치 앞으로(\r, 아스키코드 13)
                            //개행 (\n, 아스키코드 10) 추가해 주어야 한다.
      digitalWrite(13, HIGH);
    else if(myStr == "ledoff\r\n"){
      digitalWrite(13, LOW);
    }
    myStr = "";
  }
  if(Serial.available()){
    ble.write(Serial.read());
  }
}

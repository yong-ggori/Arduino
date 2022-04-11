#include <SoftwareSerial.h>

#define TX 6
#define RX 7

SoftwareSerial soft_Serial(TX, RX); //아두이노 간 통신 연결

void setup() {
  // put your setup code here, to run once:
  soft_Serial.begin(115200); // TX 6 RX 7
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    
  if(soft_Serial.available()){
    String data = soft_Serial.readString();
//  Serial.println(data); //컴퓨터와의 통신 확인
    if(data == "ledon"){
      Serial.println("success");
      digitalWrite(13, HIGH);
    }
    else if(data == "ledoff"){
      Serial.println("fail");
      digitalWrite(13, LOW);
    }
  }
}

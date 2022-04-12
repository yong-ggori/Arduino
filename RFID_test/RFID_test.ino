#include <SPI.h>//SPI 통신 이용하기 위한 라이브러리
#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#define RST_PIN 9
#define SS_PIN 10 //SS == SDA

MFRC522 mfrc(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc.PCD_Init();//UID 확인 위함
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!mfrc.PICC_IsNewCardPresent()) //카드 인식 못하면 return
    return;
  if(!mfrc.PICC_ReadCardSerial()) //20행 ~ 23행 예외처리
    return;

  if(mfrc.uid.uidByte[0] == 195 &&
     mfrc.uid.uidByte[1] == 116 &&
     mfrc.uid.uidByte[2] == 39 &&
     mfrc.uid.uidByte[3] == 12)
   {Serial.println("Authorized access");
    delay(500);
   }else{
    Serial.println("Access denied");
    delay(500);
   }
//  Serial.print("Card UID : ");
//  for(byte i = 0; i < 4; i++){
//    Serial.print(mfrc.uid.uidByte[i]);
//    Serial.print(" ");
//  }
//  Serial.println();
}

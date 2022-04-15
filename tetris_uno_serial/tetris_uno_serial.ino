#include <SoftwareSerial.h>

#define TX 6
#define RX 7

char str[20];
char* pstr[4] = {0};
int highScore = 0, lastScore = 0, state = 0;
int count = 0, i = 0;

SoftwareSerial soft_Serial(TX, RX); //아두이노 간 통신 연결

void setup() {
  // put your setup code here, to run once:
  soft_Serial.begin(115200); // TX 6 RX 7
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(soft_Serial.available()){
    str[count++] = soft_Serial.read();
    //delay(1);
  }
  str[count] = '\0';
  //soft_Serial.println(str);
  pstr[i] = strtok(str, "&");
  while(pstr[i++]!=NULL){
    switch(i){
      case 0:
        highScore = atoi(pstr[i]);
        Serial.println(highScore);
        break;
      case 1:
        lastScore = atoi(pstr[i]);
        break;
      case 2:
        state = atoi(pstr[i]);
        break;
    }
    pstr[i] = strtok(NULL, "&");
  }
  //Serial.println((String)highScore+"  "+lastScore+"  "+state);
}

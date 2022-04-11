#define BLUE 11
#define GREEN 12
#define RED 13


void setup() { //설정 부분, 초기화 기능
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  //pinMode(13, OUTPUT);
}

  void loop() { //프로그램 동작 작성
  // put your main code here, to run repeatedly:
//  for(int i = 0; i< 255; i++){ //PWM 제어 ?
//    analogWrite(RED, i);
//  }
  
  pinMode(RED, HIGH);
  //pinMode(GREEN, LOW);
  //pinMode(BLUE, LOW);
  delay(500); //ms 단위 10^-3
  
  pinMode(RED, LOW);
  //pinMode(GREEN, HIGH);
  //pinMode(BLUE, LOW);
  delay(500);
  
  pinMode(RED, LOW);
  //pinMode(GREEN, LOW);
  //pinMode(BLUE, HIGH);
  delay(500);

  pinMode(RED, HIGH);
  //pinMode(GREEN, HIGH);
  //pinMode(BLUE, HIGH);
  delay(500);
}

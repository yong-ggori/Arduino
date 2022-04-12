#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define LED 6
#define SERVO 11

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.print("test");
  pinMode(A0, INPUT);
  pinMode(LED, OUTPUT);
  myServo.attach(SERVO);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analog_in = analogRead(A0);
  int analog_out = map(analog_in, 0, 1023, 0, 255);//조도센서 범위 조정
  int analog_servo = map(analog_in, 0, 1023, 0, 180);
  
  lcd.setCursor(0, 1); //커서위치 0,1로 설정, 두번째 줄 첫번째 칸
  lcd.print("CDS : "+String(analog_out));
  //lcd.setCursor(6, 1); //커서위치 4,1로 설정
  //lcd.print(analog_out);//조도센서 값 0~255범위로 출력
  delay(50);
 // myServo.write(analog_servo);

  if ((analog_out / 100) >= 1) { //3자리 -> 2자리 마지막 숫자 제거
    lcd.setCursor(8, 1);
    lcd.print(" ");
  }

  lcd.setCursor(10, 1);
  if (analog_out >= 80) { //조도센서 값 80 이상이면 LED ON
    digitalWrite(LED, HIGH);
    lcd.print("LON ");//마지막에 띄어쓰기는 'F'를 없애주기 위함
  }
  else {
    digitalWrite(LED, LOW);//나머지라면 LED OFF
    lcd.print("LOFF");
  }
}

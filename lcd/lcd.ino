#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);//시작 주소?와 lcd 크기 가로x세로(16x2)

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.print("hello! world");
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    lcd.clear();
    delay(100);
    while(Serial.available()>0)
      lcd.write(Serial.read());
  }
//  lcd.setCursor(0,1);//16x2
//  lcd.print("hello, hi!");
}

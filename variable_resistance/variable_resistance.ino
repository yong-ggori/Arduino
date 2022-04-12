void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analog_in = analogRead(A0); // analog_in : 0~1023
                                  //pwm : 0~255
  int analog_out = map(analog_in,0,1023,0,255);//아날로그 값 0~1023의 범위를 0~255로 바꿔준다
  Serial.print(analog_in);
  Serial.print("\t");
  Serial.println(analog_out);
  delay(10);
  analogWrite(10, analog_out);
}

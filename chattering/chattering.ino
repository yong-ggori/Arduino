const int duration = 10000; //1초동안 채터링 현상을 무시, 1초동안 스위치를 아무리 눌러도 반응 안함
unsigned long pre_time = 0;
unsigned long cur_time = 0;
volatile byte state = HIGH;

void isr(){
  cur_time = millis();
  if(cur_time - pre_time >= duration){ //FALLING으로 상태 변화 이후 1초 이상 되었을 때 다시 인터럽트 발생
    Serial.println("인터럽트 발생 !!!");
    digitalWrite(13, state);
    state = !state;
    pre_time = cur_time;
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  attachInterrupt(0, isr, FALLING);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

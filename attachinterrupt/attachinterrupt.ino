volatile byte state = HIGH;

void isr(){
  digitalWrite(13, state);
  state = !state;
  Serial.println(state);
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

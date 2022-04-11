#include <MsTimer2.h>

void isr(){
  static boolean state = HIGH;
  digitalWrite(13, state);
  state = !state;
}

void setup() {
  // put your setup code here, to run once:
  MsTimer2::set(1000, isr);
  MsTimer2::start();
  pinMode(13, OUTPUT);
 // isr();
}

void loop() {
  // put your main code here, to run repeatedly:

}

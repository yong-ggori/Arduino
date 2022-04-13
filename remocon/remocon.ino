#include <IRremote.hpp>

#define r.1 0xFF30CF
#define r.2 0xFF18E7
#define r.3 0xFF7A85
#define r.4 0xFF10EF
#define r.5 0xFF38C7
#define r.6 0xFF5AA5
#define r.7 0xFF42BD
#define r.8 0xFF4AB5
#define r.9 0xFF52AD
#define r.0 0xFF6897
#define r.m 0xFFE01F
#define r.p 0xFFA857

int RECV_PIN = 2;
int pre_value = 0;

IRrecv ir(RECV_PIN);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ir.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (ir.decode(&results)) {
    if (results.value == 0xFFFFFFFF) {
      results.value = pre_value;
    }

    switch (results.value) {
      case r.1:
        pre_value = results.vlaue;
        break;
      case r.2:
        pre_value = results.vlaue;
        break;
      case r.3:
        pre_value = results.vlaue;
        break;
      case r.4:
        pre_value = results.vlaue;
        break;
      case r.5:
        pre_value = results.vlaue;
        break;
      case r.6:
        pre_value = results.vlaue;
        break;
      case r.7:
        pre_value = results.vlaue;
        break;
      case r.8:
        pre_value = results.vlaue;
        break;
      case r.9:
        pre_value = results.vlaue;
        break;
      case r.0:
        pre_value = results.vlaue;
        break;
      case r.m:
        pre_value = results.vlaue;
        break;
      case r.p:
        pre_value = results.vlaue;
        break;
    }

    Serial.println(results.value, HEX);
    ir.resume(); //다음 IR 값 받는다.
  }
}

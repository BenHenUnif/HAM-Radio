/*
OK le 8-fev-2020, Arduino Uno sur COM6
*/

#include <IRremote.h>

const int RECV_PIN = 4;   // le récepteur IR TSOP 4838 utilise la pin D4 comme entrée
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  delay(100);
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
}

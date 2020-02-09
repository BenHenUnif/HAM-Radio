/*
OK le 8-fev-2020, Arduino Uno sur COM6
*/

#include <IRremote.h>

const int RECV_PIN =  4 ;   // le récepteur IR TSOP 4838 utilise la pin D4 comme entrée
const int LED_PIN  = 13 ;   // LED témoin branchée sur la pin D13 via une résistance de 220 ohms
IRrecv irrecv(RECV_PIN);
decode_results results;

/* pour définir plusieurs marques de télécommande, si nécessaire */
#define SONY
//#define TECHNICS
//#define SAMSUNG

#ifdef SONY
  #define BUT_0 0x90B47
  #define BUT_1 0xB47
#endif
#ifdef TECHNICS
  #define BUT_0 0x55098CD
  #define BUT_1 0x550085D
#endif
#ifdef SAMSUNG
  #define BUT_0 0x87FBCA
  #define BUT_1 0x87FBC0
#endif

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  delay(100);
  if (irrecv.decode(&results))
  {
        Serial.println(results.value, HEX);
        irrecv.resume();
        switch (results.value)
        {
          case BUT_0:
            digitalWrite(LED_PIN, LOW);
            break;
          case BUT_1:
            digitalWrite(LED_PIN, HIGH);
            break;
        }
        irrecv.resume();
  }
}


// https://www.aranacorp.com/fr/votre-arduino-communique-avec-le-module-hc-05/
// OK le 08/02/2020 : Arduino Uno sur COM6

#include <SoftwareSerial.h>
#define rxPin 2   // = TX de HC-05
#define txPin 3   // = RX de HC-05 : ne pas utiliser 0 et 1 car sinon problème durant l'upload
#define LED_PIN 13  // Led témoin avec résistance de 220 ohms
#define baudrate 9600
String msg;
SoftwareSerial hc05(rxPin ,txPin);
void setup(){
 pinMode(rxPin,INPUT);
 pinMode(txPin,OUTPUT);
 pinMode(LED_PIN, OUTPUT);
 Serial.begin(9600);
 Serial.println("Pret pour commencer...");
 hc05.begin(baudrate);
}
void loop(){
  int iVal = -99;
  int iDec = -1;
   readSerialPort();
   if(msg!="")
   {
    hc05.println(msg);
   }
   
   if (hc05.available()>0){
     iVal = hc05.read();
     Serial.print("DEBUG 010 valeur recue en CODE ASCII : ");
     Serial.println(iVal);
     if (iVal == 49)
     {
      iDec = atoi(iVal);
      Serial.print("valeur = 49 --> ");
      Serial.println(iDec);
      digitalWrite(LED_PIN, HIGH); 
     }
     else if (iVal == 48)
     {
      iDec = atoi(iVal);
      Serial.print("valeur = 48 --> ");
      Serial.println(iDec);
      digitalWrite(LED_PIN, LOW); 
     }
     else
     {
      //Serial.print("valeur autre que 0 et 1 : ");
     }
   }
}
void readSerialPort(){
 msg="";
while (Serial.available()) {
  delay(10);  
  if (Serial.available() >0) {
    char c = Serial.read();  //gets one byte from serial buffer
    msg += c; //makes the string readString
  }
}
}

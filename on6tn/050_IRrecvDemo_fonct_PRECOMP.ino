
// ON3ZZT - OK on 2020-04-11
// https://www.deviceplus.com/arduino/arduino-preprocessor-directives-tutorial/

/*

Explication des fonctions en C/C++ :
https://fr.wikibooks.org/wiki/Programmation_C/Fonctions_et_proc%C3%A9dures
https://zestedesavoir.com/tutoriels/755/le-langage-c-1/1042_les-bases-du-langage-c/4296_les-fonctions/

Aussi, il faut toujours que le nombre de paramètres soit le même (quand tu définis la fonction, et quand tu l'appelles).
Le type de données, int, float, char, void  doit toujours être le même des 2 côtés.
Et il faut aussi être très vigilant à chaque caractère spécial . , ; ( ) { } - _ 
et le langage C/C++ fait la distinction entre MAJUSCULES et minuscules...

*/


/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>   // recherche le fichier dans les répertoires 'système' ou librairies.
#include "bibi.h"       // recherche le fichier d'abord dans le répertoire 'courant' ensuite le reste.

#define PI4DEC 3.1416
// #undef PI
#ifdef PI
  #warning "Pi est défini"
#else
  #error "Pi non défini !"
#endif

#define X1 10       // dans une mémoire spéciale
const int X2 = 10;  // ne peut pas changer
int X3 = 10;        // dans la mémoire 'traditionnelle'

// prend moins de place en mémoire qu'une fonction 'normale/dynamique'
#ifndef MIN
 #define MIN(A, B)     (((A) < (B)) ? (A) : (B))
#endif
#ifndef MULTIPLY
 #define MULTIPLY(A, B)     ((A) * (B))
#endif
#ifndef SOMME
 #define SOMME(A, B)     ((A) + (B))
#endif

#define ARDUINO_UNO
//#define ARDUINO_NANO
//#define ESP32
//#define WEMOS32

// int result = MULTIPLY(2 - 0, 3);

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
 //this will compile for Arduino UNO, Pro and older boards
 int v_sck  = 13;
 int v_miso = 12;
 int v_mosi = 11;
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
 //this will compile for Arduino Mega
 int v_sck  = 52;
 int v_miso = 50;
 int v_mosi = 51;
#endif

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  int iRes = 0;
  char sRes[100] = "\0";   // tableau de 100 caractères = chaine de caractères, initialisé à 'vide/blanc'

  Serial.begin(9600);
  Serial.println("Début test");

  iRes=somme_bibi(4,5);
  sprintf(sRes, "somme = %d", iRes);   // la fonction 'sprintf' est utilisée pour formatter facilement une chanie de caractères.
  Serial.println(sRes);

  X3=11;
//  X2=11;
//  X1=11;
  
  iRes=multi_bibi(4,5);
  sprintf(sRes, "multi = %d\n", iRes);
  Serial.print(sRes);

/*
  iRes = MULTIPLY(40, 50);
  sprintf(sRes, "MULTIPLY = %d\n", iRes);
  Serial.println(sRes);

  iRes = SOMME(40, 50);
  sprintf(sRes, "SOMME = %d\n", iRes);
  Serial.println(sRes);
*/  

  Serial.println("Fin test");
  Serial.println("=======================================");
  Serial.println("=======================================");
  Serial.println("=======================================");
  
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

/*

Après exécution, le programme affichera quelque chose de semblable à :

Début test
somme = 9
multi = 20
Fin test

*/

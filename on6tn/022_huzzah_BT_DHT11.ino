/*

OK le 8-feb-2020

Adafruit ESP32 Feather on COM8

https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/

*/

/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com
*********/

// Load libraries
#include "BluetoothSerial.h"
//#include <OneWire.h>
//#include <DallasTemperature.h>

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth Serial object
BluetoothSerial SerialBT;

// Import required libraries
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 21     // Digital pin connected to the DHT11 sensor

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

String readDHTTemperature() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float t = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    //Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    //Serial.println(h);
    return String(h);
  }
}

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  return String();
}

// Handle received and sent messages
String message = "";
char incomingChar;
String temperatureString = "";

// Timer: auxiliar variables
unsigned long previousMillis = 0;    // Stores last time temperature was published
const long interval = 10000;         // interval at which to publish sensor readings (10.000 = 10 seconds)

void setup() {
  dht.begin();
  Serial.begin(9600);
  Serial.println("DEBUT :");
  // Bluetooth device name
  SerialBT.begin("ESP32DHT11");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  unsigned long currentMillis = millis();
  // Send temperature readings
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
  Serial.print("temper = ");
  Serial.println(readDHTTemperature().c_str());
    SerialBT.print("temper = "); 
    SerialBT.println(readDHTTemperature().c_str()); 
  Serial.print("humidite = ");
  Serial.println(readDHTHumidity().c_str());
    SerialBT.print("humidite = "); 
    SerialBT.println(readDHTHumidity().c_str()); 
  }
  // Read received messages (LED control command)
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }
  /*
  // Check received message and control output accordingly
  if (message =="led_on"){
    digitalWrite(ledPin, HIGH);
  }
  else if (message =="led_off"){
    digitalWrite(ledPin, LOW);
  }
  */
  delay(1000);
}

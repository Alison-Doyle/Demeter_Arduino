//Importing Libraries
#include "Firebase_Arduino_WiFiNINA.h"

//Pins
int moisturePin = A0;
int lightPin = A1;

//Variables
double currentMoisture = 0;
double currentLight = 0;

void setup() {

  //Initialising Serial @ 9600 bits per second
  Serial.begin(9600);
  
}

void loop() {

  //Fetching Data from Sensor
  currentMoisture = analogRead(moisturePin);
  currentLight = analogRead(lightPin);

  //Writing Data
  Serial.println(moisturePin);
  Serial.println(lightPin);
  
  //Delaying Restart
  delay(1000);
  
}

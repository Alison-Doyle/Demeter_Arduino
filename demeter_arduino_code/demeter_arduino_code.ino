//Importing Firebase Library
#include "Firebase_Arduino_WiFiNINA.h"
#define DATABASE_URL "demeterdb-100d9-default-rtdb.europe-west1.firebasedatabase.app/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define DATABASE_SECRET "SECRET_SOMETHING"
#define WIFI_SSID "YOUR_WIFI_AP"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

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

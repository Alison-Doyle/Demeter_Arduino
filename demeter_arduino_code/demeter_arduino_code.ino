//Importing Firebase Library
#include "Firebase_Arduino_WiFiNINA.h"
#define DATABASE_URL "demeterdb-100d9-default-rtdb.europe-west1.firebasedatabase.app/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define DATABASE_SECRET "Mbv7CFfRPZfRRVMn1OdOHTmjDpFLHxVyLtYKsHtD"
#define WIFI_SSID "Vodafone-Guest"
#define WIFI_PASSWORD "JBBDMX884K2D7EEK"

//Pins
int moisturePin = A0;
int lightPin = A1;

//Variables
double currentMoisture = 0;
double currentLight = 0;

FirebaseData fbdo;

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

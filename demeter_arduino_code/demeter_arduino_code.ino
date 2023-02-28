//Including Firebase Library
#include "Firebase_Arduino_WiFiNINA.h"
#define DATABASE_URL "demeterdb-100d9-default-rtdb.europe-west1.firebasedatabase.app/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define DATABASE_SECRET "Mbv7CFfRPZfRRVMn1OdOHTmjDpFLHxVyLtYKsHtD"
#define WIFI_SSID "Alison's Phone"
#define WIFI_PASSWORD "IWantADirtNap"

//Other Libraries
#include <WiFiNINA.h>

//Pins
float moisturePin = A0;
float lightPin = A1;

//Variables
double currentMoisture = 0;
double currentLight = 0;

String moisturePath = "/Current Data/Moisture";
String lightPath = "/Current Data/UV";

const String currentDataPath = "/Current Data";

FirebaseData fbdo;

//Arduino Setup
void setup() {

  //Initialising Serial @ 9600 bits per second
  Serial.begin(9600);

  //Letting User Know arduino is being set up
  delay(2000);
  Serial.println("Setting up arduino... Please wait a moment");

  //Trying to connect to internet
  Serial.print("Connecting to WiFi...");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }

  //Providing Authentification Data for Firebase
  Firebase.begin(DATABASE_URL, DATABASE_SECRET, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
  
}

void loop() {

  //Fetching Data from Sensor
  currentMoisture = analogRead(moisturePin);
  currentLight = analogRead(lightPin);

  //Writing Data in Serial
  Serial.println(currentMoisture);
  Serial.println(currentLight);

  //Sending Data to Firebase
  Firebase.setFloat(fbdo, moisturePath, currentMoisture);
  Firebase.setFloat(fbdo, lightPath, currentLight);
  
  //Delaying Restart
  delay(1000);
  
}

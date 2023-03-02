//Including Firebase Library
#include "Firebase_Arduino_WiFiNINA.h"
#define DATABASE_URL "demeterdb-100d9-default-rtdb.europe-west1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define DATABASE_SECRET "sLwXYSlP8Art2uemSScOvYGDmKO2MrGKjDQ1Oxnq"
#define WIFI_SSID "Alison's Phone"
#define WIFI_PASSWORD "IWantADirtNap"

//Other Libraries
#include <WiFiNINA.h>

//Pins
float moisturePin = A0;
float lightPin = 8;

//Variables
double currentMoisture = 0;
double currentLight = 0;

String moisturePath = "/Current Data/Moisture";
String lightPath = "/Current Data/UV";

int value = 0;

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
  currentLight = digitalRead(lightPin);

  //Writing Data in Serial
  Serial.println(currentMoisture);
  Serial.println(currentLight);

  //Sending Moisture to Firebase
  if (Firebase.setInt(fbdo, "/test/int", 1234)) 
  {
    
    if (fbdo.dataType() == "int") 
    {
      value = fbdo.intData();
      Serial.println(value);
    }

  }
  else 
  {
    //Failed, then print out the error detail
    Serial.println(fbdo.errorReason());
  }

  if (Firebase.setInt(fbdo, "/test/int", 1234)) 
  {
    
    if (fbdo.dataType() == "int") 
    {
      value = fbdo.intData();
      Serial.println(value);
    }

  }
  else 
  {
    //Failed, then print out the error detail
    Serial.println(fbdo.errorReason());
  }
  
  //Delaying Restart
  delay(1000);
  
}

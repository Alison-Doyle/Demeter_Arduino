//Libraries
#include "Firebase_Arduino_WiFiNINA.h"
#include <WiFiNINA.h>
#include "Si115X.h"

//Setting Up Libraries
#define DATABASE_URL "demeterdb-100d9-default-rtdb.europe-west1.firebasedatabase.app"
#define DATABASE_SECRET "sLwXYSlP8Art2uemSScOvYGDmKO2MrGKjDQ1Oxnq"
#define WIFI_SSID "Alison's Phone"
#define WIFI_PASSWORD "IWantADirtNap"
FirebaseData fbdo;

Si115X si1151;

//Pins
float moisturePin = A0;

//Variables
int moistureLevel = 0;
int lightLevel = 0;
int value = 0;
int minuteCounter = 0;
int hourCounter = 0;
uint8_t conf[4];

const String currentMoisturePath = "/Moisture";
const String currentLightPath = "/Light";

void setup()
{

  //Initialising serial
  Serial.begin(9600);

  //Trying To Connect to Internet
  Serial.print("Connecting to WiFi...");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }

  Serial.println("");
  
  //Connecting to Firebase Database
  Firebase.begin(DATABASE_URL, DATABASE_SECRET, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);

  //Tring to start up sunlight sensor
  Serial.print("Connecting to Sunlight Sensor...");
  while(!si1151.Begin())
  {
    Serial.print(".");
    delay(300);
  }

  Serial.println("");
  
}

void loop()
{

  //Fetching Data From Sensors
  moistureLevel = analogRead(moisturePin);
  lightLevel = si1151.ReadHalfWord_VISIBLE();

  //Writing Data in serial
  Serial.print("Moisture Level: ");
  Serial.println(moistureLevel);
  Serial.print("Light Level: ");
  Serial.println(lightLevel);

  //Sending Moisture to Firebase
  if (Firebase.setInt(fbdo, currentMoisturePath, moistureLevel)) 
  {
  }
  else 
  {
    //Failed, then print out the error detail
    Serial.println(fbdo.errorReason());
  }

  //Sending UV to Firebase
  if (Firebase.setInt(fbdo, currentLightPath, lightLevel)) 
  {
  }
  else 
  {
    //Failed, then print out the error detail
    Serial.println(fbdo.errorReason());
  }

  minuteCounter += 5;
  hourCounter += 1;

  //Delaying Resatrt of Loop
  delay(1000);

}

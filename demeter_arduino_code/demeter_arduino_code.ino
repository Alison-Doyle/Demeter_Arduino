//Libraries
#include "arduino_secrets.h"
#include "Firebase_Arduino_WiFiNINA.h"
#include <WiFiNINA.h>
#include "Si115X.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//Setting Up Libraries
#define DATABASE_URL SECRET_DATABASEURL
#define DATABASE_SECRET SECRET_DATABASESECRET
#define WIFI_SSID SECRET_Internet
#define WIFI_PASSWORD SECRET_InternetPassword
FirebaseData fbdo;

Si115X si1151;

#define LED_PIN     6 //Where LEDs get info
#define LED_COUNT  25 //No. LEDs
#define BRIGHTNESS 50
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

//Pins
float moisturePin = A0;

//Variables
int moistureLevel = 0;
int lightLevel = 0;
int minLightLevel;
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

  //Starting LED
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  
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

  //Reading In min Light Level for Plant
  if (Firebase.getInt(fbdo, "/plantSettings/minLightLevel")) 
  {
    //If data is valid, assign it to minLightLevel
    if (fbdo.dataType() == "int") 
    {
      minLightLevel = fbdo.intData();
      Serial.println(minLightLevel);
    }
  } 
  else 
  {
    //Failed, then print out the error detail
    Serial.println(fbdo.errorReason());
  }

  //Turning on Lights if Light is Low
  if (lightLevel <= minLightLevel)
  {
    colorWipe(strip.Color(255, 255, 255), 50);
  }
  else if (lightLevel > minLightLevel)
  {
    colorWipe(strip.Color(0,   0,   0), 50);
  }

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

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

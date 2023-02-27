//Pins
int tempPin = A0;

//Variables
double current_temp = 0;

void setup() {

  //Initialising Serial @ 9600 bits per second
  Serial.begin(9600);
  
}

void loop() {

  //Fetching Data from Sensor
  current_temp = analogRead(tempPin);

  //Writing Data
  Serial.println(current_temp/20);
  
  //Delaying Restart
  delay(1000);
  
}

void setup() {
  
  Serial.begin(9600);

}

void loop() {

  //Read in vlaues from sensors
  int moistureValue = analogRead(A0);
  int uvValue = analogRead(A1);
  
  //Print Out Values
  Serial.println(moistureValue);
  delay(1000);
  
}

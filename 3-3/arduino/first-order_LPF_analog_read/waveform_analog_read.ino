int sensorPin = A0;   // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
float xn1 = 0; // = x[n-1]
float yn1 = 0; // = y[n-1]
void setup() {
  Serial.begin(115200);
}
float xpp=0;
float ypp = 0
void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  float xn = sensorValue;
  float yn = 0.969*yn1 + 0.01546*xn + 0.01546*xn1; 
  xn1 = xn;
  yn1 = yn;  
  Serial.print(sensorValue);
  Serial.print(" ");  
  Serial.println(yn);
  delay(1); 
  
}

void setup() {
   Serial.begin(9600);
}

void loop() {
  float t = micros()/1.0e6;
  float xn = sin(2*PI*1*t);
  delay(100);
  Serial.println(xn);
}

float xn1 = 0; // = x[n-1]
float xn2 = 0; // = x[n-2]
float xn3 = 0; // = x[n-3]
float xn4 = 0; // = x[n-4]
float yn1 = 0; // = y[n-1]
float yn2 = 0; // = y[n-2]
float yn3 = 0; // = y[n-3]
float yn4 = 0; // = y[n-4]
void setup() {
  Serial.begin(115200);
}

void loop() {
  float t = micros()/1.0e6; //取得即時秒數
  float xn = sin(2*PI*2*t) + sin(2*PI*50*t); //計算1Hz正弦波的瞬間值
  float yn = 3.91791462*yn1 - 5.75709608*yn2 + 3.76036868*yn3 - 0.92118815*yn4
  + 5.84323939e-08*xn + 2.33729577e-07*xn1 + 3.50594359e-07*xn2 + 2.33729580e-07*xn3 + 5.84323925e-08*xn4; 
  xn4 = xn3;
  xn3 = xn2;
  xn2 = xn1;
  xn1 = xn;
  yn4 = yn3;
  yn3 = yn2;
  yn2 = yn1;
  yn1 = yn;  
  Serial.print(xn);
  Serial.print(" ");  
  Serial.println(yn);
  delay(1); 
}

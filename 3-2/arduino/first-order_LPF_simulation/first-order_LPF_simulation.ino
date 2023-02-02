float xn1 = 0; // = x[n-1]
float yn1 = 0; // = y[n-1]
void setup() {
  Serial.begin(115200);
}

void loop() {
  float t = micros()/1.0e6; //取得即時秒數
  float xn = sin(2*PI*2*t) + sin(2*PI*50*t); //計算1Hz正弦波的瞬間值
  float yn = 0.969*yn1 + 0.01546*xn + 0.01546*xn1; 
  xn1 = xn;
  yn1 = yn;  
  Serial.print(xn);
  Serial.print(" ");  
  Serial.println(yn);
  delay(1); 
}

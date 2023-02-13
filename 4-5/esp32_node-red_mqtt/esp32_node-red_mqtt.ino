#include <SimpleDHT.h> //引入SimpleDHT函式庫
#include <WiFi.h>  //引入Wi-Fi函式庫，讓ESP32能連接wifi
#include <PubSubClient.h>

#define ledPin (gpio_num_t)12
int pinDHT = 15;  //GPIO15腳位宣告
SimpleDHT11 dht11(pinDHT);  // 建立DHT11感測器物件
char ssid[] = “<你的Wi-Fi SSID>”;  
char pass[] = “<你的Wi-Fi密碼>”; 
const char* mqtt_server = "<你的樹莓派IP位址>";
WiFiClient  espClient; //創建一個WiFiClient物件去連接ThingSpeak
PubSubClient client(espClient);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //baud rate設為9600bps
  gpio_pad_select_gpio(ledPin); //選擇GPIO12
  gpio_set_direction(ledPin, GPIO_MODE_OUTPUT);  //將GPIO12設為輸出
  //設定將ESP32的WI-FI模式設為STA模式，可以連接WI-FI基地
  //台，另一模式為AP模式，可以點對點連接
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);  //連接指定的WI-FI基地台
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("IP address:");
  Serial.println(WiFi.localIP()); //串列印出Local IP位址
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("message arrived, topic: ");
  Serial.print(topic);
  Serial.print(". message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i]; //將接收訊息拷貝至messageTemp
  }
  // 若主題是esp32/output，則判斷訊息內容，若為”on”，則開啟LED燈，若為”on”，則關閉LED燈
  if (String(topic) == "esp32/output") {
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }
}
//重新連線MQTT伺服器函式
void reconnect() {  
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("connecting…");
    // 重新連接MQTT伺服器
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // 訂閱esp32/output主題
      client.subscribe("esp32/output");
    } else {
      Serial.print("connect failed, status code:");
      Serial.print(client.state());
      Serial.println("connect again in 5 seconds...");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  //若讀取DHT11感測器器發生錯誤，則串列印出錯誤訊息，延遲1秒後重新讀取
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); 
    Serial.println(err); 
    delay(1000); 
    return;
  }
  //串列印出溫濕度值
  Serial.print("DHT11 Sample OK: ");
  Serial.print((int)temperature); Serial.print(" degree, "); 
  Serial.print((int)humidity); Serial.println(" %");  
  //若MQTT斷線，則重新連接
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // 將溫度轉換成字串，並發佈溫度訊息
  char tempString[8];
  dtostrf((double)temperature, 1, 2, tempString);
  Serial.print("Temperature: ");
  Serial.println(tempString);
  client.publish("esp32/temperature", tempString);
    
  // 將濕度轉換成字串，並發佈濕度訊息
  char humString[8];
  dtostrf((double)humidity, 1, 2, humString);
  Serial.print("Humidity: ");
  Serial.println(humString);
  client.publish("esp32/humidity", humString);
  delay(2000); //每隔2杪重新執行loop函式
}


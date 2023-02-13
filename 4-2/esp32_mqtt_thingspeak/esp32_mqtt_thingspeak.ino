#include <SimpleDHT.h> //引入SimpleDHT函式庫
#include "ThingSpeak.h" //引入ThingSpeak函式庫
#include <WiFi.h>  //引入Wi-Fi函式庫，讓ESP32能連接wifi
#include <PubSubClient.h>

#define BLINK_GPIO (gpio_num_t)12
int pinDHT = 15;  //GPIO15腳位宣告
SimpleDHT11 dht11(pinDHT);  // 建立DHT11感測器物件
unsigned long myChannelNumber = <你的Channel Number>;
const char * myWriteAPIKey = "<你的Write API Key>";
const char * myReadAPIKey = "<你的Read API Key>";
char ssid[] =  “<你的Wi-Fi SSID>”;  
char pass[] = “<你的Wi-Fi密碼>”;  
WiFiClient  client; //創建一個WiFiClient物件去連接ThingSpeak

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //baud rate設為9600bps
  gpio_pad_select_gpio(BLINK_GPIO); //選擇GPIO12
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);  //將GPIO12設為輸出
  //設定將ESP32的WI-FI模式設為STA模式，可以連接WI-FI基地
  //台，另一模式為AP模式，可以點對點連接
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);  //連接指定的WI-FI基地台
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("IP address:");
  Serial.println(WiFi.localIP()); //串列印出Local IP位址
  ThingSpeak.begin(client); //初始化ThingSpeak物件
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
  //延遲15秒
  vTaskDelay(15000 / portTICK_PERIOD_MS); 
  //MQTT發佈溫濕度值
  ThingSpeak.setField(2, (int)temperature);
  ThingSpeak.setField(3, (int)humidity);
  int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  //若發佈成功，則串列印出Channel write successful.
  if (httpCode == 200) {
    Serial.println("Channel write successful.");
  }
  //若發佈不成功，則串列印出錯誤訊息
  else {
    Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
  }
  // 訂閱LED開關訊息
  long led_status = ThingSpeak.readLongField(myChannelNumber, 1, myReadAPIKey);  
  httpCode = ThingSpeak.getLastReadStatus();
  //若讀取成功，則串列印出LED開關狀態資訊
  if(httpCode == 200){ 
    Serial.println("led_status: " + String(led_status));
    //若讀取的LED開關狀態為1，則開啟LED
    if (led_status == 1)
       gpio_set_level(BLINK_GPIO, 1);
    //若讀取的LED開關狀態為0，則關閉LED
    else if (led_status == 0)
       gpio_set_level(BLINK_GPIO, 0);
  }
  //若讀取失敗，則串列印出錯誤訊息
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(httpCode)); 
  }  
}

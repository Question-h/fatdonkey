#include <WiFi.h>
#include <esp_now.h>

// 引脚编号
#define ADC0  0
#define ADC1  1
#define ADC2  2
#define ADC3  3
#define ADC4  4
#define ADC5  5

#define IO6  6
#define IO7  7
#define IO8  8
#define IO9  9
#define IO10  10
#define IO20  20
#define IO21  21



// 设置数据结构体
//5 adc 8io
typedef struct struct_message 
{
  double adc0;
  double adc1;
  double adc2;
  double adc3;
  double adc4;
  double adc5;
  bool io6;
  bool io7;
  bool io8;
  bool io9;
  bool io10;
  bool io20;
  bool io21;
  //String board_name;
} struct_message;

struct_message myData;

// 接收设备的 MAC 地址
uint8_t broadcastAddress[] = {0x84, 0xf7, 0x03, 0xbd, 0x15,0xd8};
//84:F7:03:BD:15:D8
//84:F7:03:41:D0:94

// 数据发送回调函数
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  //Serial.print("Packet to: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
           /*
  Serial.println(macStr);
  Serial.print("Send status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  Serial.println();
  */
}

void setup() {
  Serial.begin(115200);

  // 初始化 ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
    Serial.print("STA MAC: "); Serial.println(WiFi.macAddress());

  // 设置发送数据回调函数
  esp_now_register_send_cb(OnDataSent);

  // 绑定数据接收端
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // 检查设备是否配对成功
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  pinMode(IO6 , INPUT_PULLUP);
  pinMode(IO7, INPUT_PULLUP); 
  pinMode(IO8 , INPUT_PULLUP);
  pinMode(IO9 , INPUT_PULLUP); 
  pinMode(IO10 , INPUT_PULLUP);
  pinMode(IO20 , INPUT_PULLUP);
  pinMode(IO21 , INPUT_PULLUP);
}

void loop() {
  // 设置要发送的数据
  //myData.board_name = "Fat Donkey";
  
  myData.adc0 = analogRead(ADC0);
  
  myData.adc1 = analogRead(ADC1);
  myData.adc2 = analogRead(ADC2);
  myData.adc3 = analogRead(ADC3);
  myData.adc4 = analogRead(ADC4);
  myData.adc5 = analogRead(ADC5);
  myData.io6 = digitalRead(IO6);
  myData.io7 = digitalRead(IO7);
  myData.io8 = digitalRead(IO8);
  myData.io9 = digitalRead(IO9);
  myData.io10 = digitalRead(IO10);
  myData.io20 = digitalRead(IO20);
  myData.io21 = digitalRead(IO21);
  
  /*
  Serial.print(myData.adc0);
  Serial.print(",");
  Serial.print(myData.adc1);
  Serial.print(",");
  Serial.print(myData.adc2);
  Serial.print(",");
  Serial.print(myData.adc3);
  Serial.print(",");
  Serial.print(myData.adc4);
  Serial.print(",");
  Serial.println(myData.adc5);
  
  Serial.print("IO6:");
  Serial.print(myData.io6);
  Serial.print(",");
  Serial.print("IO7:");
  Serial.print(myData.io7);
  Serial.print(",");
  Serial.print("IO8:");
  Serial.print(myData.io8);
  Serial.print(",");
  Serial.print("IO9:");
  Serial.print(myData.io9);
  Serial.print(",");
  Serial.print("IO10:");
  Serial.print(myData.io10);
  Serial.print(",");
  Serial.print("IO20:");
  Serial.print(myData.io20);
  Serial.print(",");
  Serial.print("IO21:");
  Serial.println(myData.io21);
  */
  
  
  // 发送数据
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  // 检查数据是否发送成功
  if (result == ESP_OK) {
    //Serial.println("Sent with success");
  }
  else {
    //Serial.println("Error sending the data");
  }

  //delay(100);
}

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

// 数据接收回调函数
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  //Serial.print("board_name: ");
  //Serial.println(myData.board_name);
  Serial.print("ADC0: ");
  Serial.println(myData.adc0);
  Serial.print("ADC1: ");
  Serial.println(myData.adc1);
  Serial.print("ADC2: ");
  Serial.println(myData.adc2);
  Serial.print("ADC3: ");
  Serial.println(myData.adc3);
  Serial.print("ADC4: ");
  Serial.println(myData.adc4);
  Serial.print("ADC5: ");
  Serial.println(myData.adc5);
  Serial.println();
}

void setup() {
  Serial.begin(9600);

  // 初始化 ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // 设置接收数据回调函数
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}

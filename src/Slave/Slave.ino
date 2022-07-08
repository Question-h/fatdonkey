#include <WiFi.h>
#include <esp_now.h>

#if !defined( ARDUINO_ESP32C3_DEV )
  #error This code is intended to run on the ESP32_C3 platform! Please check your Tools->Board setting.
#endif

#define TIMER_INTERRUPT_DEBUG       1
#define ISR_SERVO_DEBUG             1

// Select different ESP32 timer number (0-1) to avoid conflict
#define USE_ESP32_TIMER_NO          1
#include "ESP32_C3_ISR_Servo.h"

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

// Published values for SG90 servos; adjust if needed
#define MIN_MICROS      800  //544
#define MAX_MICROS      2450

int servoIndex0  = -1;
int servoIndex1  = -1;
int servoIndex2 = -1;
int servoIndex3  = -1;
int servoIndex4  = -1;
int servoIndex5  = -1;


// 数据接收回调函数
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  //Serial.print("board_name: ");
  //Serial.println(myData.board_name);
  int pulseWidth=0;
  ESP32_ISR_Servos.setPulseWidth(servoIndex0, pulseWidth);
  ESP32_ISR_Servos.setPulseWidth(servoIndex1, pulseWidth);
  ESP32_ISR_Servos.setPulseWidth(servoIndex2, pulseWidth);
  ESP32_ISR_Servos.setPulseWidth(servoIndex3, pulseWidth);
  ESP32_ISR_Servos.setPulseWidth(servoIndex4, pulseWidth);
  ESP32_ISR_Servos.setPulseWidth(servoIndex5, pulseWidth);
 
  digitalWrite(IO6,myData.io6);
  digitalWrite(IO7,myData.io7);
  digitalWrite(IO8,myData.io8);
  digitalWrite(IO9,myData.io9);
  digitalWrite(IO10,myData.io10);
  digitalWrite(IO20,myData.io20);
  digitalWrite(IO21,myData.io21);
  
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

  Serial.print("IO6: ");
  Serial.println(myData.io6);
  Serial.print("IO7: ");
  Serial.println(myData.io7);
  Serial.print("IO8: ");
  Serial.println(myData.io8);
  Serial.print("IO9: ");
  Serial.println(myData.io9);
  Serial.print("IO10: ");
  Serial.println(myData.io10);
  Serial.print("IO20: ");
  Serial.println(myData.io20);
  Serial.print("IO21: ");
  Serial.println(myData.io21);
  
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

  ESP32_ISR_Servos.useTimer(USE_ESP32_TIMER_NO);

  servoIndex0 = ESP32_ISR_Servos.setupServo(ADC0, MIN_MICROS, MAX_MICROS);
  servoIndex1 = ESP32_ISR_Servos.setupServo(ADC1, MIN_MICROS, MAX_MICROS);
  servoIndex2 = ESP32_ISR_Servos.setupServo(ADC2, MIN_MICROS, MAX_MICROS);
  servoIndex3 = ESP32_ISR_Servos.setupServo(ADC3, MIN_MICROS, MAX_MICROS);
  servoIndex4 = ESP32_ISR_Servos.setupServo(ADC4, MIN_MICROS, MAX_MICROS);
  servoIndex5 = ESP32_ISR_Servos.setupServo(ADC5, MIN_MICROS, MAX_MICROS);

  
  pinMode(IO6 , OUTPUT);
  pinMode(IO7, OUTPUT); 
  pinMode(IO8 , OUTPUT);
  pinMode(IO9 , OUTPUT); 
  pinMode(IO10 , OUTPUT);
  pinMode(IO20 , OUTPUT);
  pinMode(IO21 , OUTPUT);


}

void loop() {

  //ESP32_ISR_Servos.setPosition(servoIndex1, position);
  //setPulseWidth(servoIndex1, uint16_t& pulseWidth);
}

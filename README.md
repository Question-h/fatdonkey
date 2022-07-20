# 肥驴遥控



## 源起

乐鑫发布了新的espnow通信协议，想尝试下，就有了这个小项目。

## 特征

无





## 舵机库源码

#define TIMER_INTERVAL_MICRO        10

```c
bool ESP32_ISR_Servo::setPulseWidth(const uint8_t& servoIndex, uint16_t& pulseWidth)
{
  if (servoIndex >= MAX_SERVOS)
    return false;

  // Updates interval of existing specified servo
  if ( servo[servoIndex].enabled && (servo[servoIndex].pin <= ESP32_MAX_PIN) )
  {
    if (pulseWidth < servo[servoIndex].min)
      pulseWidth = servo[servoIndex].min;
    else if (pulseWidth > servo[servoIndex].max)
      pulseWidth = servo[servoIndex].max;

    // ESP32 is a multi core / multi processing chip.
    // It is mandatory to disable task switches during modifying shared vars
    portENTER_CRITICAL(&timerMux);

    servo[servoIndex].count     = pulseWidth / TIMER_INTERVAL_MICRO;
    servo[servoIndex].position  = map(pulseWidth, servo[servoIndex].min, servo[servoIndex].max, 0, 180);

    // ESP32 is a multi core / multi processing chip.
    // It is mandatory to disable task switches during modifying shared vars
    portEXIT_CRITICAL(&timerMux);

    ISR_SERVO_LOGERROR1("Idx =", servoIndex);
    ISR_SERVO_LOGERROR3("cnt =", servo[servoIndex].count, ", pos =",servo[servoIndex].position);

    return true;
  }

  // false return for non-used numServo or bad pin
  return false;
}
```



```c
bool ESP32_ISR_Servo::setPosition(const uint8_t& servoIndex, const uint16_t& position)
{
  if (servoIndex >= MAX_SERVOS)
    return false;

  // Updates interval of existing specified servo
  if ( servo[servoIndex].enabled && (servo[servoIndex].pin <= ESP32_MAX_PIN) )
  {
    // ESP32 is a multi core / multi processing chip.
    // It is mandatory to disable task switches during modifying shared vars
    portENTER_CRITICAL(&timerMux);

    servo[servoIndex].position  = position;
    servo[servoIndex].count     = map(position, 0, 180, servo[servoIndex].min, servo[servoIndex].max) / TIMER_INTERVAL_MICRO;

    // ESP32 is a multi core / multi processing chip.
    // It is mandatory to disable task switches during modifying shared vars
    portEXIT_CRITICAL(&timerMux);

    ISR_SERVO_LOGERROR1("Idx =", servoIndex);
    ISR_SERVO_LOGERROR3("cnt =", servo[servoIndex].count, ", pos =",servo[servoIndex].position);

    return true;
  }

  // false return for non-used numServo or bad pin
  return false;
}



```





感谢：

dfrobot提供的板子：https://wiki.dfrobot.com.cn/_SKU_DFR0868_Beetle_ESP32_C3#target_5

舵机开源库：https://github.com/khoih-prog/ESP32_ISR_Servo


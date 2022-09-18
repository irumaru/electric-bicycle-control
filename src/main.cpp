/**
 * @file main.cpp
 * @author Irumaru
 * @brief setup()及びloop()のあるメインのコード
 * @version 0.1
 */

#include "main.h"

int motorControlSetup();
void motorController(void);
uint8_t getDriveOutput();

//debug
int adcStatus;

void setup() {
  delay(500);

  //debug
  Serial.begin(115200);

  //ADCの初期化
  adcStatus = adcBegin();

  speedometerSetup();

  //モニタの初期化
  tftInit();
  tftViewInit();

  //----コントローラ開始----
  motorControlSetup();
}

void loop() {
  //Debug
  //Serial.printf("adcBeginStatus = %d\n", adcStatus);

  //モニタ出力
  
  //速度
  tftShowSpeed(getSpeed());
  
  //電気的情報
  tftViewOutput(getDriveOutput());
  tftViewCurrent(map(getCurrent(), 0, DRIVE_CURRENT_LIMIT, 0, 100));
  tftViewBattery(getBatteryPercent());
  
  //温度的情報
  tftViewDriverTemp(getTemp(ADC_CH_OF_DRIVE_TEMP));
  tftViewMotorTemp(getTemp(ADC_CH_OF_MOTOR_TEMP));
  
  delay(DISPLAY_LOOP_INTERVAL);
}

//グローバル変数
uint16_t duty = 0;
/**
 * @brief モータコントロールの開始
 * @return int 正常時1
 */
void motorController(void *);
int motorControlSetup()
{
  //PWMチャンネルの初期化
  ledcSetup(DRIVE_PWM_CH, DRIVE_PWM_FREQ, DRIVE_PWM_RESO);
  //PWMピンの初期化
  pinMode(IO_PIN_OF_DRIVE, OUTPUT);
  ledcAttachPin(IO_PIN_OF_DRIVE, DRIVE_PWM_CH);

  //モータ連続制御の開始
  xTaskCreatePinnedToCore(motorController, "motorController", 4096, NULL, 1, NULL, 1);

  return 0;
}
/**
 * @brief モータコントローラー
 * @param arg xTask引数
 */
void motorController(void *arg)
{
  uint16_t target;
  uint16_t current;
  uint16_t targetInverse;
  while(true)
  {
    //出力目標
    target = getThrottle();

    //debug
    //Serial.printf("Throttle: %d\n", target);
  
    //速度制限
    if(!getSpeedAllow())
    {
      //出力停止
      target = 0;
    }

    //電流制限
    current = map(getCurrent(), 0, DRIVE_CURRENT_LIMIT, 0, 1000);
    if(1000 < current)
    {
      targetInverse = constrain((current - 1000), 0, DRIVE_CURRENT_LIMIT_OVER) * (4095 / DRIVE_CURRENT_LIMIT_OVER);
      target = constrain(target - targetInverse, 0, 4095);
    }

    //出力計算
    if(duty + 8 < target)
    {
      duty = constrain(duty + 8, 0, 4095);
    }
    else if(target - 8 < duty)
    {
      duty = constrain(duty - 8, 0, 4095);
    }
  
    //モータドライブ
    ledcWrite(DRIVE_PWM_CH, duty);

    //遅延
    delayMicroseconds((DRIVE_0to100_TIME*1000) / (4096/8));
  }
}
/**
 * @brief 現在の出力(PWM Duty比)を取得
 * @return uint8_t 出力[%]
 */
uint8_t getDriveOutput()
{
  return map(duty, 0, 4095, 0, 100);
}
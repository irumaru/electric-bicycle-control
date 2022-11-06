#include <Arduino.h>
#include "adc_hq.c"

//電圧監視
#define VOLTAGE_PIN 32
#define VOLTAGE_MAX 29400
#define VOLTAGE_LOW 21000
#define VOLTAGE_MAX_MARGIN 4 //値-5%
//温度監視
#define TEMP_PIN 33
#define TEMP_MAX 60
//制御ピン
#define POWER_PIN 25
//スイッチピン
#define SW_PIN 26

//プロトタイプ宣言
void updateVolts();
void chargeControl(bool);
int chargeStatus();

//グローバル変数宣言
int BatteryVolts, BatteryPercent;

#define CHARGE_MAX VOLTAGE_MAX - (((VOLTAGE_MAX - VOLTAGE_LOW) / 100) * VOLTAGE_MAX_MARGIN)

void setup() {
  //ピンの初期化
  pinMode(VOLTAGE_PIN, ANALOG);
  pinMode(POWER_PIN, OUTPUT);
  pinMode(SW_PIN, INPUT);

  //出力リレーをオフにする
  chargeControl(false);

  //表示初期化
  Serial.begin(115200);
}

void loop() {
  //遅延
  delay(1000);
  
  //スイッチ
  while(true)
  {
    updateVolts();
    Serial.printf("充電開始待ち, 電圧: %.2fV, 容量: %d%%\n", (float)BatteryVolts/1000, BatteryPercent);
    if(digitalRead(SW_PIN))
    {
      break;
    }
    delay(1000);
  }

  //充電
  updateVolts();
  Serial.printf("充電開始, 電圧: %.2fV, 容量: %d%%\n", (float)BatteryVolts/1000, BatteryPercent);
  while(true)
  {
    //電圧チェック
    if((VOLTAGE_LOW <= BatteryVolts)&&(BatteryVolts <= CHARGE_MAX))
    {
      //充電
      chargeControl(true);
      delay(1000);
      //電圧値更新
      updateVolts();
      Serial.printf("充電中, 電圧: %.2fV, 容量: %d%%\n", (float)BatteryVolts/1000, BatteryPercent);
    }
    else
    {
      //充電停止
      chargeControl(false);
      //電圧チェック待ち
      Serial.printf("充電完了! 電圧チェック待ち");
      delay(10000);
      //電圧チェック
      updateVolts();
      Serial.printf(" 電圧: %.2fV, 容量: %d%%\n", (float)BatteryVolts/1000, BatteryPercent);
      break;
    }
  }
}

//電圧監視
void updateVolts()
{
  //電圧の監視
  uint16_t raw = analogReadHighQuality(VOLTAGE_PIN);
  //Serial.println(raw);
  BatteryVolts = map(raw, 0, 2900, 0, 27400);
  BatteryPercent = constrain(map(BatteryVolts, 21000, 29400, 0, 100), -1, 1000);
}

//充電コントロール
void chargeControl(bool Set)
{
  digitalWrite(POWER_PIN, Set);
}
int chargeStatus()
{
  return !digitalRead(POWER_PIN);
}

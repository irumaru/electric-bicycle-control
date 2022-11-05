#include "tft.h"

//文字の定義
#define FS9  &FreeSans9pt7b
#define FS12 &FreeSans12pt7b
#define FS18 &FreeSans18pt7b
#define FS24 &FreeSans24pt7b

//tft構造体
TFT_eSPI tft = TFT_eSPI();

//tft初期化
void tftInit()
{
  //TFT初期化
  tft.begin();
  tft.setRotation(3);
}

void tftViewInit()
{
  //w: 320, h:240
  //背景の色
  tft.fillScreen(TFT_BLACK);

  //----速度表示----
  //文字・背景の色
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  //フォント
  tft.setFreeFont(FS24);
  //文字サイズ
  tft.setTextSize(1);
  //文字の出力
  tft.drawString("km/h", 160, 60);


  //----線----
  //文字・背景の色
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  //フォント
  tft.setFreeFont(FS12);
  //文字サイズ
  tft.setTextSize(1);
  //文字の出力
  tft.drawString("-------------------------------------", 10, 120);
}

//速度
void tftShowSpeed(uint8_t Speed)
{
  //----速度表示----
  //初期化
  tft.fillRect(50, 25, 110, 100, TFT_BLACK);
  //文字・背景の色
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //フォント
  tft.setFreeFont(FS24);
  //文字サイズ
  tft.setTextSize(2);
  //文字の出力
  tft.drawString(String(Speed), 50, 25);
}

void tftViewOutput(uint8_t Output)
{
  //初期化
  tft.fillRect(10, 150, 150, 20, TFT_BLACK);
  //文字・背景の色
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //フォント
  tft.setFreeFont(FS12);
  //文字サイズ
  tft.setTextSize(1);
  //文字の出力
  tft.drawString("Output: " + String(Output) + "%", 10, 150, 1);
}

void tftViewCurrent(uint16_t Current)
{
  //初期化
  tft.fillRect(10, 180, 150, 20, TFT_BLACK);
  //文字・背景の色
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //フォント
  tft.setFreeFont(FS12);
  //文字サイズ
  tft.setTextSize(1);
  //文字の出力
  tft.drawString("Current: " + String(Current) + "%", 10, 180);
}

void tftViewBattery(uint8_t Capacity)
{
  //初期化
  tft.fillRect(10, 210, 150, 20, TFT_BLACK);
  //文字・背景の色
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //フォント
  tft.setFreeFont(FS12);
  //文字サイズ
  tft.setTextSize(1);
  //文字の出力
  tft.drawString("Battery: " + String(Capacity) + "%", 10, 210);
}

void tftViewBatteryTemp(uint8_t Temp)
{
  //初期化
  tft.fillRect(170, 150, 150, 20, TFT_BLACK);
  //文字・背景の色
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //フォント
  tft.setFreeFont(FS12);
  //文字サイズ
  tft.setTextSize(1);
  //文字の出力
  tft.drawString("Battery: " + String(Temp) + "`C", 170, 150);
}

void tftViewDriverTemp(uint8_t Temp)
{
  //初期化
  tft.fillRect(170, 180, 150, 20, TFT_BLACK);
  //文字・背景の色
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //フォント
  tft.setFreeFont(FS12);
  //文字サイズ
  tft.setTextSize(1);
  //文字の出力
  tft.drawString("Driver: " + String(Temp) + "`C", 170, 180);
}

void tftViewMotorTemp(uint8_t Temp)
{
  //初期化
  tft.fillRect(170, 210, 150, 20, TFT_BLACK);
  //文字・背景の色
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //フォント
  tft.setFreeFont(FS12);
  //文字サイズ
  tft.setTextSize(1);
  //文字の出力
  tft.drawString("Motor: " + String(Temp) + "`C", 170, 210);
}

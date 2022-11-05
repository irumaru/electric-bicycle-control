#include "battery.h"

/**
 * @brief バッテリ電圧を取得
 * @return uint16_t バッテリ電圧[mV]
 */
uint16_t getBatteryMillivolt()
{
  //電圧を取得
  uint16_t raw = readADCMillivolt(ADC_CH_OF_VOLTAGE);

  //バッテリ電圧に変換
  return map(raw, 0, 1000, 0, 11000);
}

/**
 * @brief バッテリ残量を取得
 * @return uint8_t バッテリ残量[%]
 */
uint8_t getBatteryPercent()
{
  return map(constrain(getBatteryMillivolt(), 21000, 29400) , 21000, 29400, 0, 100);
}
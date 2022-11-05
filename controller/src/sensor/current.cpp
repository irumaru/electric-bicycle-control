#include "current.h"

/**
 * @brief 電流量を取得
 * @return uint16_t 電流[mA]
 */
uint16_t getCurrent()
{
  //ADC
  uint16_t millvolt = readADCMillivolt(ADC_CH_OF_CURRENT);

  //Serial.printf("CurrentSensor: %dmV\n", millvolt);

  uint16_t current = map(constrain(millvolt, 0, 2525) , 2525, 2475, 0, 1000);

  Serial.printf("Current: %dmA\n", current);

  return current;
}
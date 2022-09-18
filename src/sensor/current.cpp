#include "current.h"

/**
 * @brief 電流量を取得
 * @return uint16_t 電流[mA]
 */
uint16_t getCurrent()
{
  //ADC
  uint16_t millvolt = readADCMillivolt(ADC_CH_OF_CURRENT);

  return map(constrain(millvolt, 0, 2500) , 2500, 2000, 0, 10000);
}
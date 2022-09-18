#include "temp.h"

/**
 * @brief 温度センサー(LM61CIZ)の温度を取得
 * @param channel 温度センサーが接続されている外部ADCのチャンネル
 * @return int16_t 温度
 */
int16_t getTemp(uint8_t channel)
{
  //計算
  return map(readADCMillivolt(channel) , 300, 1600, -30, 100);
}
#include "throttle.h"

//#include <BluetoothSerial.h>
//extern Serial;

/**
 * @brief スロットルの値を取得
 * @return uint16_t 
 */
uint16_t getThrottle()
{
  //入力
  uint16_t raw = readADC(ADC_CH_OF_THROTTLE);
  //int raw = readADC(ADC_CH_OF_THROTTLE);
  //ディバッグ
  //Serial.printf("ThrottleRaw=%d\n", raw);
  //スロットルの特性に合わせて変換&出力
  return map(constrain(raw, 510, 2620) , 510, 2620, 0, 4095);
}
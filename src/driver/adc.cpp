/**
 * @file adc.cpp
 * @author Irumaru
 * @brief ADCに関する機能
 * @version 0.1
 */

#include "adc.h"


//#include <BluetoothSerial.h>

//extern BluetoothSerial bt;

MCP3208 adc;

/**
 * @brief ADCの初期化
 * @return int 正常時にtrue
 */
int adcBegin()
{
    //初期化(HW SPI)
    return adc.begin();
}

/**
 * @brief ADCの読み取り
 * @param channel 読み取るチャンネル
 * @return uint16_t ADCの値
 */
uint16_t readADC(uint8_t channel)
{
    //読み取り
    int value = adc.readADC(channel);

    //ディバッグ
    //bt.printf("Ch=%d, Val=%d\n", channel, value);

    //0～4095以外の時にエラーとする
    if(value < 0 || 4095 < value)
    {
        //エラー
        return 0;
    }

    return value;
}

/**
 * @brief ADCを読み取り、電圧[mV]に変換して返す
 * @param channel 読み取るチャンネル
 * @return uint16_t 電圧
 */
uint16_t readADCMillivolt(uint8_t channel)
{
    //計算
    return map(readADC(channel), 0, 4095, 0, 3300);
}
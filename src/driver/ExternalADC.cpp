
#include "ExternalADC.h"

void ExternalADC::begin()
{
    //ディバイスの初期化
    int status = this->adc.begin(5, new SPIClass(VSPI));

    #if SERIAL_DEBUG
    Serial.printf("ExternalADC::begin() return %d\n", status);
    #endif

    //ループ開始

}

void ExternalADC::loop()
{
    uint16_t count = 0;
    uint16_t value;
    uint8_t getCount;
    
    while(true)
    {
        getCount = 0;
        for(uint8_t i = 0; i < 8; i ++)
        {
            if(this->periodCount != 0)
                if(count % this->periodCount == 0)
                {
                    this->values[i] = this->adc.readADC(i);
                    getCount ++;
                }
            delayMicroseconds(constrain((int)this->period - (readDelay * this->periodCount), 0, 1000000));
        }
        count ++;
    }
}

void ExternalADC::setADC(uint8_t channel, uint16_t freq)
{
    //周期[us]を計算
    int period = (((double)1 / freq) * 1000000);

    //readADCの時間を引いて格納
    this->delay[channel] = period - this->readDelay;

    #if SERIAL_DEBUG
    Serial.printf("ExternalADC::setADC() ch%d: period %d\n", channel, period);
    #endif
}



uint16_t ExternalADC::readADC(uint8_t channel)
{
    //読み取り
    uint16_t value = this->adc.readADC(channel);

    #if SERIAL_DEBUG
    Serial.printf("ExternalADC::readADC() Ch%d: %d\n", channel, value);
    #endif

    //0～4095以外の時にエラーとする
    if(value < 0 || 4095 < value)
        //エラー
        return 0;

    return value;
}

uint16_t ExternalADC::readADCMillivolt(uint8_t channel)
{
    //計算
    return map(readADC(channel), 0, 4095, 0, 3300);
}

#include "ExternalADC.h"

void ExternalADC::begin()
{
    //ディバイスの初期化
    int status = this->adc.begin(5, new SPIClass(VSPI));

    #if SERIAL_DEBUG
    Serial.printf("ExternalADC::begin() return %d\n", status);
    #endif

    //ループ開始
    xTaskCreatePinnedToCore(this->loop, "ADCLoop", 4096, NULL, 1, NULL, 1);
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

        //カウントリセット
        if(count == 10000)
            count = 0;
    }
}

void ExternalADC::setADC(uint8_t channel, uint16_t periodCount)
{
    this->periodCount[channel] = periodCount;
}

uint16_t ExternalADC::getADC(uint8_t channel)
{
    return this->values[channel];
}

uint16_t ExternalADC::getADCMillivolt(uint8_t channel)
{
    return map(this->getADC(channel), 0, 4095, 0, 3300);
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
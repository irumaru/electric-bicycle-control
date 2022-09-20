/**
 * @file multi.h
 * @author Irumaru
 * @brief シングルアクセスなセンサーを定期的に動かして、複数アクセスにキャッシュで応答する
 * @version 0.1
 * @date 2022-09-19
 */

#include <Arduino.h>
#include <MCP3208.h>

class ExternalADC
{
    public:
        void begin();
        void setADC(uint8_t, uint16_t);
        uint16_t getADC(uint8_t);
        uint16_t getADCMillivolt(uint8_t);
    private:
        MCP3208 adc;
        int period = 100; //1周期の時間[us]
        int periodCount[8] = {0,0,0,0,0,0,0,0}; //n周期毎にデータ取得
        int readDelay = 34; //mcp3208の遅延時間[us]
        uint16_t values[8] = {0,0,0,0,0,0,0,0}; //測定値
        void loop();
        uint16_t readADC(uint8_t);
};
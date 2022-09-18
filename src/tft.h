#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

void tftInit();
void tftViewInit();
void tftShowSpeed(uint8_t);
void tftViewOutput(uint8_t);
void tftViewCurrent(uint16_t);
void tftViewBattery(uint8_t);
void tftViewBatteryTemp(uint8_t);
void tftViewDriverTemp(uint8_t);
void tftViewMotorTemp(uint8_t);
#ifndef ADC_h
#define ADC_h

#include <Arduino.h>
#include <MCP3208.h>

int adcBegin();
uint16_t readADC(uint8_t);
uint16_t readADCMillivolt(uint8_t);

#endif
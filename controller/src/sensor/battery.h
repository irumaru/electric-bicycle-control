#ifndef BATTERY_h
#define BaTTERY_h

#include <Arduino.h>
#include "driver/adc.h"
#include "config.h"

uint16_t getBatteryMillivolt();
uint8_t getBatteryPercent();

#endif
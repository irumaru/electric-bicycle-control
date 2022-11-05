#ifndef SPEED_h
#define SPEED_h

#include <Arduino.h>
#include "config.h"

void speedometerSetup();
void speedMonitor(void *);
void speedDog();
void speedDogCheck();
void checkSet();
void checkStop();
float getSpeed();
int getSpeedAllow();

#endif
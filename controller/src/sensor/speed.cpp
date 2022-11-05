#include "speed.h"

//要修正
//----速度取得----
int unsigned checkStartTime = 0;
int unsigned checkStopTime = 0;
int unsigned speedDogTime = 0;
float Speed = 0;
uint8_t overSpeed = 0;
bool speedAllow = true;
void speedometerSetup()
{
  //割り込みピン
  pinMode(IO_PIN_OF_SPEED, INPUT_PULLUP);
  
  //磁石通通過
  //attachInterrupt(SPEED_PIN, checkAction, CHANGE);
  xTaskCreatePinnedToCore(speedMonitor, "speedMonitor", 4096, NULL, 2, NULL, 0);
}
void speedMonitor(void *arg)
{
  bool Status, oldStatus;
  while(true)
  {
    //マグネットの状態を取得
    Status = digitalRead(IO_PIN_OF_SPEED);
    
    if((Status == false) && (oldStatus == true))
    {
      checkSet();
      speedDog();
    }
    else if((Status == true) && (oldStatus == false))
    {
      checkStop();
      speedDog();
    }
    oldStatus = Status;

    speedDogCheck();
    
    delay(1);
  }
}
void speedDog()
{
  speedDogTime = millis();
}
void speedDogCheck()
{
  if(1000 < millis() - speedDogTime)
  {
    Speed = 0;
    speedAllow = true;
  }
}
void checkSet()
{
  checkStartTime = millis();
}
void checkStop()
{
  checkStopTime = millis();
  Speed = (MAGNET_INTERVAL * 3.6) / (checkStopTime - checkStartTime);
  //速度制限
  if(SPEED_LIMIT < Speed)
  {
    if(MAGNET_COUNT < overSpeed)
    {
      speedAllow = false;
    }
    else
    {
      overSpeed ++;
    }
  }
  else
  {
    speedAllow = true;
    if(0 < overSpeed)
    {
      overSpeed = 0;
    }
  }
  //ディバッグ
  //BtS.printf("Speed: %f, Over: %d, Allow: %d\n", Speed, overSpeed, speedAllow);
}
float getSpeed()
{
  return Speed;
}
int getSpeedAllow()
{
  return speedAllow;
}
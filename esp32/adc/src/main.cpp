#include <Arduino.h>
#define adcPin 32
int adcValue = 0;
hw_timer_t *tim0 = NULL;

void tim0Interrupt()
{
  adcValue=analogRead(adcPin);
  Serial.write(adcValue>>4);// convert to char and send
}

void setup()
{
  Serial.begin(230400);
  tim0 = timerBegin(0, 80, true); 
  timerAttachInterrupt(tim0, tim0Interrupt, true);
  timerAlarmWrite(tim0, 2000, true);
  timerAlarmEnable(tim0);
}

void loop()
{
  delay(10);
}

#include <Arduino.h>
#define adcPin 32
#define MAX 8
int adcValue[MAX];
hw_timer_t *tim0 = NULL;
char i = 0;

void tim0Interrupt()
{
  adcValue[i]=analogRead(adcPin);
  i++;
  if(i >= MAX) {
    for(i = 0;i < MAX;i++) {
      Serial.write(adcValue[i]>>4);// convert to char and send
    }
    i = 0;
  }
}

void setup()
{
  Serial.begin(230400);
  tim0 = timerBegin(0, 80, true);
  timerAttachInterrupt(tim0, tim0Interrupt, true);
  timerAlarmWrite(tim0, 250, true);
  timerAlarmEnable(tim0);
}

void loop()
{
  delay(10);
}

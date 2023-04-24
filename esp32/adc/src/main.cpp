#include <Arduino.h>
#define adcPin 32
#define MAX 16
int adcValue = 0;
hw_timer_t *tim0 = NULL;
char count = 0;

void tim0Interrupt()
{
  adcValue=analogRead(adcPin);
  Serial.write(adcValue>>4);// convert to char and send
  if(count < MAX) {
    count++;
  }
  else {
    count = 0;
    Serial.write('\n');
  }
}

void setup()
{
  Serial.begin(115200);
  tim0 = timerBegin(0, 80, true);
  timerAttachInterrupt(tim0, tim0Interrupt, true);
  timerAlarmWrite(tim0, 1000, true);
  timerAlarmEnable(tim0);
}

void loop()
{
  delay(10);
}

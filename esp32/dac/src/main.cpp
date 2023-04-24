#include <Arduino.h>
#include <stdlib.h>
#define dacPin 25
#define MAX 8
hw_timer_t *tim0 = NULL;
char data[MAX], j = 0;

void tim0Interrupt() {
  if(j < MAX) {
    dacWrite(dacPin,data[j]);
    j++;
  }
}

void setup() {
  Serial.begin(230400); //baud
  tim0 = timerBegin(0, 80, true);
  timerAttachInterrupt(tim0, tim0Interrupt, true);
  timerAlarmWrite(tim0, 250, true);
  timerAlarmEnable(tim0);
}

void loop() {
  // If anything comes in Serial1 (pins 0 & 1)
  if (Serial.available()) {
    Serial.readBytes(data, MAX);
    j = 0;
  }
}

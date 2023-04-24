#include <Arduino.h>
#include <stdlib.h>
#define dacPin 25
#define MAX 80
char data[MAX];
char i = 0, j = 0;
hw_timer_t *tim0 = NULL;

void tim0Interrupt() {
  if(j < MAX) {
    dacWrite(dacPin, data[j]);
    j++;
  }
}

void setup() {
  Serial.begin(115200); //baud
  tim0 = timerBegin(0, 80, true);
  timerAttachInterrupt(tim0, tim0Interrupt, true);
  timerAlarmWrite(tim0, 1000, true);
  timerAlarmEnable(tim0);
}

void loop() {
  // If anything comes in Serial1 (pins 0 & 1)
  if (Serial.available()) {
    if(i < MAX) {
      i++;
    }
    else {
      i = 0;
    }
    data[i]=(Serial.read());
    if(data[i] == '\n') {
      i = 0;
      j = 0;
    }
  }
}

#include <Arduino.h>
#include <stdlib.h>
#define dacPin 25
#define MAX 16
char data[MAX];
char i = 0, j = 0;
hw_timer_t *tim0 = NULL;
char test;

void tim0Interrupt() {
  // if(j < MAX) {
  //   dacWrite(dacPin,data[j++]);
  //   // dacWrite(dacPin, 100);
  // }
  dacWrite(dacPin, test);
}

void setup() {
  Serial.begin(115200); //baud
  tim0 = timerBegin(0, 10, true);
  timerAttachInterrupt(tim0, tim0Interrupt, true);
  timerAlarmWrite(tim0, 1000, true);
  timerAlarmEnable(tim0);
}

void loop() {
  // If anything comes in Serial1 (pins 0 & 1)
  if (Serial.available()) {
    // j = 0;
    // for(i = 0; i < MAX; i++) {
    //   data[i]=(Serial.read());
    // }
    test = Serial.read();
  }
}

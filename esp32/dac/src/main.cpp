#include <Arduino.h>
#define dacPin 25
char dat=0;

void setup() {
  Serial.begin(230400); //baud
}

void loop() {
  // If anything comes in Serial1 (pins 0 & 1)
  if (Serial.available()) 
  {
    dat=Serial.read();
    dat=dat;
    dacWrite(dacPin,dat);
  }
}

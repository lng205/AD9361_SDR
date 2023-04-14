// 不使用Serial可降低时延
#define dacPin 25
char dat=0;

void setup() {
  Serial.begin(230400); //230400
//  Serial2.begin(921600);
//  Serial.println("Hello. This is DAC.");
//  Serial2.println("Hello");
}

void loop() {
  if (Serial.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    dat=Serial.read();
    dacWrite(dacPin,dat);
//    Serial.println(dat);  // 反馈接收到的值，可以关
    // delayMicroseconds(100); //防止无线网包挤在一起到，导致dac不知所措？
  }
}

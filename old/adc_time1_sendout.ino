
// DAC管脚只能是25和26，且是8bit的（不能超过255）
// 用定时器控制ADC采样，这个代码采样率是4000Hz
// 用100Hz正弦波测得有75us时延
#define pwmPin 12
#define adcPin 32
#define outPin 23
#define dacPin 25
const int pwm_channel=8;
int flag=0;
int tim1_IRQ_count = 0;

int adcValue = 0;
char i=0;

hw_timer_t *tim1 = NULL; //这个要写

void tim1Interrupt()
{//中断服务函数
  adcValue=analogRead(adcPin);
//  Serial.println(adcValue); //注释掉降低时延，或者放Serial2.write后面
  
  // dac输出，只截取ADC值的高8bit，而adc原本是12bit的，所以只挪4bit
  // dacWrite(dacPin,adcValue>>4);
  Serial.write(adcValue>>4);

  if(i==255) i=0;
  i++;
//  Serial.write(i);
//  Serial.println();
  
//  Serial.println(flag);
  if(flag==0)
  { digitalWrite(outPin, HIGH); flag=1;}
  else
  { digitalWrite(outPin, LOW); flag=0;}
}

void setup() {
  Serial.begin(230400);
//  Serial.println("Hello. This is ADC.");
//  Serial2.begin(921600);
  pinMode(outPin, OUTPUT); //好怪，配置完要先"激活"一下中断才能用
  digitalWrite(outPin, HIGH);delay(22);digitalWrite(outPin, LOW);
  ledcSetup(pwm_channel, 1, 10);  //设置LEDC通道8频率为1，分辨率为10位，即占空比可选0~1023
  ledcAttachPin(pwmPin, pwm_channel); //设置LEDC通道8在IO12上输出
  ledcWrite(pwm_channel, 250); // 占空比为25/1024
  
  //1.定时器配置：定时器编号0-3，分频系数0-65535，是向上计数
  //  因为默认主频是80MHz，分频80，那么这个定时器的时钟频率为1MHz，一个周期为1us
  tim1 = timerBegin(0, 80, true); 
  //2. 绑定中断函数
  timerAttachInterrupt(tim1, tim1Interrupt, true);
  //3. 配置定时器计数上限值，到达后进入中断. 如100000*1us=100ms
  timerAlarmWrite(tim1, 2000, true); //fs=4kHz填250
  //4. 启动（使能）定时器
  timerAlarmEnable(tim1);
}

void loop() {
//  digitalWrite(outPin, LOW);
//  Serial.write(adcValue);
  delay(10);
}

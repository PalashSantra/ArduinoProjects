#include <IRremote.h>

#define button1 0x1FE50AF
#define button2 0x1FED827
#define button3 0x1FEF807
#define button4 0x1FE30CF
#define button5 0x1FEB04F
#define plus 0x1FE609F
#define minus 0x1FEA05F
#define off 0x1FE48B7

int RECV_PIN = 4;
int LED1=5;
int LED2=6;
int LED3=7;
int LED4=9;
int LED5=10;
int SensorLED=13;

int LEDStatus1=0;
int LEDStatus2=0;
int LEDStatus3=0;
int LEDStatus4=0;
int LEDStatus5=0;
int ledoff=0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  digitalWrite(LED5,LOW);
  digitalWrite(SensorLED,LOW);
}

void loop() {
  if (irrecv.decode(&results)) {
    switch(results.value){
      case button1:
        digitalWrite(SensorLED,HIGH);
        delay(100);
        digitalWrite(SensorLED,LOW);
        if(LEDStatus1==0){
          digitalWrite(LED1,HIGH);
          LEDStatus1=1;
        }
        else if(LEDStatus1==1){
          digitalWrite(LED1,LOW);
          LEDStatus1=0;
        }
        break;
      case button2:
        digitalWrite(SensorLED,HIGH);
        delay(100);
        digitalWrite(SensorLED,LOW);
        if(LEDStatus2==0){
          digitalWrite(LED2,HIGH);
          LEDStatus2=1;
        }
        else if(LEDStatus2==1){
          digitalWrite(LED2,LOW);
          LEDStatus2=0;
        }
        break;
      case button3:
        digitalWrite(SensorLED,HIGH);
        delay(100);
        digitalWrite(SensorLED,LOW);
        if(LEDStatus3==0){
          digitalWrite(LED3,HIGH);
          LEDStatus3=1;
        }
        else if(LEDStatus3==1){
          digitalWrite(LED3,LOW);
          LEDStatus3=0;
        }
        break;
      case button4:
        digitalWrite(SensorLED,HIGH);
        delay(100);
        digitalWrite(SensorLED,LOW);
        if(LEDStatus4==0){
          digitalWrite(LED4,HIGH);
          LEDStatus4=1;
        }
        else if(LEDStatus4==1){
          digitalWrite(LED4,LOW);
          LEDStatus4=0;
        }
        break;
      case off:
        digitalWrite(SensorLED,HIGH);
        delay(100);
        digitalWrite(SensorLED,LOW);
        digitalWrite(LED1,LOW);
        digitalWrite(LED2,LOW);
        digitalWrite(LED3,LOW);
        digitalWrite(LED4,LOW);
        digitalWrite(LED5,LOW);
        break;
    }
    irrecv.resume(); // Receive the next value
  }
  delay(10);
}

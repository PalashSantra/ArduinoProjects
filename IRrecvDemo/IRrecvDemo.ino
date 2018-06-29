
/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

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
int LED4=8;
int LED5=9;

int abc=0;

int LEDStatus1=0;
int LEDStatus2=0;
int LEDStatus3=0;
int LEDStatus4=0;
int LEDStatus5=0;
int ACLOADStatus=0;
int ledoff=0;

IRrecv irrecv(RECV_PIN);

decode_results results;

/*int dimming() {
    cli();
    int temp = dimming;
    sei();
}

void dimming(int value) {
    cli();
    dimming = value;
    sei();
}*/

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
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
}


void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch(results.value){
      case button1:
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
        if(LEDStatus4==0){
          digitalWrite(LED4,HIGH);
          LEDStatus4=1;
        }
        else if(LEDStatus4==1){
          digitalWrite(LED4,LOW);
          LEDStatus4=0;
        }
        break;
        case button5:
        if(LEDStatus5==0){
          digitalWrite(LED5,HIGH);
          LEDStatus5=1;
        }
        else if(LEDStatus5==1){
          digitalWrite(LED5,LOW);
          LEDStatus5=0;
        }
        break;
        /*case plus:
        if(ACLOADStatus<=2){
          dimming=dimming-41;
          ACLOADStatus=ACLOADStatus+1;
        }
        break;
        case minus:
        if(ACLOADStatus>=0){
          dimming=dimming+41;
          ACLOADStatus=ACLOADStatus-1;
        }
        break;*/
        case off:
        if(ledoff==0){
          digitalWrite(LED1,HIGH);
          digitalWrite(LED2,HIGH);
          digitalWrite(LED3,HIGH);
          digitalWrite(LED4,HIGH);
          digitalWrite(LED5,HIGH);
          ledoff=1;
        }
        else if(ledoff==1){
          digitalWrite(LED1,LOW);
          digitalWrite(LED2,LOW);
          digitalWrite(LED3,LOW);
          digitalWrite(LED4,LOW);
          digitalWrite(LED5,LOW);
          //digitalWrite(AC_LOAD,LOW);
          ledoff=0;
        }
        break;
      
    }
    irrecv.resume();
      delay(100);
  //analogWrite(LED2,55);
  }
}

#include <IRremote.h>
#include <TimerOne.h>
#define button1 0x38863BDC
#define button2 0x38863BFE
#define button3 0x38863BC6
#define buttonFan 0x38863BFC
#define plus 0x38863BF2
#define minus 0x38863BFA
#define off 0x38863BCC
int RECV_PIN = 3; //5
int L1=9; //15
int L2=10; //16
int L3=11; //17
int FAN =12; //18
boolean LS1=0;
boolean LS2=0;
boolean LS3=0;
boolean FANS=0;
boolean OFF=0;
int FANSpeed=0;
int prevFANSpeed=2;
volatile int i=0;               
volatile boolean zero_cross=0; 
int dim = 250;
int prevdim=60;
int freqStep = 100;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup(){
  irrecv.enableIRIn();
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(FAN, OUTPUT);
  digitalWrite(L1,LOW);
  digitalWrite(L2,LOW);
  digitalWrite(L3,LOW);
  digitalWrite(FAN,LOW);
  
  Serial.begin(9600);
}
                                  
void loop() {
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
    switch(results.value){
      case buttonFan:{
        if(LS1==0){
          Serial.println("LIGHT 1 ON");
          digitalWrite(FAN,HIGH);
          LS1=1;
        }
        else{
          Serial.println("LIGHT 1 OFF");
          digitalWrite(FAN,LOW);
          LS1=0;
        }
        break;
      }
      case button2:{
        if(LS2==0){
          Serial.println("LIGHT 2 ON");
          digitalWrite(L2,HIGH);
          LS2=1;
        }
        else{
          Serial.println("LIGHT 2 OFF");
          digitalWrite(L2,LOW);
          LS2=0;
        }
        break;
      }
      case button3:{
        if(LS3==0){
          Serial.println("LIGHT 3 ON");
          digitalWrite(L3,HIGH);
          LS3=1;
        }
        else{
          Serial.println("LIGHT 3 OFF");
          digitalWrite(L3,LOW);
          LS3=0;
        }
        break;
      }
      
      case off:{
        digitalWrite(L1,LOW);
        digitalWrite(L2,LOW);
        digitalWrite(L3,LOW);
        LS1=0;
        LS2=0;
        LS3=0;
        if(dim!=250){
          prevdim=dim;
          prevFANSpeed=FANSpeed;
          dim=250;
          FANS=0;
        }
        Serial.println("ALL OFF");
        break;
      }
      case plus:{
        if(FANS==1){
          if(FANSpeed<5){
            FANSpeed+=1;
            dim-=20;
            Serial.print("Fan Speed : ");
            Serial.println(FANSpeed);
            Serial.print("Fan dim : ");
            Serial.println(dim);
          }
        }
        break; 
      }
      case minus:{
        if(FANS==1){
          if(FANSpeed>2){
            FANSpeed-=1;
            dim+=20;
            Serial.print("Fan Speed : ");
            Serial.println(FANSpeed);
            Serial.print("Fan dim : ");
            Serial.println(dim);
          }
        }
        break;
      }
      default:{
        break;
      } 
    }
    delay(18);
    irrecv.resume();
  }
}

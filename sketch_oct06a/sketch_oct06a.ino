#include <IRremote.h>
#include <TimerOne.h>
#define button1 0xF4110
#define button2 0x74110
#define button3 0xC110
#define buttonFan 0x5C110
#define plus 0x240C
#define minus 0x640C
#define off 0x540C
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
  //Serial.println(j);
  if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
    switch(results.value){
      case button1:{
        if(LS1==0){
          Serial.println("LIGHT 1 ON");
          analogWrite(L1,255);
          LS1=1;
        }
        else{
          Serial.println("LIGHT 1 OFF");
          analogWrite(L1,255);
          LS1=0;
        }
        break;
      }
      case button2:{
        if(LS2==0){
          Serial.println("LIGHT 2 ON");
          analogWrite(L2,255);
          LS2=1;
        }
        else{
          Serial.println("LIGHT 2 OFF");
          analogWrite(L2,255);
          LS2=0;
        }
        break;
      }
      case button3:{
        if(LS3==0){
          Serial.println("LIGHT 3 ON");
          analogWrite(L3,255);
          LS3=1;
        }
        else{
          Serial.println("LIGHT 3 OFF");
          analogWrite(L3,255);
          LS3=0;
        }
        break;
      }
      case buttonFan:{
        if(FANS==0){
          Serial.println("LIGHT 3 ON");
          digitalWrite(FAN,HIGH);
          FANS=1;
        }
        else{
          Serial.println("LIGHT 3 OFF");
          digitalWrite(FAN,LOW);
          FANS=0;
        }
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

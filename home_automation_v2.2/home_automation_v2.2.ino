#include <IRremote.h>
#include <TimerOne.h>
#include <TimerFreeTone.h>
/* Remote Sensing Button*/
#define button1 0x1FE50AF
#define button2 0x1FED827
#define button3 0x1FEF807
#define buttonFan 0x1FE807F
#define plus 0x1FE609F
#define minus 0x1FEA05F
#define off 0x1FE48B7
#define intel_button 0x1FE7887
/* Pin Details */
#define PIR 4 // 6
#define RECV_PIN 3 // 5
#define L1 9 // 15
#define L2 10 // 16
#define L3 11 // 17
#define FAN 12 // 18
#define BUZ 8 // 14
#define LDR A0
/* Constant Details */
#define MAX1 1000
#define LDRValueMax 80
/* Status Details */
boolean LS1=0;
boolean LS2=0;
boolean LS3=0;
boolean FANS=0;
boolean OFF=0;
boolean IS=0;
int FANSpeed=0;
int prevFANSpeed=2;
int prevdim=60;
int LDRValue=0;
/* Global Variable Details */
volatile int i=0;               
volatile boolean zero_cross=0; 
int dim = 200;
int freqStep = 100;
int counter=0;
IRrecv irrecv(RECV_PIN);
decode_results results;
/* Initialization */
void setup(){
  //Enable IR receiver
  irrecv.enableIRIn();
  //Set Pin
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(BUZ, OUTPUT);
  pinMode(PIR,INPUT);
  //Initialize Pin Value
  digitalWrite(L1,LOW);
  digitalWrite(L2,LOW);
  digitalWrite(L3,LOW);
  digitalWrite(FAN,LOW);
  //Interrupt for Zero Cross
  attachInterrupt(0, zero_cross_detect, RISING);
  //Timing Interrupt
  Timer1.initialize(freqStep);  
  Timer1.attachInterrupt(dim_check, freqStep);
  //Start Serial Monitor
  Serial.begin(9600);
}
void zero_cross_detect() {
  zero_cross = true;
    i=0;
    digitalWrite(FAN, LOW);
}                                 
void dim_check() {           
  if(zero_cross == true) {              
    if(i>=dim) {                     
      digitalWrite(FAN, HIGH);      
      i=0;                        
      zero_cross = false;
    } 
    else {
      i++;
    }                                
  }                                 
}                                   
void intel_work(){
  if(IS==1){
    int pir_value=digitalRead(PIR);
    int ldr_value=analogRead(LDR);
    if(pir_value==HIGH && ldr_value<LDRValueMax){
      senseTone();
      digitalWrite(L1,HIGH);
      LS1=1;
      Serial.println("LIGHT 1 ON");
      counter=0;
      IS=0;
    }
    else{
      counter++;
      if(counter>MAX1){
        senseTone();
        digitalWrite(L1,LOW);
        LS1=0;
        Serial.println("LIGHT 1 OFF");
        counter=0;
      }
    } 
  }
}
void intel_on_off(){
  if(IS==0){
    Serial.println("Intel ON");
    IS=1;
  }
  else{
    Serial.println("Intel OFF");
    IS=0;
  }
}
void senseTone(){
  TimerFreeTone(BUZ, 262, 250); // Play thisNote for duration.
  delay(50);
  TimerFreeTone(BUZ, 262, 250);
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
    switch(results.value){
      case button1:{
        senseTone();
        if(LS1==0){
          Serial.println("LIGHT 1 ON");
          digitalWrite(L1,HIGH);
          LS1=1;
        }
        else{
          Serial.println("LIGHT 1 OFF");
          digitalWrite(L1,LOW);
          LS1=0;
        }
        break;
      }
      case button2:{
        senseTone();
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
        senseTone();
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
      case buttonFan:{
        senseTone();
        if(FANS==0){
          dim=prevdim;
          FANSpeed=prevFANSpeed;
          FANS=1;
          Serial.println("FAN ON");
          Serial.print("Fan Speed : ");
          Serial.println(FANSpeed);
          Serial.print("Fan dim : ");
          Serial.println(dim);
        }
        else{
          Serial.println("FAN OFF");
          prevdim=dim;
          prevFANSpeed=FANSpeed;
          dim=200;
          FANS=0;
        }
        break;
      }
      case off:{
        senseTone();
        digitalWrite(L1,LOW);
        digitalWrite(L2,LOW);
        digitalWrite(L3,LOW);
        LS1=0;
        LS2=0;
        LS3=0;
        if(dim!=200){
          prevdim=dim;
          prevFANSpeed=FANSpeed;
          dim=200;
          FANS=0;
        }
        intel_on_off();
        Serial.println("ALL OFF");
        break;
      }
      case plus:{
        senseTone();
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
        senseTone();
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
      case intel_button:{
        senseTone();
        intel_on_off();
        break;
      }
      default:{
        break;
      } 
    }
    delay(18);
    irrecv.resume();
  }
  intel_work();
  delay(5);
}


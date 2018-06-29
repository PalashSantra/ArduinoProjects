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
boolean FANSX=0;
boolean OFF=0;
int FANSpeed=0;
int prevFANSpeed=3;

IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
	irrecv.enableIRIn();
	pinMode(L1, OUTPUT);
	pinMode(L2, OUTPUT);
	pinMode(L3, OUTPUT);
	pinMode(FAN, OUTPUT);
	digitalWrite(L1,HIGH);
	digitalWrite(L2,HIGH);
	digitalWrite(L3,HIGH);
	digitalWrite(FAN,HIGH);
  
	Serial.begin(9600);
}

void loop() {
	if (irrecv.decode(&results)) {
		Serial.println(results.value,HEX);
		switch(results.value){
      case button1:{
        if(FANSX==0){
          Serial.println("LIGHT 1 ON");
          digitalWrite(FAN,LOW);
          FANSX=1;
        }
        else{
          Serial.println("LIGHT 1 OFF");
          digitalWrite(FAN,HIGH);
          FANSX=0;
        }
        break;
      }
			case buttonFan:{
				if(FANS==0){
					FANS=1;
					FANSpeed=prevFANSpeed;
					Operate(FANSpeed);
          Serial.println(FANSpeed);
				}
				else{
					digitalWrite(L1,HIGH);
					digitalWrite(L2,HIGH);
					digitalWrite(L3,HIGH);
         
					FANS=0;
					prevFANSpeed=FANSpeed;
          Serial.println(FANSpeed);
				}
        break;
      }
      /*
      case off:{
        digitalWrite(L1,HIGH);
        digitalWrite(L2,HIGH);
        digitalWrite(L3,HIGH);
		    FANS=0;
        prevFANSpeed=FANSpeed;
        break;
      }*/
      case plus:{
    		if(FANS==1){
    			if(FANSpeed<3){
    				FANSpeed++;
    				Operate(FANSpeed);
            Serial.println(FANSpeed);
    			}
        }
        break; 
      }
      case minus:{
        if(FANS==1){
    			if(FANSpeed>1){
    				FANSpeed--;
    				Operate(FANSpeed);
            Serial.println(FANSpeed);
    			}
        }
        break;
      }
      default:{
        break;
      } 
    }
    //delay(1000);
    irrecv.resume();
  }
}
void Operate(int FANSpeed){
  switch(FANSpeed){
    case 1:{
      digitalWrite(L2,HIGH);
      digitalWrite(L3,HIGH);
      digitalWrite(L1,LOW);
      break;
    }
    case 2:{
      digitalWrite(L1,HIGH);
      digitalWrite(L3,HIGH);
      digitalWrite(L2,LOW);
      break;
    }
    case 3:{
      digitalWrite(L1,HIGH);
      digitalWrite(L2,HIGH);
      digitalWrite(L3,LOW);
      break;
      }
    }
}

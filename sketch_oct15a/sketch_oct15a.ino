#include <TimerOne.h>
#include <IRremote.h>
#define button1 0x38863BDC

int RECV_PIN = 3;
int FAN =12;

boolean LS1=0;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  irrecv.enableIRIn();
  pinMode(FAN, OUTPUT);
  // put your setup code here, to run once:
digitalWrite(FAN,HIGH);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
    switch(results.value){
      case button1:{
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
    }
    irrecv.resume();
}
}

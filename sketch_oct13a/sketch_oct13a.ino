#include <IRremote.h>
#define button1 0x38863BDC
#define button2 0x38863BFE
#define button3 0x38863BC6
#define buttonFan 0x38863BFC
#define plus 0x38863BF2
#define minus 0x38863BFA
#define off 0x38863BCC

int RECV_PIN = 3; //5
int L1=9; //15
boolean LS1=0;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // put your setup code here, to run once:
irrecv.enableIRIn();
  pinMode(L1, OUTPUT);
  digitalWrite(L1,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
if (irrecv.decode(&results)) {
    switch(results.value){
      case button1:{
        if(LS1==0){
          Serial.println("LIGHT 1 ON");
          digitalWrite(L1,HIGH);
          LS1=1;
        }
        else{
          Serial.println("LIGHT 1 OFF");
          digitalWrite(L1,HIGH);
          LS1=0;
        }
        break;
      }
    }
    delay(18);
    irrecv.resume();
}
}

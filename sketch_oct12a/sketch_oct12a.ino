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
    Serial.println(results.value,HEX);
    if(results.value==button1)
    if(LS1==0)
      digitalWrite(L1,HIGH);
      else
      digitalWrite(L1,LOW);
    delay(18);
    irrecv.resume();
}
}

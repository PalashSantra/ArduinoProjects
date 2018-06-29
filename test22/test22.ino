#include <IRremote.h>
#define RECV_PIN 7

#define button1 0x1FE50AF
#define button2 0x1FED827
#define button3 0x1FEF807
#define buttonFan 0x1FE807F
#define plus 0x1FE609F
#define minus 0x1FEA05F
#define off 0x1FE48B7
#define intel_button 0x1FE7887

IRrecv irrecv(RECV_PIN);
decode_results results;
void setup() {
  // put your setup code here, to run once:
irrecv.enableIRIn();
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
    delay(18);
    irrecv.resume();
  }
}

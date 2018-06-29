#include <IRremote.h>
int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup() {
  // put your setup code here, to run once:
irrecv.enableIRIn();
Serial.begin(9600);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    delay(18);
    irrecv.resume();
  }
  // put your main code here, to run repeatedly:

}

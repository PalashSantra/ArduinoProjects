#include <IRremote.h>

int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);

decode_results results;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  // put your main code here, to run repeatedly:
if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
}
delay(100);
}

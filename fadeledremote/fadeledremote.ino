#include <IRremote.h>

int RECV_PIN = 2;
int LED=6;
int LEDStatus=0;
IRrecv irrecv(RECV_PIN);
int brightness=0;

decode_results results;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  pinMode(LED, OUTPUT);
  analogWrite(LED,brightness);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if(results.value==0x1FE609F){
      if(brightness<=255){
        brightness=brightness+1;
        analogWrite(LED,brightness);
        Serial.println(brightness);
      }
    }
    else if(results.value==0x1FEA05F){
      if(brightness>=0){
        brightness=brightness-1;
        analogWrite(LED,brightness);
        Serial.println(brightness);
      }
    }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

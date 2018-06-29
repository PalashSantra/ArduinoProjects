  #include <IRremote.h>
  #define plus 0x1FE609F
#define minus 0x1FEA05F
int RECV_PIN = 2;
  int LED=6;
int LEDStatus=0;
int brightness=0;
int thresh=0;

IRrecv irrecv(RECV_PIN);

decode_results results;


void setup() {
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogWrite(LED,brightness);
}


void loop() {
  
   if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch(results.value){
      case plus:
      brightness+=50;
        analogWrite(LED,brightness);
        break;
       case minus:
       brightness-=50;
       analogWrite(LED,brightness);
       break;
    }
    }
  }

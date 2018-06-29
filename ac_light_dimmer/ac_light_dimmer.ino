#define triacPulse 10
#define SW 4
#define aconLed 13

int val;
int incomingByte = 0;
void setup()  {
  Serial.begin(9600);
  
   pinMode(2, INPUT);
   digitalWrite(2, HIGH); // pull up
   pinMode(triacPulse, OUTPUT);
   pinMode(SW, INPUT);
   digitalWrite(SW, HIGH);
   pinMode(aconLed, OUTPUT);
   digitalWrite(aconLed, LOW);
  }

void loop() {
  // check for SW closed
  
  if (digitalRead(SW))   {
    // enable power
    attachInterrupt(0, acon, FALLING); 
    // HV indicator on
    digitalWrite(aconLed, HIGH);
  }  // end if
     else if (!digitalRead(SW)) { 
       detachInterrupt(0); // disable power
       // HV indicator off
       digitalWrite(aconLed, LOW);
     }  // else
  } // end loop
   
   

// begin ac int routine
// delay() will not work!
void acon()  
   {
    incomingByte=Serial.read();
    Serial.println(incomingByte);
    delayMicroseconds(-1); // read AD1 
    digitalWrite(triacPulse, HIGH);
    delayMicroseconds(100000000);  
    // delay 50 uSec on output pulse to turn on triac
    digitalWrite(triacPulse, LOW);
   } 

#define triacPulse 5
#define SW 4
#define aconLed 12 

int val;

void setup()  {
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
  if (!digitalRead(SW))   {
    // enable power
    attachInterrupt(0, acon, FALLING); 
    // HV indicator on
    digitalWrite(aconLed, HIGH);
  }  // end if
  else if (digitalRead(SW)) { 
    detachInterrupt(0); // disable power
    // HV indicator off
    digitalWrite(aconLed, LOW);
  }  // else
} // end loop



// begin AC interrupt routine
// delay() will not work!
void acon()  
{
  delayMicroseconds((analogRead(0) * 6) + 1000); // read AD1 
  digitalWrite(triacPulse, HIGH);
  delayMicroseconds(200);  
  // delay 200 uSec on output pulse to turn on triac
  digitalWrite(triacPulse, LOW);
} 

int pin = 2; //define interrupt pin to 2
volatile int state = LOW; // To make sure variables shared between an ISR
//the main program are updated correctly,declare them as volatile.

void setup() {
  Serial.begin(9600);  
   pinMode(10, OUTPUT); //set pin 13 as output
   digitalWrite(10, HIGH);
   //attachInterrupt(0, blink, RISING);
   //interrupt at pin 2 blink ISR when pin to change the value
} 
void loop() { 
   //digitalWrite(5, state); //pin 13 equal the state value
   //digitalWrite(5, state);
   //delayMicroseconds(75*120);
   //state = !state; //toggle the state when the interrupt occurs
  // digitalWrite(5, state);
  // delayMicroseconds(10);
  // Serial.println(state);
} 

void blink() { 
   //ISR function
   //digitalWrite(5, state);
   //delayMicroseconds(75*5);
   state = !state; //toggle the state when the interrupt occurs
   //digitalWrite(5, !state);
   //delayMicroseconds(10);
}

/*
AC Light Control
Uses up and down buttons to set levels
makes use of a timer interrupt to set the level of dimming
*/
#include <TimerOne.h>           // Avaiable from http://www.arduino.cc/playground/Code/Timer1

volatile int i=0;               // Variable to use as a counter of dimming steps. It is volatile since it is passed between interrupts
volatile boolean zero_cross=0;  // Flag to indicate we have crossed zero
int AC_pin = 10;                 // Output to Opto Triac
int buton1 = 4;                 // first button at pin 4
int buton2 = 5;                 // second button at pin 5
int dim2 = 0;                   // led control
int dim = 128;                  // Dimming level (0-128)  0 = on, 128 = 0ff
int pas = 8;                    // step for count;
int freqStep = 75;              // This is the delay-per-brightness step in microseconds. It allows for 128 steps
                                // If using 60 Hz grid frequency set this to 65

 
void setup() {  // Begin setup
  Serial.begin(9600);   
  pinMode(buton1, INPUT);  // set buton1 pin as input
  pinMode(buton2, INPUT);  // set buton1 pin as input
  pinMode(AC_pin, OUTPUT);                          // Set the Triac pin as output
  attachInterrupt(0, zero_cross_detect, RISING);    // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);      // Go to dim_check procedure every 75 uS (50Hz)  or 65 uS (60Hz)
  // Use the TimerOne Library to attach an interrupt

}

void zero_cross_detect() {    
  zero_cross = true;               // set flag for dim_check function that a zero cross has occured
  i=0;                             // stepcounter to 0.... as we start a new cycle
  digitalWrite(AC_pin, LOW);
}                                 

// Turn on the TRIAC at the appropriate time
// We arrive here every 75 (65) uS
// First check if a flag has been set
// Then check if the counter 'i' has reached the dimming level
// if so.... switch on the TRIAC and reset the counter
void dim_check() {                   
  if(zero_cross == true) {              
    if(i>=dim) {                     
      digitalWrite(AC_pin, HIGH);  // turn on light       
      i=0;  // reset time step counter                         
      zero_cross=false;    // reset zero cross detection flag
    } 
    else {
      i++;  // increment time step counter                     
    }                                
  }    
}                                      

void loop() { 
  int x; 
  x=Serial.read();
  Serial.println(x);
  
}

#include <IRremote.h>
#include  <TimerOne.h>

#define button4 0x1FE30CF
#define button5 0x1FEB04F
#define button6 0x1FE708F

int RECV_PIN = 4; //IC Pin 6
int FANStatus=0;
int fan=0;
volatile int i=0;               // Variable to use as a counter volatile as it is in an interrupt
volatile boolean zero_cross=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin =10; //16                // Output to Opto Triac
int dim = 128;                    // Dimming level (0-128)  0 = on, 128 = 0ff
int inc=1;   

int freqStep = 75;    // This is the delay-per-brightness step in microseconds.


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  irrecv.enableIRIn(); // Start the receiver

  pinMode(AC_pin, OUTPUT);
  digitalWrite(AC_pin,LOW);

  attachInterrupt(0, zero_cross_detect, RISING);    // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);     
  
  Serial.begin(9600);
}

void zero_cross_detect() {
      
    zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
    i=0;
    digitalWrite(AC_pin, LOW);       // turn off TRIAC (and AC)
  
} 
void dim_check() {           
    if(zero_cross == true) {              
      if(i>=dim) {                     
        digitalWrite(AC_pin, HIGH); // turn on light       
        i=0;  // reset time step counter                         
        zero_cross = false; //reset zero cross detection
      } 
      else {
        i++; // increment time step counter                     
      }                                  
  }                                
}  

void loop() {
  //Serial.println(dim);
  if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
    switch(results.value){
      case button4:
        dim=10;
        break;
        case button5:
        dim=50;
        break;
    }
    irrecv.resume(); 
  }
}


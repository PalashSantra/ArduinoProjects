/*AC Light Control
 
 Updated by Robert Twomey 
 
 Changed zero-crossing detection to look for RISING edge rather
 than falling.  (originally it was only chopping the negative half
 of the AC wave form). 
 
 Also changed the dim_check() to turn on the Triac, leaving it on 
 until the zero_cross_detect() turn's it off.
 
 Adapted from sketch by Ryan McLaughlin 
 http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1230333861/30
 
 */
#include <IRremote.h>
#include  <TimerOne.h>          // Avaiable from http://www.arduino.cc/playground/Code/Timer1
#define button1 0x1FE50AF
#define plus 0x1FE609F
#define minus 0x1FEA05F

int RECV_PIN = 7;
int LEDStatus1=0;
int fan=0;

IRrecv irrecv(RECV_PIN);

decode_results results;

volatile int i=0;               // Variable to use as a counter volatile as it is in an interrupt
volatile boolean zero_cross=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin = 4;                // Output to Opto Triac
int dim = 128;                    // Dimming level (0-128)  0 = on, 128 = 0ff
int inc=1;                      // counting up or down, 1=up, -1=down

int freqStep = 75;    // This is the delay-per-brightness step in microseconds.
                      // For 60 Hz it should be 65
// It is calculated based on the frequency of your voltage supply (50Hz or 60Hz)
// and the number of brightness steps you want. 
// 
// Realize that there are 2 zerocrossing per cycle. This means
// zero crossing happens at 120Hz for a 60Hz supply or 100Hz for a 50Hz supply. 

// To calculate freqStep divide the length of one full half-wave of the power
// cycle (in microseconds) by the number of brightness steps. 
//
// (120 Hz=8333uS) / 128 brightness steps = 65 uS / brightness step
// (100Hz=10000uS) / 128 steps = 75uS/step

void setup() {                                      // Begin setup
  irrecv.enableIRIn();
  pinMode(AC_pin, OUTPUT); 
  pinMode(5, OUTPUT);// Set the Triac pin as output
  attachInterrupt(0, zero_cross_detect, RISING);    // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);      
  // Use the TimerOne Library to attach an interrupt
  // to the function we use to check to see if it is 
  // the right time to fire the triac.  This function 
  // will now run every freqStep in microseconds.        
       digitalWrite(5,LOW);
   Serial.begin(9600);                               
}

void zero_cross_detect() {    
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i=0;
  digitalWrite(AC_pin, LOW);       // turn off TRIAC (and AC)
}                                 

// Turn on the TRIAC at the appropriate time
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
  if (irrecv.decode(&results)) {
    switch(results.value){
       case button1:
        if(LEDStatus1==0){
          digitalWrite(5,HIGH);
          LEDStatus1=1;
        }
        else if(LEDStatus1==1){
          digitalWrite(5,LOW);
          LEDStatus1=0;
        }
        break;   
        case plus:
        if(fan<4){
          fan+=1;
          Serial.println(fan);
          dim-=30;
        }
        break; 
        case minus:
        if(fan>0){
          fan-=1;
          Serial.println(fan);
          dim+=30;
        }
        break;                  
    }
    irrecv.resume();
  }
}
    
    
    
    
    
    
    
    
 /*   
    
    dim=6;
    Serial.println(dim);
    delay(1000);
    dim=50;
    Serial.println(dim);
    delay(1000);
    dim=80;
    Serial.println(dim);
    delay(1000);
    dim=128;
    Serial.println(dim);
    delay(1000);
  */
  /*delay(1000);
  dim=50;
  delay(1000);
  dim=10;
  delay(1000);*/
  /*
  digitalWrite(5,HIGH);
  //delay(18);
}*/

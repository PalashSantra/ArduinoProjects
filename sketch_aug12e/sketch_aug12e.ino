#include <TimerOne.h>
int AC_pin = 8;    
volatile boolean zero_cross=0;
int dim = 0;                 
int inc=1; 
volatile int i=0;  
void setup()
{
  Timer1.initialize(75);
    Timer1.attachInterrupt(dim_check, 75);
  pinMode(AC_pin, OUTPUT);// Set AC Load pin as output
  attachInterrupt(A0, zero_crosss_int, RISING);  // Choose the zero cross interrupt # from the table above
}


void zero_crosss_int()  //function to be fired at the zero crossing to dim the light
{
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i=0;
  digitalWrite(AC_pin, LOW);   // No longer trigger the TRIAC (the next zero crossing will swith it off) TRIAC
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
   
  dim+=inc;
  if((dim>=128) || (dim<=0))
    inc*=-1;
  delay(18);
}

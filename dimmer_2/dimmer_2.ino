//This code dims up and down a lamp in a period of time

//initialize and declare variables

#include <TimerOne.h>  // Avaiable from http://www.arduino.cc/playground/Code/Timer1
#define FREQ 50   // 50Hz power in these parts
#define AC1_Pin 8  // Output pin (TRIAC triggering)

const int DimMax = 100;                     // Max value in dimming scale
const int DimMin = 0;                       // Min value in dimming scale
int volatile Dim1 = 0;                 // Present dimming value
unsigned long int halfSineTime = 1000000 / (2 * FREQ);//The Timerone PWM period, 50Hz = 10000 uS
int rampInterval = halfSineTime/DimMax;                // Time of one step
int rampCounter = DimMax;        //Down counter with present step
int rampPeriod = 5;// For the fading, time in seconds that takes for the half way-up dimming (the same downwards)
int wait = rampPeriod*1000/DimMax;//Delay between increments of dimming
int buffer = 0.1*DimMax;// allows a safety buffer of steps in which results are dirty

void setup ()

{   //set the mode of the pins…
pinMode(AC1_Pin, OUTPUT);
attachInterrupt(0, light, FALLING );    //Zero-crossing detector
Timer1.initialize(halfSineTime);
Timer1.disablePwm(9);
Timer1.disablePwm(10);

}

void loop ()
{//The main loop just raises and lowers the value of Dim1 in the time specified in wait variable
   int x = 1;
   for (Dim1 = DimMin+buffer; Dim1 > DimMin+buffer-1; Dim1 = Dim1 + x){
      if (Dim1 == (DimMax-buffer)) x = -1;             // switch direction at peak
      delay(wait);
   }

}//close void loop



void light() //This function is triggerd at zero-cross
{
    Timer1.restart();//we set timer1 origin
    rampCounter = DimMax;//initialize the steps counter
    if (Dim1 < DimMin+1)
    {                  //Turn TRIAC completely OFF if Dim1 is 0
      digitalWrite(AC1_Pin, LOW);
    }
    else if (Dim1 > DimMax-1)
    {                //Turn TRIAC completely ON if Dim1 is 255
      digitalWrite(AC1_Pin, HIGH);
    }
   else 
   {     
   //Dimming part, if Dim1 is not 0 and not 255
   
    Timer1.attachInterrupt(nowIsTheTime, rampInterval); //If we have a value to dim then we trigger a timer interruption
  }
}


void nowIsTheTime ()
{
    if (rampCounter == Dim1)    //In the interrupt we fire the TRIAC only when the actual step (counting backwards) equals the value of Dim1
    {
       digitalWrite(AC1_Pin,HIGH);
    }
    else {
digitalWrite(AC1_Pin,LOW);//in the next step (and the rest) AC1_Pin remains low
    }
    rampCounter = rampCounter--;//decrease the counter
     
}

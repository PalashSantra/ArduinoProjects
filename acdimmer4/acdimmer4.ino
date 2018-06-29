#include <TimerOne.h> // Timer

int interruptPin =2;
int AC_LOAD=12;
volatile int i=0;
int x=0;
volatile boolean zero_cross=0;
int dimming=128;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(AC_LOAD, OUTPUT);
  attachInterrupt(0, zero_cross_detect, RISING);
  
}
void zero_cross_detect() { 
  //int dimming=64;  
  dimming=120;
  int dimtime = (75*dimming);    // For 60Hz =>65   
  delayMicroseconds(9000);    // Off cycle
  digitalWrite(AC_LOAD, HIGH);   // triac firing
  delayMicroseconds(10);         // triac On propagation delay (for 60Hz use 8.33)
  digitalWrite(AC_LOAD, LOW);    // triac Off
  x++;
}     

void loop()  {
  //dimming=128;
  digitalWrite(AC_LOAD,HIGH);
  Serial.println(x);
}

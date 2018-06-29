#include <IRremote.h>
#include  <TimerOne.h>

#define button1 0x1FE50AF
#define button2 0x1FED827
#define button3 0x1FEF807
#define button4 0x1FE30CF
#define button5 0x1FEB04F
#define button6 0x1FE708F

#define plus 0x1FE609F
#define minus 0x1FEA05F
#define off 0x1FE48B7

int RECV_PIN = 4; //IC Pin 6
int LED1=5; //11
int LED2=6; //12
int LED3=7; //13
int LED4=9; //15
//int LED5=10;
//int SensorLED=13;

int LEDStatus1=0;
int LEDStatus2=0;
int LEDStatus3=0;
int LEDStatus4=0;
int FANStatus=0;
int ledoff=0;
int fan=0;

volatile int i=0;               // Variable to use as a counter volatile as it is in an interrupt
volatile boolean zero_cross=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin =10; //16                // Output to Opto Triac
int dim = 128;                    // Dimming level (0-128)  0 = on, 128 = 0ff
int inc=1;                      // counting up or down, 1=up, -1=down

int freqStep = 75;    // This is the delay-per-brightness step in microseconds.


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  irrecv.enableIRIn(); // Start the receiver

  
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(AC_pin, OUTPUT);

  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  digitalWrite(AC_pin,LOW);

  attachInterrupt(0, zero_cross_detect, RISING);    // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);     
  
  Serial.begin(9600);
}

void zero_cross_detect() {
  if(FANStatus==1){    
    zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
    i=0;
    digitalWrite(AC_pin, LOW);       // turn off TRIAC (and AC)
  }
}                                 

// Turn on the TRIAC at the appropriate time
void dim_check() {           
  /*if(zero_cross == true) {       
    digitalWrite(AC_pin, HIGH);
    zero_cross = false;
  }*/
  if(FANStatus==1){ 
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
                                
}                                   

void loop() {
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value,HEX);
    switch(results.value){
      case button1:
        if(LEDStatus1==0){
          Serial.println("LIGHT 1 ON");
          digitalWrite(LED1,HIGH);
          LEDStatus1=1;
        }
        else if(LEDStatus1==1){
          Serial.println("LIGHT 1 OFF");
          digitalWrite(LED1,LOW);
          LEDStatus1=0;
        }
        break;
      case button2:
        if(LEDStatus2==0){
          Serial.println("LIGHT 2 ON");
          digitalWrite(LED2,HIGH);
          LEDStatus2=1;
        }
        else if(LEDStatus2==1){
          Serial.println("LIGHT 2 OFF");
          digitalWrite(LED2,LOW);
          LEDStatus2=0;
        }
        break;
      case button3:
        if(LEDStatus3==0){
          Serial.println("LIGHT 3 ON");
          digitalWrite(LED3,HIGH);
          LEDStatus3=1;
        }
        else if(LEDStatus3==1){
          Serial.println("LIGHT 3 OFF");
          digitalWrite(LED3,LOW);
          LEDStatus3=0;
        }
        break;
        case button4:
        if(FANStatus==0){
          Serial.println("FAN ON");
          dim=10;
          FANStatus=1;
           Serial.println(dim);
            Serial.println(FANStatus);
          
        }
        else if(FANStatus==1){
          dim=128;
          Serial.println("FAN OFF");
          FANStatus=0;
          Serial.println(FANStatus);
          digitalWrite(AC_pin,LOW);
        }
        break;
        case button5:
        if(FANStatus==0){
          Serial.println("FAN ON");
          dim=60;
          FANStatus=1;
           Serial.println(dim);
            Serial.println(FANStatus);
        }
        else if(FANStatus==1){
          Serial.println("FAN OFF");
          FANStatus=0;
          Serial.println(FANStatus);
          digitalWrite(AC_pin,LOW);
        }
        break;
        case button6:
        if(FANStatus==0){
          Serial.println("FAN ON");
          dim=100;
          FANStatus=1;
           Serial.println(dim);
            Serial.println(FANStatus);
        }
        else if(FANStatus==1){
          Serial.println("FAN OFF");
          FANStatus=0;
          Serial.println(FANStatus);
          digitalWrite(AC_pin,LOW);
        }
        break;
      case off:
      /*
        digitalWrite(LED1,LOW);
        digitalWrite(LED2,LOW);
        digitalWrite(LED3,LOW);
        digitalWrite(LED4,LOW);
        fan=0;
        dim=128;
        //digitalWrite(LED5,LOW);
        break;
        */
        case plus:
        if(fan<3){
          fan+=1;
          
          dim-=40;
          Serial.println(dim);
        }
        break; 
        case minus:
        if(fan>0){
          fan-=1;
          
          dim+=40;
          Serial.println(dim);
        }
        break;
    }
    delay(10);
    irrecv.resume(); // Receive the next value
  }
}

#include <IRremote.h>
int RECEIVE_PIN = 4;
int AC_LOAD = 5;    
int dimming=128;  

IRrecv irrecv(RECEIVE_PIN);
decode_results results;

void setup() 
{
    Serial.begin(9600);
    irrecv.enableIRIn();   
    pinMode(AC_LOAD, OUTPUT);         
    attachInterrupt(0, zero_crosss_int, RISING);  
}

void zero_crosss_int()  
{
    int dimtime = 75*dimming;      
    delayMicroseconds(dimtime);    // Off cycle
    digitalWrite(AC_LOAD, HIGH);   // triac firing
    delayMicroseconds(10);         // triac On propogation delay
    digitalWrite(AC_LOAD, LOW);    // triac Off
}

void loop() 
{
    if (irrecv.decode(&results)) 
    {
        Serial.print("0x");
        Serial.println(
        results.value, HEX);
        delay(50);

        if(results.value==0x1FE50AF)
            dimming = 120;
/*
        if(results.value==0x1FED827)
            dimming = 80;

        if(results.value==0x1FEF807)
            dimming = 20;*/

        irrecv.resume();
    }
    dimming=20;
    Serial.println(dimming);
    delay(10);
    dimming=80;
     delay(10);
    dimming=120;
     delay(10);
}

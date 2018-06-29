int AC_LOAD=13; //   We use pin 3 to ignite the TRIAC
int state; // integer to store the status of the zero crossing

void setup()
{
pinMode(AC_LOAD, OUTPUT);// Set AC Load pin as output
}

void loop()
{
state=digitalRead(AC_LOAD);
if (state=1) {
delayMicroseconds(500); // =5 ms=half power
digitalWrite(AC_LOAD, HIGH);   // triac firing
}
}

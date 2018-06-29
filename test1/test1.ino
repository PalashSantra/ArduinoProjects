#define AC 13
int j=0;
int dim=128;

void setup() {
  pinMode(AC,OUTPUT);
  digitalWrite(AC,LOW);
  attachInterrupt(0, zero_cross_int, RISING);
  Serial.begin(9600);
}
void zero_cross_int()  // function to be fired at the zero crossing to dim the light
{
  int dimtime = (75*dim);    // For 60Hz =>65   
  delayMicroseconds(dimtime);    // Off cycle
  digitalWrite(AC, HIGH);   // triac firing
  delayMicroseconds(10);         // triac On propagation delay (for 60Hz use 8.33)
  digitalWrite(AC, LOW);    // triac Off
}
void loop() {
  // put your main code here, to run repeatedly:
  dim=95;delay(100);
  dim=65;delay(100);
  dim=35;delay(100);
  dim=5;delay(100);
  dim=35;delay(100);
  dim=65;delay(100);
  dim=95;delay(100);
  dim=128;delay(100);
  dim=95;delay(100);
  dim=65;delay(100);
  dim=35;delay(100);
}

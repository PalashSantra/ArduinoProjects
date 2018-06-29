int i=0;
int dimming=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(4,1);
  //attachInterrupt(0, zero, FALLING);
  Serial.begin(9600);
}
void zero(){
  i=!i;
  /*
  int dimtime = (75*dimming);    // For 60Hz =>65   
  delayMicroseconds(dimtime);    // Off cycle
  digitalWrite(4, HIGH);   // triac firing
  delayMicroseconds(10);         // triac On propagation delay (for 60Hz use 8.33)
  digitalWrite(4, LOW);    // triac Off
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  /*Serial.println(dimming);
  for (int i=5; i <= 128; i++){
    dimming=i;
    delay(10);
   }*/
   /*
   Serial.println(i);
   delay(10);
   */
digitalWrite(8, HIGH);
   
}

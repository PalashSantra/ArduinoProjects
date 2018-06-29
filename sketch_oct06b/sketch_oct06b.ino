int L1=9;
void setup() {
  // put your setup code here, to run once:
pinMode(L1, OUTPUT);
digitalWrite(L1,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(7000);
digitalWrite(L1,HIGH);
delay(7000);
digitalWrite(L1,LOW);
delay(7000);
}

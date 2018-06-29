int LED=9;
int brightness=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LED, OUTPUT);
analogWrite(LED,brightness);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(brightness);
  /*if(brightness<=199){
    brightness=brightness+100;
    analogWrite(LED,brightness);
    delay(10000);
  }
  else{
   brightness=0;
   analogWrite(LED,brightness);
   delay(10000);
  }*/
  /*analogWrite(LED,0);
  Serial.println("1");
  delay(10000);
  /*analogWrite(LED,64);
  Serial.println("2");
  delay(10000);
  analogWrite(LED,127);
  Serial.println("3");
  delay(10000);*/
  /*analogWrite(LED,191);
  Serial.println("4");
  delay(10000);
  analogWrite(LED,255);
  Serial.println("5");
  delay(10000);*/

}

#define PIR 2 //4
#define LED 3 //5
#define MAX1 1000
#define MAX2 2000


int PIR_value=LOW;
int counter=0;
int intel=LOW;


void setup() {
  // put your setup code here, to run once:
  pinMode(PIR,INPUT);
  pinMode(LED,OUTPUT);
  intel=HIGH;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(intel==HIGH){
    int pir_value=digitalRead(PIR);
    if(pir_value==HIGH){
      digitalWrite(LED,HIGH);
      counter=0;
      //intel=LOW;
    }
    else{
      counter++;
      if(counter>MAX1){
        digitalWrite(LED,LOW);
        counter=0;
      }
    } 
  }
  delay(10);
  Serial.print("Counter : ");
  Serial.println(counter);
  Serial.print("Intel : ");
  Serial.println(intel);
}

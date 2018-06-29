#define PIR 2
#define LED 3
#define LDR A0
#define MAX 100
#define LDR_THRESHOLD 700


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
    int ldr_value=analogRead(LDR);
    if(pir_value==HIGH && ldr_value<LDR_THRESHOLD){
      digitalWrite(LED,HIGH);
      counter=0;
      //intel=LOW;
    }
    else{
      counter++;
      if(counter>MAX){
        digitalWrite(LED,LOW);
        counter=0;
      }
    } 
  }
  delay(100);
  Serial.print("Counter : ");
  Serial.println(counter);
  Serial.print("Intel : ");
  Serial.println(intel);
}

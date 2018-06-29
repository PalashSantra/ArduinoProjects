#include <LiquidCrystal.h>
#include <TimerFreeTone.h>
#include<dht.h>
dht DHTFunction;
//LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(1, 0, 5, 4, 3, 2);      // put your pin numbers here
int temp=0;
int humi=0;
void senseTone(){
  TimerFreeTone(A5, 262, 250); // Play thisNote for duration.
  delay(50);
  TimerFreeTone(A5, 262, 250);
}
void getDHT(){
  DHTFunction.read11(9);
  humi=DHTFunction.humidity;
  temp=DHTFunction.temperature;
}
void setup()
  {
  lcd.begin(16, 2);
  pinMode(9,INPUT);
  //Serial.begin(9600);
  }

  void lcdPrint(){
   
    if(millis()%1000==0){
      if((millis()/1000)%2){
        lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("L1  L2  L3  FAN");

  lcd.setCursor(0,1);
  lcd.print("OFF");
  lcd.setCursor(4,1);
  lcd.print("OFF");
  lcd.setCursor(8,1);
  lcd.print("OFF");
  lcd.setCursor(12,1);
  lcd.print("OFF");
      }else{
        getDHT();
        lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMP : ");
  lcd.setCursor(8,0);
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print("HUMI : ");
  lcd.setCursor(8,1);
  lcd.print(humi);
      }
      
    }
  }

void loop()
  {
  
  lcdPrint();
    /*
      delay(1000); //wait a sec (recommended for DHT11)
  DHTFunction.read11(9);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("humidity = ");
  lcd.print(DHTFunction.humidity);
  lcd.setCursor(0,1);
  lcd.print("Temp = ");
  lcd.print(DHTFunction.temperature);
  */
  
  }



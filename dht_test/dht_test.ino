#include<dht.h>
#include <LiquidCrystal.h>
dht DHT;

// if you require to change the pin number, Edit the pin with your arduino pin.

#define DHT11_PIN 9
LiquidCrystal lcd(1, 0, 5, 4, 3, 2);
void setup() {
lcd.begin(16, 2);
//Serial.begin(9600);

//Serial.println("welcome to TechPonder Humidity and temperature Detector"); }
}
void loop() { // READ DATA

int chk = DHT.read11(DHT11_PIN);

Serial.print(" Humidity " );

Serial.println(DHT.humidity, 1);

Serial.print(" Temparature ");

Serial.println(DHT.temperature, 1);

lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMP : ");
  lcd.setCursor(8,0);
  lcd.print(DHT.temperature);
  lcd.setCursor(0,1);
  lcd.print("HUMI : ");
  lcd.setCursor(8,1);
  lcd.print(DHT.humidity);

delay(2000);

}

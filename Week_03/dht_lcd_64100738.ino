#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

float temperature;
float humidity;
DHT dht14(D4, DHT11);

void setup() {
  lcd.begin();
  // lcd.cursor_on();
  lcd.setCursor(0,0);
  // lcd.print("Hello World!");


  temperature = 0;
  humidity = 0;
  Serial.begin(9600);
  dht14.begin();
}

void loop() {
  lcd.clear();
  humidity = dht14.readHumidity();
  temperature = dht14.readTemperature();
  
  lcd.printf("Humi: %.1f %%", humidity);
  lcd.setCursor(0,1);
  lcd.printf("Temp: %.1f C", temperature);

  delay(1000);
}

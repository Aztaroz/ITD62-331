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


// #include <Wire.h>
// void setup() {
//   Serial.begin (9600);
//   Serial.println ("I2C scanner. Scanning ...");
//   byte count = 0;
//   // 0x27 0x3F
//   Wire.begin();
//   for (byte i = 8; i < 120; i++)
//   {
//     Wire.beginTransmission (i);
//     if (Wire.endTransmission () == 0)
//       {
//       Serial.print ("Found address: ");
//       Serial.print (i, DEC);
//       Serial.print (" (0x");
//       Serial.print (i, HEX);
//       Serial.println (")");
//       count++;
//       delay (1);
//       }
//   }
//   Serial.println ("Done.");
//   Serial.print ("Found ");
//   Serial.print (count, DEC);
//   Serial.println (" device(s).");
// }  // end of setup

// void loop() {}

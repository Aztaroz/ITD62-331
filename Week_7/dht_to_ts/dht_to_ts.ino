#include <ESP8266WiFi.h>
#include <DHT.h>
#include "ThingSpeak.h"

// Network
const char* ssid = "Aztaroz";
const char* password = "14591459";
unsigned long channelID = 2339412; // Insert ID later
const char* writeKey = "TF41F7QVY5T6J5MY";

// Timer
unsigned long lastTime = 0;
unsigned long timerDelay = 15000;

//DHT
float humid;
float temp;
DHT dht(D4, DHT11);

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  dht.begin();
}

void loop() {
  humid = dht.readHumidity();
  temp = dht.readTemperature();

  if((millis() - lastTime) - timerDelay){
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attemping to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password);
        delay(5000);
      }
      Serial.println("/nConnected.");
    }
    int value = 10;
    Serial.print("Value: ");
    Serial.println(value);
    ThingSpeak.setField(1, humid);
    ThingSpeak.setField(2, temp);
    int x = ThingSpeak.writeFields(channelID, writeKey);
    if(x == 200){
      Serial.println("Channel update succesful");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code" + String(x));
    }
    lastTime = millis();
  }

}

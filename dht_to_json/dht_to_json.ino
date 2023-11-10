#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <WiFiUdp.h>
#include <NTPClient.h>
#include <UnixTime.h>

UnixTime stamp(7);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
uint32_t epochTime;
String dayStamp;
String timeStamp;

// Network
const char* ssid = "Aztaroz";
const char* password = "14591459";


String httpRequestData;

// DHT
float humid;
float temp;
DHT dht(D4, DHT11);

DynamicJsonDocument doc(1024);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
  timeClient.begin();
  timeClient.setTimeOffset(25200);
}

void loop() {

  // Set Datetime
  timeClient.update();
  epochTime = timeClient.getEpochTime();
  stamp.getDateTime(epochTime);
  Serial.println(epochTime);
  String datetime = String(stamp.day) + "/" + String(stamp.month) + "/" + String(stamp.year) + " " + String(timeClient.getFormattedTime());
  Serial.println(datetime);

  // Read Environment Data From DHT11
  humid = dht.readHumidity();
  temp = dht.readTemperature();

  // Set JSON and Create a Request
  doc["timestamp"] = datetime;
  doc["humid"] = humid;
  doc["temp"] = temp;
  String req;
  serializeJson(doc, req);

  // Sent Request to Server
  WiFiClient client;
  HTTPClient http;
  http.begin(client, "http://192.168.81.37:3000/data");
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(req);

  Serial.println(httpResponseCode);

  Serial.println(req);
  Serial.print("");
  http.end();
  delay(10000);
  

}

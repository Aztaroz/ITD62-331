#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <uri/UriBraces.h>
#include <uri/UriRegex.h>

#include <DHT.h>
float temperature;
float humidity;
DHT dht14(D4, DHT11);

ESP8266WebServer server(80);    //V2
const int led = D6;
bool led_status = false;

const char* html = "<!DOCTYPE html>\n"
                  "<html>\n"
                  "  <script>\n"
                  "    const led = async function(){\n"
                  "      await fetch('/led')\n"
                  "    }\n"
                  "    const report = async function(){\n"
                  "      fetch('/report')\n"
                  "         .then(res => res.text())\n"
                  "         .then(text => {\n"
                  "                 const [temp, humi] = text.split('/')\n"
                  "                 document.getElementById('temp').textContent = `Temperature: ${temp}`\n"
                  "                 document.getElementById('humi').textContent = `Humidity: ${humi}`\n"
                  "})\n"
                  "         .catch(error => console.log(error))\n"
                  "     }\n"
                  "  </script>\n"
                  "  <head>\n"
                  "    <title>Home</title>\n"
                  "  </head>\n"
                  "  <body onload='report()'>\n"
                  "    <center><h1>Welcome to ESP8266<h1></center>\n"
                  "<center><h3 id='temp'></h1></center>\n"
                  "<center><h3 id='humi'></h1></center>\n"
                  "    <center><button onclick='report()'>refresh</button></center> <br><br><br>\n"
                  "    <center><button onclick='led()'>Toggle LED on/off LED</button></center>\n"
                  "  </body>\n"
                  "</html>";





void init_wifi(String ssid, String password){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  pinMode(led, OUTPUT);

  temperature = 0;
  humidity = 0;
  dht14.begin();

  Serial.begin(115200);
  init_wifi("Aztaroz", "14591459");
  server.on(F("/"), [](){      //V2
    server.send(200, "text/html", html);
  });

  server.on(F("/led"), [](){
    if (led_status){
      digitalWrite(led,LOW);
      led_status = false;
      server.send(200, "text/plain", "Off");
    }
    else {
      digitalWrite(led,HIGH);
      led_status = true;
      server.send(200, "text/plain", "On");
    }
  });

  server.on("/report", [](){
    humidity = (dht14.readHumidity());
    temperature = (dht14.readTemperature());
    const String report = String(temperature) +'/'+ String(humidity);
    // const float report[] = {humidity,temperature};
    server.send(200, "text/plain", report);
  });

  server.begin();   //V2
  Serial.println("HTTP server started");    //V2

}

void loop() {
  server.handleClient();
}









// #include <ESP8266WiFi.h>

// WiFiServer server(8080);

// void init_wifi(){
//   WiFi.begin("Aztaroz", "14591459");
//   while (WiFi.status() != WL_CONNECTED){
//     Serial.print(".");
//     delay(300);
//   }
//   Serial.printf("\nConnected IP Address: ");
//   Serial.println(WiFi.localIP().toString());
//   server.begin();
// }

// void setup() {
//   Serial.begin(9600);
//   init_wifi();


// void loop() {
//   // WiFiClient client = server.available();
//   if (!client)
//     return;
//   while (!client.available()){
//     delay(1);
//   }

//   String ret_msg = "<h1>10<h1>";
//   client.println("HTTP/1.0 200 OK");
//   client.println("Content-Type: text/html");
//   client.println("");
//   client.println(ret_msg);
//   delay(1);

// }

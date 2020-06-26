/************************************************
This project uses ESP8266 NODEMCU ESP12-E and DHT11
author: sergio lucio
github: srg-lc
email: sergiolucio.ns@gmail.com

See README on https://github.com/srg-lc/IoT_Termometer
for circuit scheeme and instructions
*************************************************/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

//DHT Area
#define DHTPIN D3 // set the pin that DHT is connected to
#define DHTTYPE DHT11 // set the DHT version
DHT dht(DHTPIN, DHTTYPE); // declares the DHT object
int t,h;

//Wifi area
const char* ssid = "IEEE 802.11"; // Set here SSID of your wifi network
const char* password = "EAEA939308"; // Password of your wifi network
const char* mqtt_broker = "mqtt.eclipse.org"; // Change for your MQTT Broker prefered
WiFiClient nodemcuClient;
PubSubClient client(nodemcuClient);

void setup() {
  Serial.begin(9600);
  dht.begin(); // initialize dht
  Serial.println("\n\n***************************************");
  Serial.println(" Initializing IoT Termometer...");
  wifi_connect();
  client.setServer(mqtt_broker,1883); // Set your MQTT server and port
  pinMode(LED_BUILTIN, OUTPUT); // declares internal LED
}

void loop() {
  if (!client.connected()) {
    reconnect_MQTT();
  }
  DHT_readings();
  publish_MQTT();
  delay(5000);
}

// Function establishes connection with wifi network
void wifi_connect(){
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println("***************************************\n\n");
}

//Seeks to re-establish the connection with the MQTT broker
void reconnect_MQTT(){
  while (!client.connected()) {
    client.connect("IoT_Termometer");
    Serial.println("Reconnecting MQTT...");
  }
}

// Function that takes dht readings and show results
void DHT_readings(){
  // Reading temperature or humidity takes about 250 milliseconds!
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

}

// Function publish readings in MQTT topic
void publish_MQTT(){
  // The true parameter persist information in topic
  client.publish("lab/temp", String(t).c_str(), true);
  client.publish("lab/humid", String(h).c_str(), true);

  // A series of prints to show readings
  Serial.println("\n---------------------------------------");
  Serial.println("Temperature and Humidity Readings: \n");
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

  // Shows publication success in the MQTT topic blinking internal led
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
}

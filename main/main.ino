#include <DHTesp.h>

#include <ESP8266MQTTClient.h>
#include <ESP8266WiFi.h>

// our settings are in config.h.
// This is where we set our wifi and mqtt host details
#include "config.h"

MQTTClient mqtt;
DHTesp dht;

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to Wifi...");
  WiFi.begin("Perl Home", "00112233445566778899101112");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected, IP address ");
  Serial.println(WiFi.localIP());

  mqtt.onConnect([]() {
    Serial.println("MQTT Connected");
  });

  Serial.println("Calling MQTT begin");
  mqtt.begin("mqtt://mqtt.fritz.box:1883");

  Serial.println("Getting temperature and humidity readings");
  dht.setup(DHTPIN, DHTesp::DHT22);
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Unable to read from DHT sensor");
  }
  mqtt.publish("shed/temperature", String(temperature, 2), 0, 0);
  mqtt.handle();
  mqtt.publish("shed/humidity", String(humidity, 2), 0, 0);
  mqtt.handle();
  yield();
  delay(5000);
  yield();

  // deepsleep for 30 seconds. When we wake up we start in setup() again.
  ESP.deepSleep(30e6);
}

void loop() {
  Serial.println("In loop");
}

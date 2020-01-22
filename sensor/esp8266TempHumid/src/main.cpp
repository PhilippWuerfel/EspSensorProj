#include <Arduino.h>
#include "sensor/sht30.h"
#include "wifi/wifimanager.h"
#include <ArduinoJson.h>
#include "PubSubClient.h"

using namespace std;

// Setup IP from Broker
const char* MQTT_BROKER = "192.168.178.36";
const char* DEVICE_NAME = "ESP8266-Room404";
char sensorTime [80];

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char mqttMsg[500];
int value = 0;

// Connect with MQTT Broker
void reconnect() {
    while (!client.connected()) {
        Serial.print("Reconnecting...");
        if (!client.connect("ESP8266Client")) {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds");
            delay(5000);
        }
    }
}

// Setting up time
#include <time.h>
#define MIN_EPOCH 40 * 365 * 24 * 3600 // Times before 2010 (1970 + 40 years) are invalid
const int time_offset_sec = 3600;
static void initTime() {  
   time_t epochTime;
   configTime(time_offset_sec, 0, "pool.ntp.org", "time.nist.gov");

   while (true) {
       epochTime = time(NULL);

       if (epochTime < MIN_EPOCH) {
           Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
           delay(2000);
       } else {
          //  Serial.print("Fetched NTP epoch time is: ");
          //  Serial.println(epochTime);
           time(&epochTime);
           strftime(sensorTime, 80, "%F %H:%M:%S" ,localtime(&epochTime));
           // Serial.println(sensorTime);
           break;
       }
   }
}

// Sensor for humidity and temperature
Sht30 sht30 = Sht30();

// Class to connect ESP with WiFi
WifiManager wifimanager = WifiManager();
// implement connection to cloud here
// tbd

// setup intervall of measuring and sending data to iot hub
const int measure_intervall = 60000; // [ms]

void setup() {
  Serial.begin(115200);
  wifimanager.connect();

  // Set server connection for MQTT to Broker (Raspberry Pi)
  client.setServer(MQTT_BROKER, 1883);
}

void loop() {
 
  // handle updates via OTA
  wifimanager.handleUpdates();

  // Measure with SHT30, false if measurment fails
  if(sht30.measure()){

    // Serial.print("Temperature in Celsius : ");
    // Serial.println(sht30.getTempCelsius());
    // Serial.print("Relative Humidity : ");
    // Serial.println(sht30.getHumidity());
    // Serial.println();

    // Measurment succesfull --> connect ESP as client with MQTT Broker
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    
    // setup time (necessary to send time on sensor to cloud)
    initTime();

    // build json document with measurment data which will be published to MQTT Broker
    StaticJsonDocument<256> doc;
    doc["device"] = "ESP8266-00001";
    doc["temperature"] = String(sht30.getTempCelsius());
    doc["humidity"] = String(sht30.getHumidity());
    doc["sensortime"] = sensorTime;

    serializeJson(doc, mqttMsg);
    Serial.print("Publish message: ");
    Serial.println(mqttMsg);
    client.publish("/iot/temphumid", mqttMsg);
    client.disconnect();

  }
  else
  {
    Serial.println("Error!");
  }

  Serial.println("wait...");
  delay(measure_intervall); // if aim is to install extern power source (eg. battery) -> increase measure_intervall and turn esp into sleep mode
}
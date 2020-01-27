/**
 * ** GNU General Public License Usage
 ** This file may be used under the terms of the GNU
 ** General Public License version 3 or (at your option) any later version
 ** approved by the KDE Free Qt Foundation. The licenses are as published by
 ** the Free Software Foundation and appearing in the file LICENSE.GPL3
 ** included in the packaging of this file. Please review the following
 ** information to ensure the GNU General Public License requirements will
 ** be met: https://www.gnu.org/licenses/gpl-3.0.html.* 
 * 
 * description     :Entry point of ESP8266 with sensor SHT30
 *                  main.cpp handles measurement of sensordata (temperature and humidity) and the connections to the MQTT Broker via IP-Adress 
 *                  and establishes the WiFi connection
 * 
 *                  Setup                 
 *                  1. Setup serial communication for serial monitor
 *                  2. Try connection with WiFi network until it is successfull
 *                  3. Set server for PubSubClient with MQTT Broker (e.g. Raspberry Pi)
 * 
 *                  Loop
 *                  1. ESP will be available for OTA-updates by using the method handleUpdates() of wifimanager
 *                  2. ESP will measure via the SHT30-object (retrieve data from SHT30-sensor)
 *                  3. ESP will connect to MQTT Broker (try connect till connection sucessful)
 *                  4. ESP will initialize the time via WiFi connection by retrieving actual time from pool.ntp.org and time.nist.gov
 *                  5. ESP will build the Json document and fill it with device name, temperature value, humidity value and current time on sensor
 *                  6. ESP will publish the Json (message) to the channel /iot/temphumid
 *                  7. ESP will disconnect from MQTT Broker
 *                  8. ESP will delay for the measure_intervall which is set as a constant before setup
 *                  
 * author          :Philipp Wuerfel
 * date            :2019-11-20
 * version         :1.0
 * notes           :Still running tests in prototype environment, ready for next phase
 * language        :C++
*/


#include <Arduino.h>
#include "sensor/sht30.h"  // used for measurement via installed SHT30-Sensor
#include "wifi/wifimanager.h"  // Used to establish WiFi Connection
#include <ArduinoJson.h>  // Used for creation of Json document which will be send to MQTT Broker
#include "PubSubClient.h"  // Used to implement MQTT Protocol

using namespace std;

// Setup IP from Broker
const char* MQTT_BROKER = "192.168.178.36"; // enter IP of the MQTT Broker (e.g. IP of Raspberry Pi where gateway.py is running)
const char* DEVICE_NAME = "ESP8266-Room404";
char sensorTime [80];

// Create a WiFiClient espClient which is used for WiFi-connection and by PubSubClient
// the PubSub client in the implementation of publishing abd subscribing via MQTT protocol
// therefore the PubSubClient needs a WiFiClient which handles the internet connection making communication in network possible
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

// Setting up time to implement the time of measurement which will be send additionally to the sensordata
#include <time.h>
#define MIN_EPOCH 40 * 365 * 24 * 3600 // Times before 2010 (1970 + 40 years) are invalid
const int time_offset_sec = 3600;
// method used to retrieve time by accessing the website pool.ntp.org and time.nist.gov
static void initTime() {  
   time_t epochTime;
   configTime(time_offset_sec, 0, "pool.ntp.org", "time.nist.gov");
   // try to retrieve time until sucessfull
   while (true) {
       epochTime = time(NULL);

       if (epochTime < MIN_EPOCH) {
           Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
           delay(2000);
       } else {
           time(&epochTime);
           strftime(sensorTime, 80, "%F %H:%M:%S" ,localtime(&epochTime));
           break;
       }
   }
}

// Sensor for humidity and temperature
Sht30 sht30 = Sht30();

// Class to connect ESP with WiFi
WifiManager wifimanager = WifiManager();

// setup intervall of measuring --> ESP will delay after the loop
const int measure_intervall = 5000; // [ms]

void setup() {
  Serial.begin(115200);
  // connect to WiFi-Network
  wifimanager.connect();

  // Set server connection for MQTT to Broker (e.g. Raspberry Pi) over port 1883
  client.setServer(MQTT_BROKER, 1883);
}

void loop() {
 
  // handle updates via OTA
  wifimanager.handleUpdates();

  // Measure with SHT30, false if measurment fails
  if(sht30.measure()){

    Serial.print("Temperature in Celsius : ");
    Serial.println(sht30.getTempCelsius());
    Serial.print("Relative Humidity : ");
    Serial.println(sht30.getHumidity());
    Serial.println();

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

    // serialize json to variable mqttMsg to make it sendable
    serializeJson(doc, mqttMsg);
    Serial.print("Publish message: ");
    Serial.println(mqttMsg);
    // publish on channel /iot/temphumid on which the MQTT Broker will listen
    client.publish("/iot/temphumid", mqttMsg);
    client.disconnect();

  }
  else
  { // print error message if measurement goes wrong
    Serial.println("Error!");
  }

  Serial.println("wait...");
  delay(measure_intervall); // delay ESP to decrease amount of used data and energy
  // sidenote: If aim is to install extern power source (eg. battery) -> increase measure_intervall and turn esp into sleep mode instead
}
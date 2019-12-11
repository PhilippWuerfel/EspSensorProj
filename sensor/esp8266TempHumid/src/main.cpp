#include <Arduino.h>
#include "sensor/sht30.h"
#include "wifi/wifimanager.h"
#include "cloud/azuremanager.h"

// Setting up time
#include <time.h>
#define MIN_EPOCH 40 * 365 * 24 * 3600 // Times before 2010 (1970 + 40 years) are invalid

static void initTime() {  
   time_t epochTime;

   configTime(0, 0, "pool.ntp.org", "time.nist.gov");

   while (true) {
       epochTime = time(NULL);

       if (epochTime < MIN_EPOCH) {
           Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
           delay(2000);
       } else {
           Serial.print("Fetched NTP epoch time is: ");
           Serial.println(epochTime);
           break;
       }
   }
}

Sht30 sht30 = Sht30();
WifiManager wifimanager = WifiManager();
char msg[100];
AzureManager azuremanager = AzureManager();

void setup() {
  Serial.begin(115200);
  wifimanager.connect();
}

void loop() {
  /*
    Think about efficiency : 
      - jump into sleep mode between measure intervalls
    Think about configurations:
      - edit measure intervalls from cloud
  */

  wifimanager.handleUpdates();

  // test prints of sht30 sensor
  if(sht30.measure()){
    Serial.print("Temperature in Celsius : ");
    Serial.println(sht30.getTempCelsius());
    Serial.print("Relative Humidity : ");
    Serial.println(sht30.getHumidity());
    Serial.println();
  }
  else
  {
    Serial.println("Error!");
  }

  // https://github.com/esp8266/Arduino/issues/
  // https://github.com/Azure-Samples/iot-hub-c-huzzah-getstartedkit
  // https://clemenssiebler.com/building-an-iot-setup-with-nodemcu-and-azure-iot-hub-on-macos/
  // try send data of sht30 to azure cloud

  Serial.println("Trying to send IoTHubMessage");
  sprintf(msg, "{ 'humidity': %.2f,'temperature':%.2f }", sht30.getHumidity(), sht30.getTempCelsius());  
  
  Serial.println(msg);
  
  initTime();
  azuremanager.sendMsg(msg);
  
  Serial.println("wait...");
  delay(1000); // here could be a editable measure intervall
}
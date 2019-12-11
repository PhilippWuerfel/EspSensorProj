#include <Arduino.h>
#include "sensor/sht30.h"
#include "wifi/wifimanager.h"

// new untested code
// #include <time.h>

// Times before 2010 (1970 + 40 years) are invalid
// #define MIN_EPOCH 40 * 365 * 24 * 3600

// #include <AzureIoTHub.h>
// #include <AzureIoTProtocol_HTTP.h>
// char msg[100];
// #define IOT_CONFIG_CONNECTION_STRING ""

// IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle = nullptr;

// static void initTime() {  
//    time_t epochTime;

//    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

//    while (true) {
//        epochTime = time(NULL);

//        if (epochTime < MIN_EPOCH) {
//            Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
//            delay(2000);
//        } else {
//            Serial.print("Fetched NTP epoch time is: ");
//            Serial.println(epochTime);
//            break;
//        }
//    }
// }

// new untested code

Sht30 sht30 = Sht30();
WifiManager wifimanager = WifiManager();

void setup() {
  Serial.begin(115200);
  wifimanager.connect();

  // new untested code
  // initTime();
  // // Init IoT client
  // //
  // iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(IOT_CONFIG_CONNECTION_STRING, HTTP_Protocol);
  // if (iotHubClientHandle == NULL)
  // {
  //     Serial.println("Failed on IoTHubClient_LL_Create");
  // }
  
  // new untested code
}

void loop() {
  /*
    Think about efficiency : 
      - jump into sleep mode between measure intervalls
    Think about configurations:
      - edit measure intervalls from cloud
  */


  wifimanager.handleUpdates();

  // test prints, send data to cloud here
  if(sht30.measure()){
    Serial.print("Temperature in Celsius : ");
    Serial.println(sht30.getTempCelsius());
    Serial.print("Temperature in Fahrenheit : ");
    Serial.println(sht30.getTempFahrenheit());
    Serial.print("Relative Humidity : ");
    Serial.println(sht30.getHumidity());
    Serial.println();
  }
  else
  {
    Serial.println("Error!");
  }

  // new untested code
  // https://github.com/esp8266/Arduino/issues/5787
  // try send data to azure cloud

  // Serial.println("trying to send IoTHubMessage");

  // sprintf(msg, "{ 'humidity': %.2f,'temperature':%.2f }", sht30.getHumidity(), sht30.getTempCelsius());  
  // IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray((const unsigned char *)msg, strlen(msg));
  // if (messageHandle == NULL)
  // {
  //   Serial.println("unable to create a new IoTHubMessage");
  // }
  // else
  // {                           
  //   if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, nullptr, nullptr) != IOTHUB_CLIENT_OK)
  //   {
  //     Serial.println("failed to hand over the message to IoTHubClient");
  //   }
  //   else
  //   {
  //     Serial.println("IoTHubClient accepted the message for delivery");
  //   }
  //   IoTHubMessage_Destroy(messageHandle);
  // }
  
  // IOTHUB_CLIENT_STATUS status;
  // while ((IoTHubClient_LL_GetSendStatus(iotHubClientHandle, &status) == IOTHUB_CLIENT_OK) && (status == IOTHUB_CLIENT_SEND_STATUS_BUSY))
  // {
  //     IoTHubClient_LL_DoWork(iotHubClientHandle);
  //     ThreadAPI_Sleep(100);
  // }
  
  // Serial.println("wait...");
  // delay(1000);



  // new untested code
}
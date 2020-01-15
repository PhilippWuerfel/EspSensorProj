// currently not activated as there is no connection to azure-cloud necessary (reached via gateway with MQTT)

// #include <time.h>
// #include <HardwareSerial.h>
// #include <AzureIoTHub.h>
// // #include <AzureIoTProtocol_HTTP.h>
// #include <AzureIoTProtocol_MQTT.h>

// // #include<string>

// #define IOT_CONFIG_CONNECTION_STRING "HostName=iottest8266.azure-devices.net;DeviceId=ESP8266;SharedAccessKey=wF8UYMSkHJmEfj6CyxUTVRbmJr78rPLK6poTFh4K9g4="
// // #define IOT_CONFIG_CONNECTION_STRING "HostName=TemperatureAndHumidity.azure-devices.net;DeviceId=raspberrypi;SharedAccessKey=fRqt8STDhQZpoGwgS7NcgmeNpp+v3o7Jte7O0uM0mw0="

// class AzureManager{

//     private:
//         IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle = nullptr;
//         const char *connectionString;
//         // tbd
//     public:
//         AzureManager();
//         AzureManager(const char *connectionString);
//         ~AzureManager();
        
//         void sendMsg(char msg[]);
//         // tbd

// };
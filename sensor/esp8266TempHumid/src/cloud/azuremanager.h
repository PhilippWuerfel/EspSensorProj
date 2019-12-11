#include <time.h>
#include <HardwareSerial.h>
#include <AzureIoTHub.h>
// #include <AzureIoTProtocol_HTTP.h>
#include <AzureIoTProtocol_MQTT.h>

// Times before 2010 (1970 + 40 years) are invalid
#define MIN_EPOCH 40 * 365 * 24 * 3600

#define IOT_CONFIG_CONNECTION_STRING "HostName=iottest8266.azure-devices.net;DeviceId=ESP8266;SharedAccessKey=wF8UYMSkHJmEfj6CyxUTVRbmJr78rPLK6poTFh4K9g4="

class AzureManager{

    private:
        IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle = nullptr;
        // tbd
    public:
        AzureManager();
        ~AzureManager();
        
        void sendMsg(char msg[]);
        // tbd

};
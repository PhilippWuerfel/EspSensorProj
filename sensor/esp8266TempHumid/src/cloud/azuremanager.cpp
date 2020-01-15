// currently not activated as there is no connection to azure-cloud necessary (reached via gateway with MQTT)

// #include "azuremanager.h"

// using namespace std;

// AzureManager::AzureManager(){
//     // iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(IOT_CONFIG_CONNECTION_STRING, HTTP_Protocol);
//     iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(IOT_CONFIG_CONNECTION_STRING, MQTT_Protocol);
//     if (iotHubClientHandle == NULL)
//     {
//         Serial.println("Failed on IoTHubClient_LL_Create");
//     }
// }
// AzureManager::AzureManager(const char *connectionString){
//     this -> connectionString = connectionString;
//     // iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, HTTP_Protocol);
//     iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, MQTT_Protocol);
//     if (iotHubClientHandle == NULL)
//     {
//         Serial.println("Failed on IoTHubClient_LL_Create");
//     }
// }

// AzureManager::~AzureManager(){
// };

// void AzureManager::sendMsg(char msg[]){
    
//     IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray((const unsigned char *)msg, strlen(msg));
//     if (messageHandle == NULL)
//     {
//         Serial.println("unable to create a new IoTHubMessage");
//     }
//     else
//     {                           
//         if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, nullptr, nullptr) != IOTHUB_CLIENT_OK)
//         {
//         Serial.println("failed to hand over the message to IoTHubClient");
//         }
//         else
//         {
//         Serial.println("IoTHubClient accepted the message for delivery");
//         }
//         IoTHubMessage_Destroy(messageHandle);
//     }
    
//     // break manually out of loop as currently IOTHub is currently not responding correctly
//     int count = 0;

//     IOTHUB_CLIENT_STATUS status;
//     while ((IoTHubClient_LL_GetSendStatus(iotHubClientHandle, &status) == IOTHUB_CLIENT_OK) && (status == IOTHUB_CLIENT_SEND_STATUS_BUSY))
//     {
//         IoTHubClient_LL_DoWork(iotHubClientHandle);
//         ThreadAPI_Sleep(100);
        
//         // break manually out of loop as currently IOTHub is currently not responding correctly
//         if(count == 100){
//             break;
//         }else{
//             count ++;
//         }
//     }
    
// }
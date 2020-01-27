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
 * CURRENTLY DEACTIVATED as there is currently no connection to azure-cloud necessary (reached via gateway with MQTT)
 * 
 * 
 * description     :Manager which handles the communication to AzureCloud via IoT-Hub
 * 
 * variables       :
 *                 private
 *                  connectionString -> connection string which will establish the connection to the wanted adress
 * 
 * methods         :
 *                 public
 *                  AzureManager() and ~AzureManager() -> Constructor and Destructor
 *                  sendMsg(char msg[]) -> sends the measurement data to AzureCloud
 *                                         parameter is a char array which will be basically in json format
 *                  
 * author          :Philipp Wuerfel
 * date            :2019-11-15
 * version         :1.0
 * notes           :Currently deactivated
 * language        :C++
*/

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
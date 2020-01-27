#include "wifimanager.h"

WifiManager::WifiManager(){
}
WifiManager::~WifiManager(){
};

void WifiManager::connect(){
    // resource check on: https://www.youtube.com/watch?v=lXchL3hpDO4

    // establish WiFi connection
    Serial.println("Booting...");    
    WiFi.mode(WIFI_STA); // setup WiFi mode
    WiFi.begin(STASSID, STAPSK);  // connect to WiFi network via the given id and pw

    // connect till status WL_CONNECTED retrieved
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    // establish ArduinoOTA-protocoll and handle all necessarry / possible OTA-Status
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
        } else { // U_FS
        type = "filesystem";
        }
        // NOTE: if updating FS this would be the place to unmount FS using FS.end()
        Serial.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
        Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
        Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
        Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
        Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
        Serial.println("End Failed");
        }
    });
    ArduinoOTA.begin();
    Serial.println("Ready to rumble");
    
    // print IP adress which could be used in MQTT Broker
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}

void WifiManager::handleUpdates(){
    ArduinoOTA.handle();
}

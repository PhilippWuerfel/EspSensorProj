#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "TransEatSleepRepeat"//"SiPommesNo"//"FredsG6"//"TransEatSleepRepeat"
#define STAPSK  "Eat5$BurgerDrink8CervezaSleep6HoursRepeat"//"QuadroCalzones133$"//"stirnbandhefterkoks"//"Eat5$BurgerDrink8CervezaSleep6HoursRepeat"
#endif

class WifiManager{

    private:
        const char* ssid = STASSID;
        const char* password = STAPSK;
    public:
        WifiManager();
        ~WifiManager();

        void connect();
        void handleUpdates();
};
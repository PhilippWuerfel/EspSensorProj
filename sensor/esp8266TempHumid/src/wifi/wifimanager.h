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
 * description     :WifiManager which handles the connection to WiFi and updates via OTA
 * 
 * variables       :
 *                 private
 *                  ssid -> holds id / name of WiFi network
 *                  password -> holds password of WiFi network
 * 
 * methods         :
 *                 public
 *                  WifiManager() and ~WifiManager() -> Constructor and Destructor
 *                  connect() -> Handle connection to WiFi-network and also makes OTA-Setup
 *                  handleUpdates() -> Handle OTA-updates
 *                      sidenote: Call connect() before handleUpdates as it will establish OTA-Setup
 *                  
 * author          :Philipp Wuerfel
 * date            :2019-11-20
 * version         :1.0
 * notes           :Still running tests in prototype environment, ready for next phase
 * language        :C++
*/

#ifndef WIFIMANAGER_H
#define WIFIMANGER_H

#include <ESP8266WiFi.h> // bib to establish WiFi connection on ESP8266
#include <ESP8266mDNS.h> // bib to establish DNS on ESP8266
#include <WiFiUdp.h>  // bib to implement UDP protocol on ESP8266
#include <ArduinoOTA.h> // bib to implement OTA upates on ESP8266

#ifndef STASSID
#define STASSID "TransEatSleepRepeat" // enter name of WLAN Network here
#define STAPSK "Eat5$BurgerDrink8CervezaSleep6HoursRepeat"  // enter pw of WLAN Network here
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

#endif
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
 *                  sht30 -> creates sht3x object of importet lib WEMOS_SHT3X
 * 
 * methods         :
 *                 public
 *                  Sht30() and ~Sht30() -> Constructor and Destructor
 *                  measure() -> calls the measure method on sht3x object
 *                            -> returns boolean: true if measurement sucessfull and false if not
 *                  getTempCelsius() -> retrieves the measured temperature value in Celius of sht3x object
 *                            -> returns float
 *                  getTempFahrenheit()-> retrieves the measured temperature value in Fahrenheit of sht3x object
 *                            -> returns float
 *                  getHumidity() -> retrieves the measured temperature value in Percent of sht3x object
 *                            -> returns float
 *                  
 * author          :Philipp Wuerfel
 * date            :2019-11-20
 * version         :1.0
 * notes           :Still running tests in prototype environment, ready for next phase
 * language        :C++
*/

#ifndef SHT30_H
#define SHT30_H

#include <WEMOS_SHT3X.h> // lib to implement measurement via SHT30 Sensor on ESP8266

class Sht30{
    private:
        SHT3X sht30;
    public:
        Sht30();
        ~Sht30();

        bool measure();
        float getTempCelsius();
        float getTempFahrenheit();
        float getHumidity();
};

#endif
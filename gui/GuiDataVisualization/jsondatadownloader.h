#ifndef JSONDATADOWNLOADER_H
#define JSONDATADOWNLOADER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

class JsonDataDownloader
{
public:
    JsonDataDownloader();
  static  QJsonArray getDataArray();    // returns a QJsonArray of the measurements data
private:
 static   QJsonDocument downloadJsonData(); // retrieves the sensor data from the database
};

#endif // JSONDATADOWNLOADER_H

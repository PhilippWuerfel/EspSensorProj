#include "jsondatadownloader.h"

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

JsonDataDownloader::JsonDataDownloader(){}

/*
 * retrieves all the sensor data via a http.get()
 * returns a QJsonDocument with all the sensor data in it
 */
 QJsonDocument JsonDataDownloader::downloadJsonData()
{
    QNetworkAccessManager nam;
    // the web url for the http.get()
    QNetworkRequest request(QUrl("https://webhooks.mongodb-stitch.com/api/client/v2.0/app/connecteddevices-fyecb/service/HttpGetAllData/incoming_webhook/HttpGetAllDataWebhook"));

    // the data the get request retrieves
    QNetworkReply *reply = nam.get(request);
    while(!reply->isFinished()){
        qApp->processEvents();
    }
    // parse the data into a QString
    QString data = (QString) reply->readAll();
    reply->deleteLater();

    return QJsonDocument::fromJson(data.toUtf8());
}
 /*
  * downloads all the data and converts it into a QJsonArray which it returns
  */
 QJsonArray JsonDataDownloader::getDataArray()
{
    // downloading the sensor data
    QJsonObject jsonObj = downloadJsonData().object();
    // getting all the measurements array from the document
    QJsonArray dataArray = jsonObj.value(QString("measurements")).toArray();
    return dataArray;
}

//#include "jsondatadownloader.h"

//#include <QtNetwork>
//#include <QNetworkAccessManager>
//#include <QNetworkReply>
//#include <QNetworkRequest>

//#include <QJsonArray>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonValue>

//JsonDataDownloader::JsonDataDownloader()// in den Konstruktor vielleicht noch die adresse packen?
//{

//}

//// QJsonDocument JsonDataDownloader::downloadJsonData()
////{
////    QNetworkAccessManager nam;
////    QNetworkRequest request(QUrl("https://webhooks.mongodb-stitch.com/api/client/v2.0/app/connecteddevices-fyecb/service/HttpGetAllData/incoming_webhook/HttpGetAllDataWebhook"));

////    QNetworkReply *reply = nam.get(request);
////    while(!reply->isFinished()){
////        qApp->processEvents();
////    }
////    QString data = (QString) reply->readAll();
////    //QByteArray response_data = reply->readAll();    //DELETE funktioniert ja offensichtlich nicht
////    reply->deleteLater();

////    return QJsonDocument::fromJson(data.toUtf8()); //response_data);    // DELETE , also nur den kommentar nicht die ganze Zeile
////}
// QJsonArray JsonDataDownloader::getDataArray()
//{

//    QJsonObject jsonObj = downloadJsonData().object();
//    QJsonArray dataArray = jsonObj.value(QString("measurements")).toArray();
//    return dataArray;
//}

////  TBD
////QJsonObject JsonDataDownloader::getLastDataPoint(){
////    QJsonObject jsonObj = downloadJsonData().object();

////    return jsonObj;
////}


//// GET JSON DATA FROM A FILE: ==========================================
//// QJsonArray JsonDataDownloader::getDataArray()
////   {
////   QString jsonString = downloadJsonData();
////   QJsonDocument dataDoc = QJsonDocument::fromJson(jsonString.toUtf8());
////   QJsonArray dataArray = dataDoc.array();
////   return dataArray;
////   }
//// void JsonDataDownloader::downloadJsonData()
//// {
////   QFile file;
////   QString jsonString;
////   file.setFileName("C:\\Users\\grego\\Desktop\\Vertiefung Projekt 30_11_19\\EspSensorProj\\gui\\GuiDataVisualization\\somedata.json");
////   file.open(QIODevice::ReadOnly | QIODevice::Text);
////   jsonString = file.readAll();
////   file.close();
////   return jsonString;
//// }

// QJsonDocument JsonDataDownloader::downloadJsonData()
// {
//   QFile file;
//   QString jsonString;
//   file.setFileName("C:\\Users\\grego\\Desktop\\Vertiefung Projekt 30_11_19\\EspSensorProj\\gui\\GuiDataVisualization\\somedata.json");
//   file.open(QIODevice::ReadOnly | QIODevice::Text);
//   jsonString = file.readAll();
//   file.close();
//   QJsonDocument dataDoc = QJsonDocument::fromJson(jsonString.toUtf8());
//   return dataDoc;
// }


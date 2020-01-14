#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


//#include "jsondatadownloader.h"


// The main window to which you add toolbars,
// menubars, widgets and status bar
#include <QtWidgets/QMainWindow>

// Widget used to display charts
#include <QtCharts/QChartView>

// Used to draw bars representing data provided
// grouped into categories
#include <QtCharts/QBarSeries>

// Represents 1 set of bars in a bar chart
#include <QtCharts/QBarSet>

// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>

// Adds categories to the charts axes
#include <QtCharts/QBarCategoryAxis>

// Used to create stacked bar charts
#include <QtCharts/QHorizontalStackedBarSeries>

// Used to create a line chart
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QCategoryAxis>

// Used to make Pie Charts
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>


#include <QJsonObject>

QT_CHARTS_USE_NAMESPACE

#include "graphhandler.h"

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


//QUrl urlLastDataPoint = //IM MOMENT NOCH ALLE PUNKTE
//        QUrl("https://webhooks.mongodb-stitch.com/api/client/v2.0/app/connecteddevices-fyecb/service/HttpGetAllData/incoming_webhook/HttpGetAllDataWebhook");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // getData()

//    GraphHandler* grh = new GraphHandler();
//    QChart* pieChartHum = grh->createHumPieChart();
//    ui->dounutHum->setChart(pieChartHum);
    refresh();

    //createHumidityPie();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnShowChartWindow_clicked()
{
    graphWindow = new GraphWindow(this);
    graphWindow->grabGesture(Qt::PanGesture);
    graphWindow->grabGesture(Qt::PinchGesture);
    graphWindow->show();
}

QJsonObject MainWindow::getNewestDataPoint(){
    QJsonDocument doc = downloadJsonDataOnline();
    QJsonArray array = doc.object().value(QString("measurements")).toArray();
    QJsonValue value = array.last();
    QJsonObject newestDataPoint = value.toObject();

    return newestDataPoint;
}

QJsonDocument MainWindow::downloadJsonDataOnline() //DELETE -> oder umschreiben so dass halt nur ein Datenpunkt empfangen wird
{
    QNetworkAccessManager nam;
    QNetworkRequest request(QUrl("https://webhooks.mongodb-stitch.com/api/client/v2.0/app/connecteddevices-fyecb/service/HttpGetAllData/incoming_webhook/HttpGetAllDataWebhook"));

    QNetworkReply *reply = nam.get(request);
    while(!reply->isFinished()){
        qApp->processEvents();
    }
    QString data = (QString) reply->readAll();
    reply->deleteLater();

    return QJsonDocument::fromJson(data.toUtf8());
}

// to refresh/update the data in the main window
void MainWindow::refresh(){
    // get data
    QJsonObject newData = getNewestDataPoint();
    double tempr = newData.value(QString("temperature"))
            .toObject().value(QString("$numberDouble")).toString().toDouble();
    double humi = newData.value(QString("humidity"))
            .toObject().value(QString("$numberDouble")).toString().toDouble();

//    GraphHandler* grh = new GraphHandler();   // DELETE -> piechart wurde rausgewählt
//    QChart* pieChartHum = grh->createHumPieChart(humi);
    //ui->lcdTemp->setPalette(); // DELETE -> wenn ich es über den Designer hinbekomme
    ui->lcdTemp->display(tempr);
    ui->lcdHum->display(humi);
   // ui->dounutHum->setChart(pieChartHum); DELETE
}

void MainWindow::on_refreshButton_clicked()
{
    refresh();
}


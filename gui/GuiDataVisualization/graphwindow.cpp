#include "graphwindow.h"
#include "ui_graphwindow.h"

// Manages the applications main settings like
// widget initialization
#include <QApplication>

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

// Used to make the y-axis show dates
#include <QDateTimeAxis>

#include <QDateTime>


#include <QJsonObject>

QT_CHARTS_USE_NAMESPACE

#include "graphhandler.h"


//include für zoom
#include "chart.h"

// TEST INCLUDES====================================================

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>

//==================================================================

// for conversion of string to date to int and back
QString dateFormatWindow = "yyyy-MM-dd HH:mm:ss";
// setting the standard boundaries for the diagram axis
int standardMinTemp = 0;
int standardMaxTemp = 30;
int standardMinHum = 0;
int standardMaxHum = 100;
QString firstDate;
QString lastDate;

//QUrl urlAllData =
//        QUrl("https://webhooks.mongodb-stitch.com/api/client/v2.0/app/connecteddevices-fyecb/service/HttpGetAllData/incoming_webhook/HttpGetAllDataWebhook");

// instance of JsonDataDownloader to get the data from the database //DELETE -> brauche ich ja wohl nicht mehr weil ich es nicht nutzen kann...
//JsonDataDownloader *jdownl = new JsonDataDownloader();            // ...außer mit nem Singleton vielleicht

//instance to draw graphs
GraphHandler *grHandler = new GraphHandler();     //jdownl->getDataArray());    //DELETE

//instances for the graphs  // DELETE -> muss das vermutlich so machen wie in der Hausaufgabe (Aufgabe 5 oder so)
//QChart* temperatureChart;// = new QChart();
//QChart* humidityChart;// = new QChart();


GraphWindow::GraphWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);

    // to add a maximize and minimize button to the title bar
    Qt::WindowFlags flags = Qt::Window | Qt::WindowSystemMenuHint
                                | Qt::WindowMaximizeButtonHint
                                | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);

    //refresh();
    // DELETE -> das ist ja eigentlich die refresh()
    // to get all the data from the webservice into a QJsonDocument
    QJsonDocument testdoc = downloadJsonDataOnline();
    QJsonObject jsonObj = testdoc.object();
    QJsonArray jsonArray = jsonObj.value(QString("measurements")).toArray();

    // get the two different charts for temperature and humidity
    Chart* tempChart = grHandler->createTempChart(jsonArray);
    Chart* humChart = grHandler->createHumChart(jsonArray);
    ui->temperatureGraph->setRenderHint(QPainter::Antialiasing);
    ui->temperatureGraph->setChart(tempChart);

    ui->humidityGraph->setChart(humChart);


    // TEST OB DER GET BEFEHL GEHT ==========================================================================
    // wandel ich vielleicht um in die Standardmaßerfassung des Diagramms

    QJsonObject firstDataPoint = jsonArray.first().toObject();
    QString firstTemp = firstDataPoint.value(QString("temperature"))
            .toObject().value(QString("$numberDouble")).toString();
    QString firstHum = firstDataPoint.value(QString("humidity"))
            .toObject().value(QString("$numberDouble")).toString();
    firstDate = firstDataPoint.value(QString("sensortime")).toString();

    QJsonObject lastDataPoint = jsonArray.last().toObject();
    QString lastTemp = lastDataPoint.value(QString("temperature"))
            .toObject().value(QString("$numberDouble")).toString();
    QString lastHum = lastDataPoint.value(QString("temperature"))
            .toObject().value(QString("$numberDouble")).toString();
    lastDate = lastDataPoint.value(QString("sensortime")).toString();

    QString sizeJsonArray = QString::number(jsonArray.size());

    // textViews in temperature tab
    ui->xminValueTemp->setText(firstDate);
    ui->xmaxValueTemp->setText(lastDate);
    ui->yminValueTemp->setText(QString::number(standardMinTemp));
    ui->ymaxValueTemp->setText(QString::number(standardMaxTemp));

    //textViews in humidity tab
    ui->xminValueHum->setText(firstDate);
    ui->xmaxValueHum->setText(lastDate);
    ui->yminValueHum->setText(QString::number(standardMinHum));
    ui->ymaxValueHum->setText(QString::number(standardMaxHum));

    //ui->yminValueText->setText(testErstesEle);

    //ui->xminValueText->setText(sizeJsonArray);


    //=======================================================================================================


}

GraphWindow::~GraphWindow()
{
    delete ui;
}

QJsonDocument GraphWindow::downloadJsonDataOnline()
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


void GraphWindow::on_btnApplyTemp_clicked()
{
    QString minDateString = ui->xminValueTemp->text();
    QDateTime minDateTime = QDateTime::fromString(minDateString, dateFormatWindow);
    QString maxDateString = ui->xmaxValueTemp->text();
    QDateTime maxDateTime = QDateTime::fromString(maxDateString, dateFormatWindow);

    double minTemp = ui->yminValueTemp->text().toDouble();
    double maxTemp = ui->ymaxValueTemp->text().toDouble();

    Chart* chart = (Chart*)ui->temperatureGraph->chart();
    chart->axisX()->setRange(minDateTime, maxDateTime);
    chart->axisY()->setRange(minTemp, maxTemp);
    ui->temperatureGraph->setChart(chart);
}


void GraphWindow::on_btnRefreshTemp_clicked()
{
    refresh();
}

void GraphWindow::on_btnResetTempAxis_clicked()
{
    Chart* chart = (Chart*)ui->temperatureGraph->chart();
    chart->axisX()->setRange(firstDate, lastDate);
    chart->axisY()->setRange(standardMinTemp, standardMaxTemp);
    ui->temperatureGraph->setChart(chart);
}

void GraphWindow::on_btnApplyHum_clicked()
{
    QString minDateString = ui->xminValueHum->text();
    QDateTime minDateTime = QDateTime::fromString(minDateString, dateFormatWindow);
    //double minDate = QDateTime::fromString(minDateString, dateFormatWindow).toMSecsSinceEpoch();  //DELETE
    QString maxDateString = ui->xmaxValueHum->text();
    QDateTime maxDateTime = QDateTime::fromString(maxDateString, dateFormatWindow);
    //double maxDate = QDateTime::fromString(maxDateString, dateFormatWindow).toMSecsSinceEpoch();  //DELETE

    double minHum = ui->yminValueHum->text().toDouble();
    double maxHum = ui->ymaxValueHum->text().toDouble();

    Chart* chart = (Chart*)ui->humidityGraph->chart();
    chart->axisX()->setRange(minDateTime, maxDateTime);
    chart->axisY()->setRange(minHum, maxHum);
    ui->humidityGraph->setChart(chart);
}

void GraphWindow::on_btnResetHumAxis_clicked()
{
    Chart* chart = (Chart*)ui->humidityGraph->chart();
    chart->axisX()->setRange(firstDate, lastDate);
    chart->axisY()->setRange(standardMinHum, standardMaxHum);
    ui->humidityGraph->setChart(chart);
}

void GraphWindow::on_btnRefreshHum_clicked()
{
    refresh();
}
void GraphWindow::refresh(){
    // to get all the data from the webservice into a QJsonDocument
    QJsonDocument testdoc = downloadJsonDataOnline();
    QJsonObject jsonObj = testdoc.object();
    QJsonArray jsonArray = jsonObj.value(QString("measurements")).toArray();

    // get the two different charts for temperature and humidity
    Chart* tempChart = grHandler->createTempChart(jsonArray);
    Chart* humChart = grHandler->createHumChart(jsonArray);
    ui->temperatureGraph->setRenderHint(QPainter::Antialiasing);
    ui->temperatureGraph->setChart(tempChart);

    ui->humidityGraph->setChart(humChart);
}

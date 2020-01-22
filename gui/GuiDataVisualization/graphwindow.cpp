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
// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>
// Adds categories to the charts axes
#include <QtCharts/QBarCategoryAxis>
// Used to create a line chart
#include <QtCharts/QLineSeries>
// Used to change names on axis
#include <QtCharts/QCategoryAxis>
// Used to make the y-axis show dates
#include <QDateTimeAxis>
#include <QDateTime>
// necessary that the QtChart includes work
QT_CHARTS_USE_NAMESPACE
#include "graphhandler.h"
//include für zoom
#include "chart.h"
#include <QJsonObject>
#include "jsondatadownloader.h"

// for conversion of string to date to int and back
QString dateFormatWindow = "yyyy-MM-dd HH:mm:ss";
// initializing the standard  values for the boundaries for the chart axis
int standardMinTemp = 0;
int standardMaxTemp = 30;
int standardMinHum = 0;
int standardMaxHum = 100;
QString firstDate;
QString lastDate;


// instance of JsonDataDownloader to get the data from the database
JsonDataDownloader *jdownlGr = new JsonDataDownloader();

// data array used for this dialog
QJsonArray jsonArray;// = new QJsonArray();

//instance to draw graphs
GraphHandler *grHandler = new GraphHandler();


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

    refresh();

    /*
     * the following lines just get the default values of the axis
     * and set them as strings to the line edits
     */
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

    // textViews in temperature tab to set the chart axis
    ui->xminValueTemp->setText(firstDate);
    ui->xmaxValueTemp->setText(lastDate);
    ui->yminValueTemp->setText(QString::number(standardMinTemp));
    ui->ymaxValueTemp->setText(QString::number(standardMaxTemp));

    // textViews in humidity tab to set the chart axis
    ui->xminValueHum->setText(firstDate);
    ui->xmaxValueHum->setText(lastDate);
    ui->yminValueHum->setText(QString::number(standardMinHum));
    ui->ymaxValueHum->setText(QString::number(standardMaxHum));
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

/*
 * downloads the data again and puts it into the
 * line charts
 */
void GraphWindow::refresh(){
    jsonArray = jdownlGr->getDataArray();

    // get the two different charts for temperature and humidity
    Chart* tempChart = grHandler->createTempChart(jsonArray);
    Chart* humChart = grHandler->createHumChart(jsonArray);
    ui->temperatureGraph->setRenderHint(QPainter::Antialiasing);
    ui->temperatureGraph->setChart(tempChart);

    ui->humidityGraph->setRenderHint(QPainter::Antialiasing);
    ui->humidityGraph->setChart(humChart);
}

/*
 * This click handler applies the changes made in the UI
 * to set the borders of the temperatur line chart
 */
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
/*
 * This click handler sets the borders of the temperature line chart
 * to the default values
 */
void GraphWindow::on_btnResetTempAxis_clicked()
{
    Chart* chart = (Chart*)ui->temperatureGraph->chart();
    chart->axisX()->setRange(firstDate, lastDate);
    chart->axisY()->setRange(standardMinTemp, standardMaxTemp);
    ui->temperatureGraph->setChart(chart);
}
/*
 * calls the refresh function for the temperature line chart
 */
void GraphWindow::on_btnRefreshTemp_clicked()
{
    refresh();
}

/*
 * This click handler applies the changes made in the UI
 * to set the borders of the humidity line chart
 */
void GraphWindow::on_btnApplyHum_clicked()
{
    QString minDateString = ui->xminValueHum->text();
    QDateTime minDateTime = QDateTime::fromString(minDateString, dateFormatWindow);
    QString maxDateString = ui->xmaxValueHum->text();
    QDateTime maxDateTime = QDateTime::fromString(maxDateString, dateFormatWindow);

    double minHum = ui->yminValueHum->text().toDouble();
    double maxHum = ui->ymaxValueHum->text().toDouble();

    Chart* chart = (Chart*)ui->humidityGraph->chart();
    chart->axisX()->setRange(minDateTime, maxDateTime);
    chart->axisY()->setRange(minHum, maxHum);
    ui->humidityGraph->setChart(chart);
}
/*
 * This click handler sets the borders of the humidity line chart
 * to the default values
 */
void GraphWindow::on_btnResetHumAxis_clicked()
{
    Chart* chart = (Chart*)ui->humidityGraph->chart();
    chart->axisX()->setRange(firstDate, lastDate);
    chart->axisY()->setRange(standardMinHum, standardMaxHum);
    ui->humidityGraph->setChart(chart);
}
/*
 * calls the refresh function for the humidity line chart
 */
void GraphWindow::on_btnRefreshHum_clicked()
{
    refresh();
}

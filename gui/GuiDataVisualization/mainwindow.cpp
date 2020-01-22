#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
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
#include <QJsonObject>
QT_CHARTS_USE_NAMESPACE
#include "graphhandler.h"
#include "jsondatadownloader.h"

// instance of JsonDataDownloader to get the data from the database
JsonDataDownloader *jdownlMain = new JsonDataDownloader();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * click handler for the button that opens the graph window
 */
void MainWindow::on_btnShowChartWindow_clicked()
{
    graphWindow = new GraphWindow(this);
    graphWindow->grabGesture(Qt::PanGesture);
    graphWindow->grabGesture(Qt::PinchGesture);
    graphWindow->show();
}
/*
 * gets the newest data array and returns the last data point of that array as QJsonObject
 */
QJsonObject MainWindow::getNewestDataPoint(){
    QJsonArray array = jdownlMain->getDataArray();
    QJsonValue value = array.last();
    QJsonObject newestDataPoint = value.toObject();

    return newestDataPoint;
}
/*
 * refreshs/updates the data in the main window
 */
void MainWindow::refresh(){
    // get the data of the last/newest measurement point
    QJsonObject newData = getNewestDataPoint();
    double tempr = newData.value(QString("temperature"))
            .toObject().value(QString("$numberDouble")).toString().toDouble();
    double humi = newData.value(QString("humidity"))
            .toObject().value(QString("$numberDouble")).toString().toDouble();
    // display the data in the window
    ui->lcdTemp->display(tempr);
    ui->lcdHum->display(humi);
}

void MainWindow::on_refreshButton_clicked()
{
    refresh();
}

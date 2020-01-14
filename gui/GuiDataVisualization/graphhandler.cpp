#include "graphhandler.h"


// Manages the applications main settings like
// widget initialization
#include <QApplication>

// The main window to which you add toolbars,
// menubars, widgets and status bar
#include <QtWidgets/QMainWindow>

// =============== Chart includes: ===============
// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>

// Used to change names on axis
#include <QtCharts/QCategoryAxis>

// Used to make Pie Charts
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

// Used to make the y-axis show dates
#include <QDateTimeAxis>

QT_CHARTS_USE_NAMESPACE

// =============== JSON includes: ===============
#include <QJsonObject>

// for passing the lineedits; can probably be DELETEd
#include<QWidget>
//for showing the graphdata in a tooltip
#include<QToolTip>

// to parse string to date and other way round
QString dateFormat = "yyyy-MM-dd HH:mm:ss";
QString dateFormatChart = "yyyy-MM-dd HH:mm";


// custom class to allow showing a tooltip for the chart where to mouse cursor touches the graph line
class LineSeries: public QLineSeries{
public:
    LineSeries(QObject *parent = nullptr):
        QLineSeries(parent)
    {
        connect(this, &QXYSeries::clicked, this, &LineSeries::onClicked);
        connect(this, &QXYSeries::hovered, this, &LineSeries::showHoveredPoint);
    }
private slots:
    void onClicked(const QPointF &point){
        QPen p = pen();
        p.setWidth(p.width()+1);
        setPen(p);
        double y = point.y();
        const QString yValueString = QString::number(y);
        this->setName(yValueString);
        QPoint globalCursorPos = QCursor::pos();
        QToolTip::showText(globalCursorPos,yValueString);
    }
    void showHoveredPoint(const QPointF &point){
        double measuredValue = point.y();
        qint64 dateValue = point.x();
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(dateValue);

        QString yValueString = QString::number(measuredValue,'f',2);
        QString xValueString = dateTime.toString(dateFormatChart);
        this->setName(yValueString);
        QPoint globalCursorPos = QCursor::pos();
        QToolTip::showText(globalCursorPos,xValueString + ": " + yValueString);
    }
};



GraphHandler::GraphHandler()//QJsonArray sensorData) // hier vielleicht das array mit den Daten übergeben?  // DELETE -> nur kommentare!?
{
    //sensorDataArray = sensorData; // DELETE -> ist ja irgendwie nicht so richtig schön so
}



Chart* GraphHandler::createTempChart(QJsonArray sensorData)
{
    LineSeries *temperaturSeries = new LineSeries();


    for(QJsonValue val : sensorData)
    {
        QJsonObject obj = val.toObject();

        QString timeString = obj.value(QString("sensortime")).toString();
        QDateTime timeStampDate = QDateTime::fromString(timeString,dateFormat);


        double time = timeStampDate.toMSecsSinceEpoch();
        double tempr = obj.value(QString("temperature"))
                .toObject().value(QString("$numberDouble")).toString().toDouble();

        temperaturSeries->append(time, tempr);
    }

    Chart *chart = new Chart();
    chart->addSeries(temperaturSeries);
    chart->legend()->hide();
    chart->setTitle("Temperature Graph");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QDateTimeAxis *dateAxisX = new QDateTimeAxis;
    dateAxisX->setTickCount(10);
    dateAxisX->setFormat(dateFormatChart);
    dateAxisX->setTitleText("Date ["+dateFormatChart+"]");
    chart->addAxis(dateAxisX, Qt::AlignBottom);
    temperaturSeries->attachAxis(dateAxisX);

    // set the y axis
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Temperature [°C]");
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->axisY()->setRange(0, 30);
    temperaturSeries->attachAxis(axisY);

    return chart;
}



Chart* GraphHandler::createHumChart(QJsonArray sensorData)
{
    LineSeries *humiditySeries = new LineSeries();

    for(QJsonValue val : sensorData)
    {
        QJsonObject obj = val.toObject();

        QString timeString = obj.value(QString("sensortime")).toString();
        QDateTime timeStampDate = QDateTime::fromString(timeString,dateFormat);

        double time = timeStampDate.toMSecsSinceEpoch();
        double humi = obj.value(QString("humidity"))
                .toObject().value(QString("$numberDouble")).toString().toDouble();

        humiditySeries->append(time, humi);
    }

    Chart *chart = new Chart();
    chart->addSeries(humiditySeries);
    chart->legend()->hide();
    chart->setTitle("Humidity Graph");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // set the x axis and give them date & time labels
    QDateTimeAxis *dateAxisX = new QDateTimeAxis;
    dateAxisX->setTickCount(10);
    dateAxisX->setFormat(dateFormatChart);
    dateAxisX->setTitleText("Date ["+dateFormatChart+"]");
    chart->addAxis(dateAxisX, Qt::AlignBottom);
    humiditySeries->attachAxis(dateAxisX);

    // set the y axis
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Humidity [%]");
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->axisY()->setRange(0, 100);
    humiditySeries->attachAxis(axisY);

    return chart;
}

//DELETE -> machen die Darstellung nur mit Qlcdnumber
//QChart* GraphHandler::createHumPieChart(double humValue){
//    //    JsonDataDownloader *dwn = new JsonDataDownloader();
//    //    QJsonObject lastMPoint = dwn->getDataArray().first().toObject();
//        QPieSeries *humidityseries = new QPieSeries();
//        humidityseries->setHoleSize(0.35);


//        QString valueName = QString("Humidity");
//        double humiVal = 69.69; // DELETE
//        QString humiLabel = valueName + " " + QString::number(humValue) + " %"; //DELETE

//        double rest = 100-humValue;  //humiVal;
//        QPieSlice *humSli = humidityseries->append(humiLabel, humValue);
//        //humSli->setExploded();
//        //humSli->setLabelVisible();  //DELETE
//        humidityseries->append("",rest);
//        QChart *chart = new QChart();
//        chart->legend()->hide();
//        chart->addSeries(humidityseries);
//        chart->setTitle(valueName + ": " + QString::number(humValue) + " %");

//        return chart;
//}

// NICHT LÖSCHEN !!!
// ACHTUNG DAS IST DIE FUNKTIONIERENDE METHODE
//QChart* GraphHandler::createTempChart(QJsonArray sensorData)
//{
//    QLineSeries *temperaturSeries = new QLineSeries();
//    int i = 0;  // DELETE



//    for(QJsonValue val : sensorData)
//    {
//        //QJsonValue val = sensorData[i]; // DELETE -> nur um zu schauen ob es mit 100 Messpunkten geht

//        QJsonObject obj = val.toObject();

//        QString timeString = obj.value(QString("sensortime")).toString();
//        QDateTime timeStampDate = QDateTime::fromString(timeString,dateFormat);


//        double time = timeStampDate.toMSecsSinceEpoch();
//        double tempr = obj.value(QString("temperature"))
//                .toObject().value(QString("$numberDouble")).toString().toDouble();

//        temperaturSeries->append(time, tempr);
//        i++; // DELETE
//    }

//    QChart *chart = new QChart();
//    chart->addSeries(temperaturSeries);
//    chart->legend()->hide();
//    chart->setTitle("Temperature Graph");

//    QDateTimeAxis *dateAxisX = new QDateTimeAxis;
//    dateAxisX->setTickCount(10);
//    dateAxisX->setFormat(dateFormatChart);
//    dateAxisX->setTitleText("Date");
//    chart->addAxis(dateAxisX, Qt::AlignBottom);
//    temperaturSeries->attachAxis(dateAxisX);

//    // set the y axis
//    QValueAxis *axisY = new QValueAxis;
//    axisY->setLabelFormat("%i");
//    axisY->setTitleText("Humidity");
//    chart->addAxis(axisY, Qt::AlignLeft);
//    temperaturSeries->attachAxis(axisY);

//    return chart;
//}

// DELETE --> old method for both charts, maybe reuse if time
//QChart* GraphHandler::createLineGraph(QJsonArray sensorData)
//{
//    QLineSeries *temperaturSeries = new QLineSeries();
//    QLineSeries *humiditySeries = new QLineSeries();
//    //QJsonArray dataArray = jdownl->getDataArray();    //DELETE


//    //for(QJsonValue val : sensorDataArray)//dataArray) //DELETE -> nur den Kommentar
//    for(int i = 0; i < 100; i++)
//    {
//        QJsonValue val = sensorData[i]; // DELETE -> nur um zu schauen ob es mit 100 Messpunkten geht

//        QJsonObject obj = val.toObject();

//        double time = i;
//        double tempr = obj.value(QString("temperature"))
//                .toObject().value(QString("$numberDouble")).toString().toDouble();
//        double humi = obj.value(QString("humidity"))
//                .toObject().value(QString("$numberDouble")).toString().toDouble();
//        //nur test------------------------------------------------------------------
////        QString TESTtempr = obj.value(QString("temperature"))
////                .toObject().value(QString("$numberDouble")).toString();
////        QString TESThumi = obj.value(QString("humidity"))
////                .toObject().value(QString("$numberDouble")).toString();
////        double TESTdoubleTemp = TESTtempr.toDouble();
////        double TESTdoubleHumi = obj.value(QString("humidity"))
////                .toObject().value(QString("$numberDouble")).toString().toDouble();
//        //--------------------------------------------------------------------------
////        double time = obj.value(QString("TimeStamp")).toDouble();
////        double tempr = obj.value(QString("Temperature")).toDouble();
////        double humi = obj.value(QString("Humidity")).toDouble();

//        temperaturSeries->append(time, tempr);
//        humiditySeries->append(time, humi);
//    }

//    QChart *chart = new QChart();

//    chart->addSeries(temperaturSeries);
//    chart->addSeries(humiditySeries);
//    chart->createDefaultAxes();
//    chart->setTitle("WOW what a nice linegraph!");

//    QDateTimeAxis *dateAxisX = new QDateTimeAxis;
//    dateAxisX->setTickCount(10);
//    dateAxisX->setFormat("dd MMM");
//    dateAxisX->setTitleText("Date");
//    chart->addAxis(dateAxisX, Qt::AlignBottom);
//    temperaturSeries->attachAxis(dateAxisX);

//    //chart->setAxisX(series);

//    //    ui->dataGraph->setChart(chart);// = new QChartView(chart); //DELETE -> alle vier zeilen können weg
//    ////    QChartView *chartView = new QChartView(chart);
//    ////    chartView->setRenderHint(QPainter::Antialiasing);
//    //    ui->dataGraph->setRenderHint(QPainter::Antialiasing);}
//    return chart;
//}

#include "graphhandler.h"
// Manages the applications main settings like
// widget initialization
#include <QApplication>
// The main window to which you add toolbars,
// menubars, widgets and status bar
#include <QtWidgets/QMainWindow>
// =============== Chart includes: ===============
#include <QtCharts/QLegend>
// Used to change names on axis
#include <QtCharts/QCategoryAxis>
// Used to make the y-axis show dates
#include <QDateTimeAxis>
QT_CHARTS_USE_NAMESPACE
// =============== JSON includes: ===============
#include <QJsonObject>
// for passing the lineedits; can probably be DELETEd
#include<QWidget>
//for showing the graphdata in a tooltip
#include<QToolTip>

// string date formats to parse string to date and other way round
QString dateFormat = "yyyy-MM-dd HH:mm:ss";                             // this is for the label on the x-axis
QString dateFormatWithUTC = "ddd, dd MMM yyyy HH':'mm':'ss 'UTC'";      // this is for the parsing into millis
QString dateFormatChart = "yyyy-MM-dd HH:mm";   // use this one if you want to have some funny bugs because
                                                // it uses the DateTime of the sensor which has problems
                                                // when turning on and off


/*
 * custom class to allow showing a tooltip for the chart where to mouse cursor touches the graph line
 * the constructor gets a String for the unit that is needed to show it on the tooltip for the y-value
 */
class LineSeries: public QLineSeries{
public:
    LineSeries(QString unit, QObject *parent = nullptr):
        QLineSeries(parent)
    {
        // create a custom event for my charts
        connect(this, &QXYSeries::hovered, this, &LineSeries::showHoveredPoint);

        yUnit = unit;
    }
private:
    QString yUnit = "";
private slots:
    /*
     * get the data from the currently hovered data point and show the information
     */
    void showHoveredPoint(const QPointF &point){
        double measuredValue = point.y();
        qint64 dateValue = point.x();
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(dateValue);
        QString yValueString = QString::number(measuredValue,'f',2);
        QString xValueString = dateTime.toString(dateFormatChart);
        this->setName(yValueString);
        QPoint globalCursorPos = QCursor::pos();
        QToolTip::showText(globalCursorPos,xValueString + ": " + yValueString + " " + yUnit);
    }
};

GraphHandler::GraphHandler(){}

// standard value for both graphs
int titleSize = 22;

/*
 * returns a Chart object which is created from the passed QJsonArray and the humidity data
 */
Chart* GraphHandler::createTempChart(QJsonArray sensorData)
{
    LineSeries *temperaturSeries = new LineSeries("°C");
    // goes through all sensor data and appends the temperatur data to the chart
    for(QJsonValue val : sensorData)
    {
        // the QJsonValue needs to be put in a QJsonObject to read the key value pairs
        QJsonObject obj = val.toObject();

        QString timeString = obj.value(QString("cloudtime")).toString();
        QDateTime timeStampDate = QDateTime::fromString(timeString,dateFormatWithUTC);

        // parse the date to milli seconds for the chart
        double time = timeStampDate.toMSecsSinceEpoch();
        double tempr = obj.value(QString("temperature"))
                .toObject().value(QString("$numberDouble")).toString().toDouble();

        temperaturSeries->append(time, tempr);
    }

    // set the chart properties
    Chart *chart = new Chart();
    chart->addSeries(temperaturSeries);
    chart->legend()->hide();
    chart->setTitle("Temperature Graph");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // set title font
    QFont font;
    font.setPixelSize(titleSize);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));

    // set the x axis and give them date & time labels
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

/*
 * returns a Chart object which is created from the passed QJsonArray and the humidity data
 */
Chart* GraphHandler::createHumChart(QJsonArray sensorData)
{
    LineSeries *humiditySeries = new LineSeries("%");

    for(QJsonValue val : sensorData)
    {
        QJsonObject obj = val.toObject();

        QString timeString = obj.value(QString("cloudtime")).toString();
        QDateTime timeStampDate = QDateTime::fromString(timeString,dateFormatWithUTC);

        double time = timeStampDate.toMSecsSinceEpoch();
        double humi = obj.value(QString("humidity"))
                .toObject().value(QString("$numberDouble")).toString().toDouble();

        humiditySeries->append(time, humi);
    }

    // set the chart properties
    Chart *chart = new Chart();
    chart->addSeries(humiditySeries);
    chart->legend()->hide();
    chart->setTitle("Humidity Graph");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // set title font
    QFont font;
    font.setPixelSize(titleSize);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));

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

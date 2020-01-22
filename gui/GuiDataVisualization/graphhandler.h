#ifndef GRAPHHANDLER_H
#define GRAPHHANDLER_H

#include <QJsonArray>
// Widget used to display charts
#include <QtCharts/QChartView>
// Used to create a line chart
#include <QtCharts/QLineSeries>
QT_CHARTS_USE_NAMESPACE // needed to use the charts
#include <QDateTime>
#include "chart.h"

class GraphHandler
{
public:
    GraphHandler();
    Chart* createTempChart(QJsonArray sensorData);  // creates the temperatur chart
    Chart* createHumChart(QJsonArray sensorData);   // createa the humidity chart
};

#endif // GRAPHHANDLER_H

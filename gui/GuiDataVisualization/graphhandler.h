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
    GraphHandler(); // FRAGE: hier einen Pointer nehmen für die Sensordaten?
    QChart* createLineGraph(QJsonArray sensorData); //DELETE brauch ich vermutlich nicht mehr
    QChart* createHumPieChart(double humValue);
    Chart* createTempChart(QJsonArray sensorData);
    Chart* createHumChart(QJsonArray sensorData);

private:
    QJsonArray sensorDataArray; // erstmal testen ob das mit einem pointer hier geht
    //QLineSeries
};

#endif // GRAPHHANDLER_H

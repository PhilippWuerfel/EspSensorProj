#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include "jsondatadownloader.h"
#include <QJsonDocument>    //TEST
#include <QtCharts/QChartView> //TEST
QT_CHARTS_USE_NAMESPACE //TEST

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = 0);
    ~GraphWindow();

private slots:
    void on_btnApplyTemp_clicked();
    void on_btnRefreshTemp_clicked();

    void on_btnResetTempAxis_clicked();

    void on_btnApplyHum_clicked();

    void on_btnResetHumAxis_clicked();

    void on_btnRefreshHum_clicked();

private:
    Ui::GraphWindow *ui;
    void createGraph(); // DELETE -> sollte über andere Klassen geregelt sein
    QJsonDocument downloadJsonDataOnline();//TEST
    QChart* createLineGraphs(QJsonArray sensorData);
    void refresh();
};

#endif // GRAPHWINDOW_H

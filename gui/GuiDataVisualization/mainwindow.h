#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphwindow.h"
#include <QJsonObject>
#include <QJsonDocument> //DELETE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createGraph();

private slots:
    void on_btnShowChartWindow_clicked();

    void on_refreshButton_clicked();

private:
    Ui::MainWindow *ui;
    GraphWindow *graphWindow;
    QString readJson();
    void createHumidityPie();
    QJsonObject getNewestDataPoint();
    QJsonDocument downloadJsonDataOnline(); //DELETE -> oder siehe .cpp
    void refresh();

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphwindow.h"
#include <QJsonObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnShowChartWindow_clicked();   // opens the window with the chart diagrams
    void on_refreshButton_clicked();        // reloads the data

private:
    Ui::MainWindow *ui;
    GraphWindow *graphWindow;               // necessary for the second window
    QJsonObject getNewestDataPoint();       // return a QJsonObject the newest measurement point
    void refresh();                         // downloads the newest data and displays it

};

#endif // MAINWINDOW_H

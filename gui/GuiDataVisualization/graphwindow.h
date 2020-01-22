#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>

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
    void on_btnApplyTemp_clicked();     // temperature chart: applies axis changes
    void on_btnResetTempAxis_clicked(); // temperature chart: sets the axis to default
    void on_btnRefreshTemp_clicked();   // temperature chart: calls refresh()
    void on_btnApplyHum_clicked();      // humidity chart: applies axis changes
    void on_btnResetHumAxis_clicked();  // humidity chart: sets the axis to default
    void on_btnRefreshHum_clicked();    // humidity chart: calls refresh()

private:
    Ui::GraphWindow *ui;
    void refresh();                     //reloads the data and redraws the charts
};

#endif // GRAPHWINDOW_H

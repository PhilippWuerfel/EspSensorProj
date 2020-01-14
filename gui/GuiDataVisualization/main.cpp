#include "mainwindow.h"

//// Manages the applications main settings like
//// widget initialization
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

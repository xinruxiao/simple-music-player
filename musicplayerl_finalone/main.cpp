#include "mainwindow.h"
#include "mylove.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    myLove my1;
    w.show();

    return a.exec();
}

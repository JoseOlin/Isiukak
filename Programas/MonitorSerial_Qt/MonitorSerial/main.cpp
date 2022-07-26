#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qInstallMessageHandler(customMessageHandler); // To send qDebug, qInfo and qWarning Messages to Log.

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

#-------------------------------------------------
#
# Project created by QtCreator 2015-08-21T14:31:43
#
#-------------------------------------------------

QT  += core gui
QT  += serialport
# sudo apt install libqt5serialport5-dev

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MonitorIsiukak
TEMPLATE = app

HEADERS  += logging.hpp \
        RegExp_Search.hpp \
        mainwindow.h

SOURCES += main.cpp\
        mainwindow.cpp

FORMS    += mainwindow.ui

RESOURCES += \
    #build-LecturaValores/resources.qrc \
    Resources.qrc


BITSIZE = $$system(getconf LONG_BIT)
if (contains(BITSIZE, 64)) {
  message($$BITSIZE)
}
if (contains(BITSIZE, 32)) {
  message($$BITSIZE)
}

linux-g++ {
  message(On Linux)
}
macx-g++ {
  message(On Mac)
}



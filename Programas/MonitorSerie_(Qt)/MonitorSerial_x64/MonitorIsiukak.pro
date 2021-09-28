#-------------------------------------------------
#
# Project created by QtCreator 2015-08-21T14:31:43
#
#-------------------------------------------------

QT       += core gui
# sudo apt install libqt5serialport5-dev

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MonitorIsiukak
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

QT += serialport

RESOURCES += \
    #build-LecturaValores/resources.qrc \
    Resources.qrc


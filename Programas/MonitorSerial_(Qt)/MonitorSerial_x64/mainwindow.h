#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

//#include <QMainWindow>
#include <QtWidgets/QMainWindow>


#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QGraphicsView>
#include <QDebug>

#include <chrono>
#include <thread>

#define CERRAR_PUERTO_SERIAL 0

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    signed char dx=0, dy=0;

private slots:
    void readData();
    void escribir(const char *datos);
    void escribirCadena(const QByteArray &datos);

    void on_btnDesconectar_pressed();
    void on_btnConectar_pressed();
    void on_cmbSerialPortSelector_currentTextChanged(const QString &arg1);
    void on_cmbSerialPortSelector_currentIndexChanged(int index);

    //void on_btnParoEmergencia_pressed();
    void on_cmbSerialPortSelector_highlighted(int index);
    void on_btnDesconectar_clicked();

private:
    //QStringList buscarPuertos();
    void fillPortsParameters();
    void fillPortsInfo();
    //void llenarInfoPuertosManual();
    void showPortInfo(int idx);
    void desplegarValores(QString renglonDatos_s);

    int buscarExpresionRegular_returnNextInt(QString expReg, QString fuente);
    bool buscarExpresionRegular(QString expReg, QString fuente);
    void checkBoxBouncing(QCheckBox *chkBox, int statusRcv);
    void checkBoxColor(QCheckBox * chkBox);
    void checkBoxBouncing_Errors(QCheckBox *chkBox, bool statusRcv);
    void apagarLEDsError();
    void decodeDriverError();
    void dibujarVolante(float anguloGrados);

    //Variables globales
    Ui::MainWindow *ui;
    QGraphicsScene *escena;
    QSerialPort* serial;

    QString renglonDatos_s;

};

#endif // MAINWINDOW_H

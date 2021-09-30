#ifndef MAINWINDOW_H
#define MAINWINDOW_H



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


    //void on_btnSendBaudRate_released();

    //void on_horizontalSlider_sliderReleased();
    //void on_verticalSlider_sliderReleased();

    void ControlRobotDiferencial(signed char dx, signed char dy);
    void EnviarComando();


    //void on_dial_sliderReleased();


    void on_btnParoEmergencia_pressed();

    void on_cmbSerialPortSelector_highlighted(int index);

    void on_btnDesconectar_clicked();

private:
    //QStringList buscarPuertos();
    void fillPortsParameters();
    void fillPortsInfo();
    //void llenarInfoPuertosManual();
    void showPortInfo(int idx);
    void desplegarValores(QString renglonDatos_s);

    void dibujarVolante(float anguloGrados);
    int buscarExpresionRegular(QString expReg, QString fuente);
    Ui::MainWindow *ui;

    //Variables globales
    QGraphicsScene *escena;
    QSerialPort* serial;

    QString renglonDatos_s;
};

#endif // MAINWINDOW_H

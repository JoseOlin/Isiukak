#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

//#include <QMainWindow>
#include <QtWidgets/QMainWindow>

#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QGraphicsView>
#include <QDebug>
#include <QMessageBox>

#include <string.h>
#include <vector>
#include <algorithm> // To use rotate

#include "logging.hpp"

#include <iostream>     // std::cout
using namespace std;

#define qDbg qDebug()

#include <chrono>
#include <thread>
#include <QFile>
//#include <QIODevice>
//#include <QTextStream>

#define CERRAR_PUERTO_SERIAL 0

struct driverValuesRow{
    float Vin;
    float Temperature;
    uint16_t errorsRaw;
    uint8_t errorsArray[10];
    QStringList errorsList;
};

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
    void on_cmbSerialPortSelector_currentIndexChanged(int index);
    //void on_cmbSerialPortSelector_currentTextChanged(const QString &arg1);
    //void on_cmbSerialPortSelector_highlighted(int index);

    void on_btnParoEmergencia_clicked();
    //void on_btnConectar_clicked();
    //void on_btnDesconectar_clicked();


    void on_actionGuardar_rangos_triggered();

private:
    void desplegarValores(QString renglonDatos_s);

    void displayInfoJoystick(QString renglonDatos);
    void displayInfoButtons(QString renglonDatos);

    void displayInfoBrake(QString renglonDatos);
    void displayInfoAccel(QString renglonDatos);
    void displayInfoSteer(QString renglonDatos);
    void displaySystemInfo(QString renglonDatos);
    void displayInfoShiftGear(QString renglonDatos);

    void displayPotsErrors(QString renglonDatos);


    bool Limits_update(int currentValue, int& min, int& max,
                                   QLabel *min_lbl, QLabel *max_lbl);

    bool saveRanges();

    void apagarLEDsError();
    void decodeDriverError(const uint16_t errorRaw, driverValuesRow& row);
    void driverMatrixValues_insert(vector<driverValuesRow>& driverMatrix,
                                              driverValuesRow row);
    QString driverMatrixValues_display(vector<driverValuesRow> driverMatrix);
    QString driverMatrixErrors_display(vector<driverValuesRow> driverMatrix);

    void driverMatrixValues_gridLayoutDisplay(QGridLayout* grid,
                                                vector<driverValuesRow> driverMatrix);
    void driverMatrixErrors_gridLayoutDisplay(QGridLayout* grid,
                                              vector<driverValuesRow> driverMatrix);

    bool buscarExpresionRegular_returnNextInt(QString expReg, QString fuente, int& match_int);
    bool buscarExpresionRegular(QString expReg, QString fuente);
    bool buscarExpresionRegular_PotError(QString fuente, QString &matchString, int &match_int);

    void checkBoxBouncing(QCheckBox *chkBox, bool statusRcv);
    void checkBoxColor(QCheckBox * chkBox);
    void checkBoxColor_Error(QCheckBox * chkBox);
    void checkBoxBouncing_Errors(QCheckBox *chkBox, bool statusRcv);



    void dibujarVolante(float anguloGrados);

    //QStringList buscarPuertos();
    //void llenarInfoPuertosManual();
    void fillPortsParameters();
    void fillPortsInfo();
    void showPortInfo(int idx);

    //* Variables globales
    Ui::MainWindow *ui;
    //QGraphicsScene *escena;
    QSerialPort* serial;

    QString renglonDatos_s;

    vector<driverValuesRow> brake_driverValuesMatrix;
    vector<driverValuesRow> accel_driverValuesMatrix;
    vector<driverValuesRow> steer_driverValuesMatrix;
    vector<vector<QLabel*>> erroresMatrix_lbl;

    int T_sys = 0; // System period.
    int T_max = 0; // Max System period.
    int T_min = 1000;

    int valorJy, valorJx;
    int Joystick_Activado;
    int statusFixFreno, statusModoCarr, statusPalancaUp, statusPalancaDown;

    int B_pos, B_tgt, B_Pos_Error, B_Ctrl, B_Activado, B_Inhibido;
    int B_Vin, B_Temp, B_Driver_Errors;

    int A_pos, A_tgt, A_Pos_Error, A_Ctrl, A_Activado, A_Inhibido;
    int A_Vin, A_Temp, A_Driver_Errors;

    int V_Ctrl, V_Activado, V_Mode;
    int V_Vin, V_Temp, V_Driver_Errors;

    int ShiftGear_Activated;

    int SystemStatusNum = 7;

    int normalDefines;

    int Brake_pos_max = 0; // Max value of brake position readed.
    int Brake_pos_min = 10000;
    int Accel_pos_max = 0; // Max value of accelerator position readed.
    int Accel_pos_min = 10000;

    // Min and max values start at opposites
    int Joy_Y_max = 0;
    int Joy_Y_min = 4096;

    int Joy_X_max = 0;
    int Joy_X_min = 4096;
};

#endif // MAINWINDOW_H

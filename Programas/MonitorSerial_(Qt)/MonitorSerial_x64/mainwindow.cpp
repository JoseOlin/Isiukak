/* Programa para leer el puerto serie del arduino del Sistema de Conducción
 *
 *
 *
 *
 */

#include "mainwindow.h"


#include <string.h>
#include <QMessageBox>
#include <QDebug>

#define qDbg qDebug()
//QString serialPort;
int baudRate = QSerialPort::Baud115200;
//int baudRate = QSerialPort::Baud9600;
//int baudRate = QSerialPort::Baud38400;


QString cadJoystickActivado = "J_ac";
QString cadJx_Desc = "J_x_Desc";
QString cadJy_Desc = "J_y_Desc";
QString cadJx_OutOfRange = "J_x_OutOfRange";
QString cadJy_OutOfRange = "J_y_OutOfRange";

QString cadAcelActivado = "A_ac";
QString cadAcelInhibido = "A_inh";
QString cadAcel_Desc = "Acel_Desc";
QString cadAcel_OutOfRange = "Acel_OutOfRange";

QString cadBrakeActivado = "B_ac";
QString cadBrakeInhibido = "B_inh";
QString cadBrakeDesc = "Freno_Desc";
QString cadBrake_OutOfRange = "Brake_OutOfRange";
QString cadBrake_VIN = "B_Vin";
QString cadBrake_Temp = "B_Tmp";
QString cadBrake_Error = "B_Err";

QString cadVolanteActivado = "Vol_ac";
QString cadVolanteModo = "Vol_m";
QString cadVolanteControl = "Vol_c";

QString cadPalancaActivada = "Shft_a";

QString cadEstadoSistema = "edo";

QString cadCompsReconnected = "Componentes Reconectados y en Rango Válido";
QString cadParoEmergenciaManual = "Paro de Emergencia Manual.";
QString cadRestartTesting = "Testing";

// Usadas en desplegarValores(QString renglonDatos)


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ////// Inicialización y llenado de los elementos
    // Comunicación serial.
    serial = new QSerialPort(this);

    //buscarPuertos();

    fillPortsInfo();
    fillPortsParameters();


    /// Conexiones.
    connect(serial,     SIGNAL(readyRead()),
            this,       SLOT(readData())          );

    connect(ui->cmbSerialPortSelector,  SIGNAL(currentIndexChanged(int)),
           this,                       SLOT(showPortInfo(int))   );


    int joyY_Center = 510;
    int joyY_MinVal = joyY_Center - 130;
    int joyY_MaxVal = joyY_Center + 130;
    //int joyY_FrenoCambios = 600;

    // ** Eje X (Volante)
    int joyX_Center = 512;  //
    int joyX_MinVal = joyX_Center - 130;  //
    int joyX_MaxVal = joyX_Center + 130;  //

    ui->joystickVertical_sld->setMinimum(joyY_MinVal);
    ui->joystickVertical_sld->setMaximum(joyY_MaxVal);
    ui->joystickHorizontal_Sld->setMinimum(joyX_MinVal);
    ui->joystickHorizontal_Sld->setMaximum(joyX_MaxVal);


    ui->btnConectar->click(); //Conectar automáticamente al arranque.
    ///////////////////////////////////////////////////

    escena = new QGraphicsScene(0,0, 250,250);
    //ui->joystick_graphics->setScene(escena);
}

MainWindow::~MainWindow()
{
    ui->btnDesconectar->click();
    delete ui;
}


int MainWindow::buscarExpresionRegular_returnNextInt(QString expReg, QString fuente)
{

    //QRegularExpression expRegInt_R("J_Y: (\\d+)");
    QRegularExpression expRegInt_R(expReg);
    QRegularExpressionMatch RegExMatch = expRegInt_R.match(fuente);
    //int indiceJy_Fin
    //int indiceJy_Ini = expRegInt.indexIn(renglonDatos_s);
    if(RegExMatch.hasMatch() )
    {
        QString match_s = RegExMatch.captured(1);
        int match_int = match_s.toInt();
        return match_int;
    }
    else
    {
        return -1;
    }
}

bool MainWindow::buscarExpresionRegular(QString expReg_str, QString fuente)
{
    QRegularExpression expReg(expReg_str);
    QRegularExpressionMatch RegExMatch = expReg.match(fuente);
    if(RegExMatch.hasMatch())
    {
        return true;
    }
    else
    {
        return false;
    }

}


void MainWindow::decodeDriverError()
{
    /*The motor can only be driven when this register has a value of 0. (See Section 3.4 for error descriptions.)
    • Bit 0: Safe Start Violation
    • Bit 1: Required Channel Invalid
    • Bit 2: Serial Error
    • Bit 3: Command Timeout
    • Bit 4: Limit/Kill Switch
    • Bit 5: Low VIN
    • Bit 6: High VIN
    • Bit 7: Over Temperature
    • Bit 8: Motor Driver Error
    • Bit 9: ERR Line High
    • Bits 10-15: reserved */

}

void MainWindow::desplegarValores(QString renglonDatos)
{
    /* Función para desplegar los datos que se reciben por Serial y mostrar los errores
     * en la GUI.
     * Se invoca en readData()     */

    ui->InfoSalida_txt->insertPlainText(renglonDatos);
    ui->InfoSalida_txt->ensureCursorVisible();
    ui->erroresSalida_txt->ensureCursorVisible();

    /// Separar renglón datos para mostrar valores del Joystick.

    /// Joystick Y
    int valorJy = buscarExpresionRegular_returnNextInt("J_Y: (\\d+)", renglonDatos);
    ui->joystick_Y_lcd->display(valorJy);
    ui->joystickVertical_sld->setValue(valorJy);

    /// Joystick X
    int valorJx = buscarExpresionRegular_returnNextInt("J_X: (\\d+)", renglonDatos);
    ui->joystick_X_lcd->display(valorJx);
    ui->joystickHorizontal_Sld->setValue(valorJx);


    //* Brake INFO
    int B_pos = buscarExpresionRegular_returnNextInt("B_p: (\\d+)", renglonDatos);
    ui->frenoPos_lcd->display(B_pos);

    int B_tgt = buscarExpresionRegular_returnNextInt("B_t: (\\d+)", renglonDatos);
    ui->frenoDes_lcd->display(B_tgt);

    int B_Ctrl = buscarExpresionRegular_returnNextInt("B_c: (-?(\\d+))", renglonDatos);
    // -?(\\d+) = Uno o ningún signo menos, seguido de uno o más dígitos.
    ui->frenoControl_lcd->display(B_Ctrl);
    ui->FrenoControl_Slider->setValue(B_Ctrl);

    int B_Error = buscarExpresionRegular_returnNextInt("B_e: (-?(\\d+))", renglonDatos);
    ui->Freno_lcdError->display(B_Error);


    int B_Vin = buscarExpresionRegular_returnNextInt(cadBrake_VIN + ": (-?(\\d+))", renglonDatos);
    if(B_Vin > 1000) // 1000 mV = 1V
    {
        float B_Vin_f = (float)B_Vin / 1000.0; // Received en mV.
        ui->Brake_VIN_lbl->setText(QString::number(B_Vin_f));
    }

    int B_Temp = buscarExpresionRegular_returnNextInt(cadBrake_Temp  + ": (-?(\\d+))", renglonDatos);
    if(B_Temp > 100) //100 = 10 °C
    {
        float B_Temp_f = (float)B_Temp / 10.0; // Received in 0.1 °C
        ui->Brake_Temp_lbl->setText(QString::number(B_Temp_f));
    }

    int B_Error_Driver = buscarExpresionRegular_returnNextInt(cadBrake_Error + ": (-?(\\d+))", renglonDatos);
    if(B_Error_Driver > -1)
    {
        ui->Brake_Error_lbl->setText(QString::number(B_Error_Driver));
        //decodeDriverError();
    }


    // Acelerador INFO
    int A_pos = buscarExpresionRegular_returnNextInt("A_p: (\\d+)", renglonDatos);
    ui->aceleradorPos_lcd->display(A_pos);

    int A_tgt = buscarExpresionRegular_returnNextInt("A_t: (\\d+)", renglonDatos);
    ui->aceleradorDes_lcd->display(A_tgt);

    int A_Ctrl = buscarExpresionRegular_returnNextInt("A_c: (-?(\\d+))", renglonDatos);
    ui->aceleradorControl_lcd->display(A_Ctrl);
    ui->AceleradorControl_Slider->setValue(A_Ctrl);

    int A_Error = buscarExpresionRegular_returnNextInt("A_e: (-?(\\d+))", renglonDatos);
    ui->Acelerador_lcdError->display(A_Error);


    /// Volante
    int Vol_Ctrl = buscarExpresionRegular_returnNextInt(cadVolanteControl + ": (-?(\\d+))", renglonDatos);
    //qDebug() << "V_Ctrl: " << V_Ctrl;
    ui->volante_lcd->display(Vol_Ctrl);
    ui->VolanteControl_Dial->setValue(Vol_Ctrl);

    int Vol_mode = buscarExpresionRegular_returnNextInt(cadVolanteModo + ": (-?(\\d+))", renglonDatos);


    ui->VolanteModo_cmb->setCurrentIndex(Vol_mode);
    if(Vol_mode == 0)    { // Modo Inhibido.
        checkBoxBouncing(ui->palanca_Activada_chk, true);
    } else {
        checkBoxBouncing(ui->palanca_Activada_chk, false);
    }

    int statusVolActivado = buscarExpresionRegular_returnNextInt(cadVolanteActivado + ": (-?(\\d+))", renglonDatos);
    checkBoxBouncing(ui->volante_Activado_chk, statusVolActivado);
    checkBoxColor(ui->volante_Activado_chk);

    /// Estado del Sistema
    int edoSistemaNum = buscarExpresionRegular_returnNextInt("edo: (\\d+)", renglonDatos);
    //qDebug() << "Edo Sistema: " << edoSistema;
    if(edoSistemaNum < 0)
        edoSistemaNum = 7;

    QStringList estadosSistema = {"OK", "Mnt Req", "Return Home", "Safe Parking", "Immediate Stop", "Emergency Stop", "Emergency Braking", "NA"};
    QString edoSist = estadosSistema[edoSistemaNum];

    QString edoSistema_str = QString::number(edoSistemaNum) + ": " + edoSist;
    ui->estadoSistema_lbl->setText(edoSistema_str);

    // BOTONES
    /// Fix Brake Position.
    int statusFixFreno = buscarExpresionRegular_returnNextInt("bFB: (-?(\\d+))", renglonDatos);
    checkBoxBouncing(ui->FixFreno_chk, statusFixFreno);

    /// Modo Carretera
    int statusModoCarr    = buscarExpresionRegular_returnNextInt("bMC: (-?(\\d+))", renglonDatos);
    checkBoxBouncing(ui->RoadMode_chk, statusModoCarr);

    int statusPalancaUp   = buscarExpresionRegular_returnNextInt("bPU: (-?(\\d+))", renglonDatos);
    checkBoxBouncing(ui->PalUp_chk, statusPalancaUp);

    int statusPalancaDown = buscarExpresionRegular_returnNextInt("bPD: (-?(\\d+))", renglonDatos);
    checkBoxBouncing(ui->PalDown_chk, statusPalancaDown);

    /// Errores
    //QRegularExpression expRegInt_R = QRegularExpression ("(\\*\\*)(.+)\n");
    QRegularExpression expRegInt_R = QRegularExpression ("(\\*\\*)(.+)(\\*\\*)");
    // \\*\\* = **
    // (.+) = Cualquier caracter una o más veces
    // (Freno|Joy_V|Joy_H|Acelerador) = Freno   OR   Joy_V   OR   Joy_H   OR   Acelerador
    QRegularExpressionMatch match = expRegInt_R.match(renglonDatos);
    QString Error_s = match.captured(0);
    if(Error_s.length() > 0)
    {
        ui->erroresSalida_txt->insertPlainText(Error_s);
        ui->erroresSalida_txt->insertPlainText("\n");
    }


    // Estas señales actúan como un switch.
    // Cuando se activan no se desactivarán hasta el próximo inicio del sistema

    //* Joystick
    //** Desconectado
    //bool LED_Joystick_Y_Desconectado = buscarExpresionRegular("(\\*\\*)(Joystick_Y_Desconectado)(\\*\\*)", renglonDatos);
    QString cadJyDescFull = "(\\*\\*)(" + cadJy_Desc + ")(\\*\\*)";
    bool LED_Joystick_Y_Desconectado = buscarExpresionRegular(cadJyDescFull, renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Joy_Y_Desc, LED_Joystick_Y_Desconectado);

    bool LED_Joystick_X_Desconectado = buscarExpresionRegular("(\\*\\*)(" + cadJx_Desc + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Joy_X_Desc, LED_Joystick_X_Desconectado);

    //** OutOfRange
    bool LED_Joystick_Y_OutOfRange = buscarExpresionRegular("(\\*\\*)(" + cadJy_OutOfRange + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Joy_Y_OutR, LED_Joystick_Y_OutOfRange);

    bool LED_Joystick_X_OutOfRange = buscarExpresionRegular("(\\*\\*)(" + cadJx_OutOfRange + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Joy_X_OutR, LED_Joystick_X_OutOfRange);

    //** Activado
    int statusJoystickActivado = buscarExpresionRegular_returnNextInt(cadJoystickActivado+ ": (-?(\\d+))", renglonDatos);
    checkBoxBouncing(ui->joystick_Activado_chk, statusJoystickActivado);
    checkBoxColor(ui->joystick_Activado_chk);


    //* ACTUADORES
    //** Desconectados
    bool LED_Acelerador_Desconectado = buscarExpresionRegular("(\\*\\*)(" + cadAcel_Desc + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Acel_Desc, LED_Acelerador_Desconectado);

    bool LED_Freno_Desconectado = buscarExpresionRegular("(\\*\\*)(" + cadBrakeDesc + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Freno_Desc, LED_Freno_Desconectado);

    //** Inhibidos
    int statusAcelInhibido = buscarExpresionRegular_returnNextInt(cadAcelInhibido + ": (-?(\\d+))", renglonDatos);
    checkBoxBouncing(ui->Acel_Inhibido_chk, statusAcelInhibido);

    int statusFrenoInhibido = buscarExpresionRegular_returnNextInt(cadBrakeInhibido + ": (-?(\\d+))", renglonDatos);
    checkBoxBouncing(ui->Freno_Inhibido_chk, statusFrenoInhibido);

    //** Activados
    int statusFrenoActivado = buscarExpresionRegular_returnNextInt(cadBrakeActivado + ": (-?(\\d+))", renglonDatos);
    checkBoxBouncing(ui->Freno_Activado_chk, statusFrenoActivado);
    checkBoxColor(ui->Freno_Activado_chk);

    int statusAcelActivado = buscarExpresionRegular_returnNextInt(cadAcelActivado + ": (-?(\\d+))", renglonDatos);
    //qDbg << "statusAcelActivado" << statusAcelActivado;
    checkBoxBouncing(ui->Acel_Activado_chk, statusAcelActivado);
    checkBoxColor(ui->Acel_Activado_chk);

    int statusShiftGearActivated = buscarExpresionRegular_returnNextInt(cadPalancaActivada + ": (-?(\\d+))", renglonDatos);
    checkBoxBouncing(ui->palanca_Activada_chk, statusShiftGearActivated);
    checkBoxColor(ui->palanca_Activada_chk);


    //** OutOfRange
    bool LED_Freno_OutOfRange = buscarExpresionRegular("(\\*\\*)(" + cadBrake_OutOfRange + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Freno_OutR, LED_Freno_OutOfRange);

    //bool LED_Acel_OutOfRange = buscarExpresionRegular("(\\*\\*)(Acelerador_OutOfRange)(\\*\\*)", renglonDatos);
    bool LED_Acel_OutOfRange = buscarExpresionRegular("(\\*\\*)(" + cadAcel_OutOfRange + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Acel_OutR, LED_Acel_OutOfRange);


    bool testingRestartingReceived = buscarExpresionRegular("(\\*\\*)(" + cadRestartTesting + ")(\\*\\*)", renglonDatos);
    if(testingRestartingReceived)
    {
        apagarLEDsError();
    }

    //int valorJx = Jx_s.toInt();

}

void MainWindow::apagarLEDsError()
{
    ui->chk_LED_Joy_Y_Desc->setChecked(false);
    ui->chk_LED_Joy_X_Desc->setChecked(false);
    ui->chk_LED_Freno_Desc->setChecked(false);
    ui->chk_LED_Acel_Desc->setChecked(false);

    ui->chk_LED_Joy_Y_OutR->setChecked(false);
    ui->chk_LED_Joy_Y_OutR->setChecked(false);
    ui->chk_LED_Acel_OutR->setChecked(false);
    ui->chk_LED_Freno_OutR->setChecked(false);
}

void MainWindow::checkBoxBouncing(QCheckBox *chkBox, int statusRcv)
{
    // Atención que -1 se considera true.

    bool chkStatus = chkBox->checkState();

    if( (statusRcv > 0) && !chkStatus)
    {
        chkBox->setChecked(true);
    }
    else if( (statusRcv <= 0) && chkStatus)
    {
        chkBox->setChecked(false);
    }
}

void MainWindow::checkBoxColor(QCheckBox * chkBox)
{
    bool status = chkBox->isChecked();
    if(status)
    {
        chkBox->setStyleSheet("background-color: rgb(0, 85, 255);\ncolor: rgb(255, 255, 0);");
    }else {
        chkBox->setStyleSheet("background-color: rgb(255, 85, 0);\ncolor: rgb(255, 255, 0);");
    }
}

void MainWindow::checkBoxBouncing_Errors(QCheckBox *chkBox, bool statusRcv)
{
    bool chkStatus = chkBox->checkState();
    if(statusRcv && !chkStatus)
    {
        chkBox->setChecked(true);
    }
    /*else if(!statusRcv && chkStatus)
        chkBox->setChecked(false);
*/
}

/*
QStringList MainWindow::buscarPuertos()
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    qDebug() << QObject::tr("Total number of ports available: ") << serialPortInfos.count() << endl;

    const QString blankString = QObject::tr("N/A");
    QString description;
    QString manufacturer;
    QString serialNumber;

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        description = serialPortInfo.description();
        manufacturer = serialPortInfo.manufacturer();
        serialNumber = serialPortInfo.serialNumber();
        qDebug() << endl
            << QObject::tr("Port: ") << serialPortInfo.portName() << endl
            << QObject::tr("Location: ") << serialPortInfo.systemLocation() << endl
            << QObject::tr("Description: ") << (!description.isEmpty() ? description : blankString) << endl
            << QObject::tr("Manufacturer: ") << (!manufacturer.isEmpty() ? manufacturer : blankString) << endl
            << QObject::tr("Serial number: ") << (!serialNumber.isEmpty() ? serialNumber : blankString) << endl
            << QObject::tr("Vendor Identifier: ") << (serialPortInfo.hasVendorIdentifier() ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) : blankString) << endl
            << QObject::tr("Product Identifier: ") << (serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : blankString) << endl
            << QObject::tr("Busy: ") << (serialPortInfo.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) << endl;
    }

    return QStringList({QString("1"),QString("2")});
}
*/

void MainWindow::on_btnConectar_pressed()
{
    //serial.setPortName("/dev/ttyUSB0");
    //serial.setPortName("/dev/ttyUSB1");
    QString portName = ui->cmbSerialPortSelector->currentText();
    qDebug() << "Port name: " << portName;
    serial->setPortName(portName);
    //serial.setPortName("/dev/ttyACM1");
    serial->open(QIODevice::ReadWrite);

    baudRate = ui->cmbBaudRate->currentData().toInt();
    qDebug() << "BaudRate:" << baudRate;
    serial->setBaudRate(baudRate);

    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);


    if (serial->isOpen() && serial->isWritable())
    {
        qDebug() << "Ready..." << endl;
        //serial.write("R");

        if(serial->flush())
        {
            qDebug() << "ok" << endl;
        }
        //qDebug() <<"value sent!!! "<< endl;
        #if CERRAR_PUERTO_SERIAL
        serial->close();
        #endif

        ui->btnConectar->setEnabled(false);
        ui->btnDesconectar->setEnabled(true);
    }
    else
    {
        qDebug() << "Was an error while creating the Serial Port. btnConectar_pressed()";
        QMessageBox msg;
        msg.setText("Was an error while creating the Serial Port. btnConectar_pressed()");
        msg.exec();
    }
}

void MainWindow::on_btnDesconectar_pressed()
{
    serial->close();
    if(!serial->isOpen())
    {
        ui->btnConectar->setEnabled(true);
        ui->btnDesconectar->setEnabled(false);
    }
    else
    {
        QMessageBox msg;
        msg.setText("No se pudo cerrar el puerto");
        msg.exec();
    }
}



void MainWindow::readData()
{
    if(!ui->btnConectar->isEnabled())
    {
        QByteArray data = serial->readAll();

        if(!data.isEmpty())
        {
            int indSalto;// = data.indexOf("\n");
            //La cadena leída puede contener varios renglones. Separarlos.
            int cantSaltos = data.count("\n");
            //qDebug() << "cantSaltos: " << cantSaltos; //2 Saltos máximo, en los experimentos.
            if(cantSaltos > 0)
            {
                int cont = 0;
                while(cont < cantSaltos)
                {
                    indSalto = data.indexOf("\n");
                    //qDebug() << "indSalto: " <<indSalto;
                    QString cadenaTemp = data.left(indSalto+1);
                    //qDebug() << "cadenaTemp: " << cadenaTemp;

                    renglonDatos_s.append(cadenaTemp);
                    //qDebug() << "renglonDatos: " << renglonDatos_s;

                    desplegarValores(renglonDatos_s);

                    data.remove(0, indSalto+1); //Si llegó un salto de línea en el data, enviar y limpiar el renglón.
                    renglonDatos_s.clear();
                    cont++;
                }
                renglonDatos_s.append(data);//El resto del dato ponerlo en el renglón, para concatenarlo con la siguiente lectura.
            }
            else
            {
                renglonDatos_s.append(data);
            }
            /*if(indSalto  != -1)
                renglonDatos.append(data);
            else
            {
                qDebug() << renglonDatos;
                renglonDatos.clear();
            }*/
        }
    }
}

void MainWindow::escribir(/*QString datos*/ const char* datos)
{
    #if CERRAR_PUERTO_SERIAL
    serial->open(QIODevice::ReadWrite); //Ya debe estar abierto.
    #endif
    if(serial->isOpen()  &&  serial->isWritable())
    {
        //qDebug() << datos;
        //serial->write(datos.toStdString().c_str());
        serial->write(datos);

        if(serial->flush())
            qDebug() << "ok";
        #if CERRAR_PUERTO_SERIAL
        serial->close(); //Probar sin cerrar.
        #endif
    }
    else
        qDebug() << "Error: Puerto cerrado.";
}
void MainWindow::escribirCadena(const QByteArray &datos)
{
    #if CERRAR_PUERTO_SERIAL
    serial->open(QIODevice::ReadWrite); //Ya debe estar abierto.
    #endif
    if(serial->isOpen()  &&  serial->isWritable())
    {
        //qDebug() << datos;
        //serial->write(datos.toStdString().c_str());
        serial->write(datos);

        if(serial->flush())
            qDebug() << "ok";
        #if CERRAR_PUERTO_SERIAL
        serial->close(); //Probar sin cerrar.
        #endif
    }
    else
        qDebug() << "Error: Puerto cerrado.";
}


void MainWindow::fillPortsParameters()
{
    ui->cmbBaudRate->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->cmbBaudRate->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->cmbBaudRate->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->cmbBaudRate->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->cmbBaudRate->addItem(QStringLiteral("Custom"));
    //ui->cmbBaudRate->setCurrentIndex(2); //38400
    ui->cmbBaudRate->setCurrentIndex(3);//115200
}
void MainWindow::fillPortsInfo()
{
    // Consultar los puertos disponibles y agregarlos a cmbSerialPortSelector
    ui->cmbSerialPortSelector->clear();

    static const QString blankString = QObject::tr("N/A");
    QString description;
    QString manufacturer;
    //QString serialNumber;
    const auto puertosDisponibles = QSerialPortInfo::availablePorts();
    //foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    foreach (const QSerialPortInfo &info, puertosDisponibles)
    {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        //serialNumber = info.serialNumber();

        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             //<< (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        ui->cmbSerialPortSelector->addItem(list.first(), list);
    }

    qDebug() << "Cantidad de puertos disponibles: " << puertosDisponibles.length();
    if(puertosDisponibles.length() < 1)
    {
        qDebug() << "No se encontraron dispositivos conectados.";
    }
}

/*void MainWindow::llenarInfoPuertosManual()
{
    ui->cmbSerialPortSelector->clear();

    ui->cmbSerialPortSelector->addItem(QStringLiteral("/dev/ttyACM0"), QStringLiteral("/dev/ttyACM0"));
    ui->cmbSerialPortSelector->addItem(QStringLiteral("/dev/ttyACM1"), QStringLiteral("/dev/ttyACM1"));
    ui->cmbSerialPortSelector->addItem(QStringLiteral("/dev/ttyACM2"), QStringLiteral("/dev/ttyACM2"));


    ui->cmbSerialPortSelector->addItem(QStringLiteral("/dev/ttyUSB0"), QStringLiteral("/dev/ttyUSB0"));
    ui->cmbSerialPortSelector->addItem(QStringLiteral("/dev/ttyUSB1"), QStringLiteral("/dev/ttyUSB1"));
    ui->cmbSerialPortSelector->addItem(QStringLiteral("/dev/ttyUSB2"), QStringLiteral("/dev/ttyUSB2"));

    ui->cmbSerialPortSelector->setCurrentIndex(0);
}*/

void MainWindow::showPortInfo(int idx)
{
    // Mostrar la información del puerto en la etiqueta lblDescripción
    if(idx != -1)
    {
        QStringList list = ui->cmbSerialPortSelector->itemData(idx).toStringList();
        ui->lblDescripcion->setText(tr("Descripción: %1").arg(list.at(1)));
    }
}




void MainWindow::on_cmbSerialPortSelector_currentTextChanged(const QString &arg1)
{
    /*
    //serial.setPortName("/dev/ttyUSB1");
    serial->setPortName(arg1);
    serial->open(QIODevice::ReadWrite);
    serial->setBaudRate(baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->isOpen() && serial->isWritable())
    {
        //qDebug() << "Ready..." << endl;
        qDebug() << "Conectado." << endl;
        //QMessageBox msg;
        //msg.setText("Conectado.");
        //msg.exec();
        //serial.write("R");

        //if(serial.flush())
        //{
        //    qDebug() << "ok" << endl;
        //}
        //qDebug() <<"value sent!!! "<< endl;
        //serial.close();
    }
    else
    {
        qDebug() << "Was an error while creating the Serial Port. cmbSerialPortSelector_currentTextChanged()";
        QMessageBox msg;
        msg.setText("Was an error while creating the Serial Port. cmbSerialPortSelector_currentTextChanged()");
        msg.exec();
    }*/
}
void MainWindow::on_cmbSerialPortSelector_currentIndexChanged(int index)
{
        showPortInfo(index);
}


/*
void MainWindow::ControlRobotDiferencial(signed char dx, signed char dy)
{
    //qDebug() << "dx:" << dx <<", dy:" << dy;
    float angulo = atan2((double)dy, (double)dx);
    //qDebug() << "Angulo:" << angulo;

    float coseno = cos(angulo);
    float seno = sin(angulo);

    //qDebug() << "cos:" << coseno << ", sen:" << seno << endl;

    float leftMotor = (abs(dx))*coseno + abs(dy)*seno;
    float rightMotor = (-1*abs(dx))*coseno + abs(dy)*seno;

    //ui->lcdLeftMotor->display(leftMotor);
    //ui->lcdRightMotor->display(rightMotor);

    //Enviar datos por puerto serial.
    EnviarComando();
}

void MainWindow::EnviarComando()
{
    QString dx_s = QString("%1").arg(dx, 2, 10, QChar('0'));
    QString dy_s = QString("%1").arg(dy, 2, 10, QChar('0'));

    qDebug() << "dx:" << dx_s << ", dy:" << dy_s << endl;

    //escribir("i");

    //QByteArray dx_a = dx_s.toUtf8();
    //QByteArray dy_a = dy_s.toUtf8();

    QString cadenaCompleta = "i" + dx_s + dy_s;


    //qDebug() << "dx_a:" << dx_a <<", dy_a:"<< dy_a << endl;

    QByteArray cadenaCompleta_a = cadenaCompleta.toUtf8();

    qDebug() << "cadCom:" << cadenaCompleta_a << endl;

    escribirCadena(cadenaCompleta_a);
}


void MainWindow::on_btnParoEmergencia_pressed()
{
    escribirCadena("00000");
}
*/


void MainWindow::dibujarVolante(float anguloGrados)
{
    escena->clear();

    //ui->graphicsView->set
    float origen_x = 125;
    float origen_y = 125;
    float largoLinea = 100;
    float alto  = largoLinea*sin(anguloGrados*M_PI/180);
    float ancho = largoLinea*cos(anguloGrados*M_PI/180);
    float alto_perp = largoLinea*sin((anguloGrados+90)*M_PI/180);
    float ancho_perp = largoLinea*cos((anguloGrados+90)*M_PI/180);


    QPen penHLines(QColor("#FF0000"), 5, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
    QPen penRLines(QColor("#0000FF"), 5, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);

    QLine linea1(origen_x, origen_y, origen_x+ancho, origen_y+alto);
    QLine linea2(origen_x, origen_y, origen_x-ancho, origen_y-alto);
    QLine linea3(origen_x, origen_y, origen_x+ancho_perp, origen_y+alto_perp);
    //QRectF rectVolante(100,100,100,100);
    //QGraphicsEllipseItem

    escena->addLine(linea1, penHLines);
    escena->addLine(linea2, penRLines);
    escena->addLine(linea3, penHLines);
    escena->addEllipse(origen_x-largoLinea, origen_y-largoLinea, largoLinea*2, largoLinea*2, penHLines);
}

void MainWindow::on_cmbSerialPortSelector_highlighted(int index)
{

}

void MainWindow::on_btnDesconectar_clicked()
{

}

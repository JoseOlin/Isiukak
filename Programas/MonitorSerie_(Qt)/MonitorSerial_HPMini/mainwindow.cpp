/* Programa para leer el puerto serie del arduino del Sistema de Conducción
 *
 *
 *
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <string.h>
#include <QMessageBox>


//QString serialPort;
int baudRate = QSerialPort::Baud115200;
//int baudRate = QSerialPort::Baud9600;
//int baudRate = QSerialPort::Baud38400;

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

    //showPortInfo(ui->cmbSerialPortSelector->currentIndex());


    ui->btnConectar->click(); //Conectar automáticamente al arranque.
    ///////////////////////////////////////////////////

    escena = new QGraphicsScene(0,0, 250,250);
    //ui->joystick_graphics->setScene(escena);
}

void MainWindow::desplegarValores(QString renglonDatos)
{
    ui->InfoSalida_txt->insertPlainText(renglonDatos);
    ui->InfoSalida_txt->ensureCursorVisible();

    /// Separar renglón datos para mostrar valores del Joystick.

    // Joystick Y
    int valorJy = buscarExpresionRegular("J_Y: (\\d+)", renglonDatos);
    ui->joystick_Y_lcd->display(valorJy);

    //Joystick X
    int valorJx = buscarExpresionRegular("J_X: (\\d+)", renglonDatos);
    ui->joystick_X_lcd->display(valorJx);

    int B_pos = buscarExpresionRegular("B_p: (\\d+)", renglonDatos);
    ui->frenoPos_lcd->display(B_pos);

    int B_tgt = buscarExpresionRegular("B_t: (\\d+)", renglonDatos);
    ui->frenoDes_lcd->display(B_tgt);

    int B_Ctrl = buscarExpresionRegular("B_c: (-?(\\d+))", renglonDatos);
    // Uno o ningún signo menos, seguido de uno o más dígitos.
    ui->frenoControl_lcd->display(B_Ctrl);

    int B_Error = buscarExpresionRegular("B_e: (-?(\\d+))", renglonDatos);
    ui->Freno_lcdError->display(B_Error);


    int A_pos = buscarExpresionRegular("A_p: (\\d+)", renglonDatos);
    ui->aceleradorPos_lcd->display(A_pos);

    int A_tgt = buscarExpresionRegular("A_t: (\\d+)", renglonDatos);
    ui->aceleradorDes_lcd->display(A_tgt);

    int A_Ctrl = buscarExpresionRegular("A_c: (-?(\\d+))", renglonDatos);
    ui->aceleradorControl_lcd->display(A_Ctrl);

    int A_Error = buscarExpresionRegular("A_e: (-?(\\d+))", renglonDatos);
    ui->Acelerador_lcdError->display(A_Error);

    int V_Ctrl = buscarExpresionRegular("Ctrl_Vol: (-?(\\d+))", renglonDatos);
    //qDebug() << "V_Ctrl: " << V_Ctrl;
    ui->volante_lcd->display(V_Ctrl);

    int StatusFixFreno = buscarExpresionRegular("bFB: (-?(\\d+))", renglonDatos);
    bool statusFixFreno_chk = ui->FixFreno_chk->checkState();
    if( StatusFixFreno && !statusFixFreno_chk)
    {
        ui->FixFreno_chk->setChecked(true);
    }
    else if (!StatusFixFreno && statusFixFreno_chk)
    {
        ui->FixFreno_chk->setChecked(false);
    }

    int statusModoCarr    = buscarExpresionRegular("bMC: (-?(\\d+))", renglonDatos);
    bool statusModoCarr_chk = ui->RoadMode_chk->checkState();
    if(statusModoCarr && !statusModoCarr_chk)
        ui->RoadMode_chk->setChecked(true);
    else if ( !statusModoCarr && statusModoCarr_chk)
        ui->RoadMode_chk->setChecked(false);


    int statusPalancaUp   = buscarExpresionRegular("bPU: (-?(\\d+))", renglonDatos);
    bool statusPalancaUp_chk = ui->PalUp_chk->checkState();
    if(statusPalancaUp && !statusPalancaUp_chk)
        ui->PalUp_chk->setChecked(true);
    else if (!statusPalancaUp && statusPalancaUp_chk)
        ui->PalUp_chk->setChecked(false);

    int statusPalancaDown = buscarExpresionRegular("bPD: (-?(\\d+))", renglonDatos);
    bool statusPalancaDown_chk = ui->PalDown_chk->checkState();
    if(statusPalancaDown && !statusPalancaDown_chk)
        ui->PalDown_chk->setChecked(true);
    else if (!statusPalancaDown && statusPalancaDown_chk)
        ui->PalDown_chk->setChecked(false);

    //Errores
    //QRegularExpression expRegInt_R
    //QRegularExpression expRegInt_R = QRegularExpression ("(\\*\\*)(Freno|Joy_V|Joy_H|Acelerador|Pot_)(.+)\n");
    QRegularExpression expRegInt_R = QRegularExpression ("(\\*\\*)(.+)\n");
    // \\*\\* = **
    // (Freno|Joy_V|Joy_H|Acelerador) = Freno OR Joy_V OR Joy_H OR Acelerador
    // (.+) = Cualquier caracter una o más veces
    QRegularExpressionMatch match = expRegInt_R.match(renglonDatos);
    QString Error_s = match.captured(0);

    ui->erroresSalida_txt->insertPlainText(Error_s);
    //int valorJx = Jx_s.toInt();

}

MainWindow::~MainWindow()
{
    ui->btnDesconectar->click();
    delete ui;
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

        //QString cadena = QString::fromStdString(data.data());
        //qDebug() << "data: " << data;
        //qDebug() << cadena;

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



int MainWindow::buscarExpresionRegular(QString expReg, QString fuente)
{
    //QRegularExpression expRegInt_R("J_Y: (\\d+)");
    QRegularExpression expRegInt_R(expReg);
    QRegularExpressionMatch RegExMatch = expRegInt_R.match(fuente);
    //int indiceJy_Fin
    //int indiceJy_Ini = expRegInt.indexIn(renglonDatos_s);
    QString match_s = RegExMatch.captured(1);
    int match_int = match_s.toInt();

    return match_int;
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

/* Programa para leer el puerto serie del arduino del Sistema de Conducción
 *
 *
 *
 *
 */

#include "mainwindow.h"


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

QString cadAccel_VIN = "A_Vin";
QString cadAccel_Temp = "A_Tmp";
QString cadAccel_Error = "A_Err";

QString cadBrakeActivado = "B_ac";
QString cadBrakeInhibido = "B_inh";
QString cadBrakeDesc = "Freno_Desc";
QString cadBrake_OutOfRange = "Brake_OutOfRange";

QString PotError_header = "EPot_";
QString cadBrake_VIN = "B_Vin";
QString cadBrake_Temp = "B_Tmp";
QString cadBrake_Error = "B_Err";

QString cadVolanteActivado = "V_ac";
QString cadVolanteModo = "V_m";
QString cadVolanteControl = "Vol_c";
QString cadSteer_VIN = "V_Vin";
QString cadSteer_Temp = "V_Tmp";
QString cadSteer_Error = "V_Err";

QString cadPalancaActivada = "Shft_a";

QString cadEstadoSistema = "edo";
QString cadT = "T";
QString cadNormalDefines = "nDef";

QString cadTemp_uC = "Tm_uC";
QString cadTemp_Therm1 = "Tm_Th1";
QString cadTemp_Therm2 = "Tm_Th2";

QString cadCompsReconnected = "Componentes Reconectados y en Rango Válido";
QString cadParoEmergenciaManual = "Paro de Emergencia Manual.";
QString cadRestartTesting = "Testing";




vector<driverValuesRow> brake_driverMat; //Used for testing purposes.

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

    // Initialize gridLayout with 5 rows of empty labels, plus the headers row.
    uint rows = 5;
    uint cols = 12; //Vin, Temp and 10 possible errors.
    for (uint row = 0; row < rows; row++)
    {
        //vector<QLabel*> rowQLabels;
        //erroresMatrix_lbl.push_back(rowQLabels);
        for (uint col = 0; col < cols; col++)
        {
            QLabel* lbl = new QLabel();
            lbl->setText("0");
            //erroresMatrix_lbl[row].push_back(lbl);

            //ui->driverErrorsValues_gridLayout->addWidget(lbl, row, col, 1, 1, Qt::AlignCenter);
            ui->driverErrorsHeaders_gridLayout->addWidget(lbl, row + 1, col, 1, 1, Qt::AlignCenter);
        }
    }

    ///////////////////////////////////////////////////

    //escena = new QGraphicsScene(0,0, 250,250);
    //ui->joystick_graphics->setScene(escena);
    qDbg << "       Inicio sesión Logging" << QDate::currentDate() << ", " << QTime::currentTime();
    qWarning() << "Prueba warning";
    qInfo() << "Prueba Info";
}

MainWindow::~MainWindow()
{
    ui->btnDesconectar->click();
    delete ui;
}


void MainWindow::desplegarValores(QString renglonDatos)
{
    /* Función para desplegar los datos que se reciben por Serial y mostrar los errores
     * en la GUI.
     * Se invoca en readData()     */

    ui->InfoSalida_txt->insertPlainText(renglonDatos);

    ui->InfoSalida_txt->ensureCursorVisible();
    ui->erroresSalida_txt->ensureCursorVisible();
    ui->driversValues_txt->ensureCursorVisible();


    /// Separar renglón datos para mostrar valores del Joystick.

    ///* Joystick
    displayInfoJoystick(renglonDatos);

    ///* Buttons
    displayInfoButtons(renglonDatos);

    ///* Brake INFO
    displayInfoBrake(renglonDatos);

    ///* Accelerator INFO
    displayInfoAccel(renglonDatos);

    ///* Steer Wheel
    displayInfoSteer(renglonDatos);

    ///* Shift gear
    displayInfoShiftGear(renglonDatos);

    ///* System status
    displaySystemInfo(renglonDatos);

    ///* Temperature values
    displayTemperature(renglonDatos);

    ///* Test restarting string when running embedded Testing
    bool testingRestartingReceived = buscarExpresionRegular("(\\*\\*)(" + cadRestartTesting + ")(\\*\\*)", renglonDatos);
    if(testingRestartingReceived)
    {
        apagarLEDsError();
    }


    ///* Errors
    QRegularExpression expRegInt_R = QRegularExpression ("(\\*\\*)(.+)(\\*\\*)");
    // \\*\\* = **             (.+) = Any character one or more times
    QRegularExpressionMatch match = expRegInt_R.match(renglonDatos);
    QString Error_s = match.captured(0);
    if( Error_s.length() > 0 )
    {
        ui->erroresSalida_txt->insertPlainText(Error_s);
        ui->erroresSalida_txt->insertPlainText("\n");
    }

}

void MainWindow::on_btnParoEmergencia_clicked()
{
    /*vector<int> rows;

    for (int i = 1; i < 9; ++i)
    {
        int sizeR = rows.size();

        if(sizeR > 4)
        {
            rows.at(0) = i;
            //rotate(rows.begin(), rows.end()-1, rows.end());
            rotate(rows.begin(), rows.begin()+1, rows.end());
            //rotate(rows.end(), rows.begin()+1, rows.begin());
            //rows.at(rows.size()-1) = i;
        }
        else {
            rows.push_back(i);
        }


        // Display current values of row.
        QString debugString;
        for (vector<int>::iterator it = rows.begin(); it != rows.end(); ++it)
        {
            debugString += QString::number(*it);
            //qDbg << ", " << *it;
        }
        //qDbg << "\n";
        qDbg << debugString;
    }
    */

    driverValuesRow brake_row;

    for(int i = 0; i < 10; i++)
    {
        qDbg << "it: " << i ;
        brake_row.Vin = 12.4 + i;
        brake_row.Temperature = 38.4 + i;

        uint16_t errorRaw = i;
        //QStringList active_errors_list;
        decodeDriverError(errorRaw, brake_row);

        //brake_row.errorsList = active_errors_list;


        /*int brake_mat_size = brake_driverMat.size();
        if(brake_mat_size > 4)
        {
            brake_driverMat.at(0) = brake_row;
            rotate(brake_driverMat.begin(),
                   brake_driverMat.begin()+1,
                   brake_driverMat.end());
        }
        else
        {
            brake_driverMat.push_back(brake_row);
        }
        */
        driverMatrixValues_insert(brake_driverMat, brake_row);


        /*for(vector<driverValuesRow>::iterator it = brake_driverMat.begin();
             it != brake_driverMat.end();
             ++it )
        {
            QString debugString;
            driverValuesRow row = *it;

            debugString += QString::number(row.Vin) + ", ";
            debugString += QString::number(row.Temperature) + ", ";

            QStringList errors = row.errorsList;
            foreach(QString error, errors)
            {
                debugString += error + ", ";
            }
            qDbg << debugString << "\n";


            //qDbg << ", " << *it;
        }
        */
        QString brakeMatString = driverMatrixErrors_display(brake_driverMat);
        //driverMatrixErrors_gridLayoutDisplay(ui->driverErrorsValues_gridLayout, brake_driverMat);
        driverMatrixErrors_gridLayoutDisplay(ui->driverErrorsHeaders_gridLayout, brake_driverMat);
        qDbg << brakeMatString;
        ui->driversValues_txt->setPlainText(brakeMatString);
    }


}
void MainWindow::driverMatrixValues_insert(vector<driverValuesRow>& driverMatrix,
                                          driverValuesRow row)
{
    int mat_size = driverMatrix.size();

    if(mat_size > 4)
    {
        driverMatrix.at(0) = row;
        rotate(driverMatrix.begin(),
               driverMatrix.begin()+1,
               driverMatrix.end());
    }
    else
    {
        driverMatrix.push_back(row);
    }
}

void MainWindow::driverMatrixValues_gridLayoutDisplay(QGridLayout* grid,
                                                      vector<driverValuesRow> driverMatrix)
{
    //TODO: C. Optimizar considerando que la matrix puede tener menos de 5 renglones.
    int row = 1; // The first row is for the headers.
    for(vector<driverValuesRow>::iterator it = driverMatrix.begin();
         it != driverMatrix.end();
         ++it )
    {
        driverValuesRow DriverRow = *it;

        QLayoutItem* gridItem = grid->itemAtPosition(row, 0);
        QLabel* gridLbl = (QLabel*)gridItem->widget();
        gridLbl->setText(QString::number(DriverRow.Vin));

        gridItem = grid->itemAtPosition(row, 1);
        gridLbl = (QLabel*)gridItem->widget();
        gridLbl->setText(QString::number(DriverRow.Temperature));

        for(int col = 2; col < 12; col++)
        {
            QLayoutItem* gridItem = grid->itemAtPosition(row, col);
            QLabel* gridLbl = (QLabel*)gridItem->widget();
            gridLbl->setText(QString::number(DriverRow.errorsArray[col]));
        }
        row++;
    }
}
void MainWindow::driverMatrixErrors_gridLayoutDisplay(QGridLayout* grid,
                                                      vector<driverValuesRow> driverMatrix)
{
    //TODO: C. Optimizar considerando que la matrix puede tener menos de 5 renglones.
    int row = 1; // The first row is for the headers.
    for(vector<driverValuesRow>::iterator it = driverMatrix.begin();
         it != driverMatrix.end();
         ++it )
    {
        driverValuesRow DriverRow = *it;


        for(int col = 0; col < 9; col++)
        {
            QLayoutItem* gridItem = grid->itemAtPosition(row, col);
            QLabel* gridLbl = (QLabel*)gridItem->widget();
            gridLbl->setText(QString::number(DriverRow.errorsArray[col]));
        }
        row++;
    }
}

QString MainWindow::driverMatrixErrors_display(vector<driverValuesRow> driverMatrix)
{

    QString matrixString;

    for(vector<driverValuesRow>::iterator it = driverMatrix.begin();
         it != driverMatrix.end();
         ++it )
    {
        QString rowString;
        driverValuesRow row = *it;

        //rowString += QString::number(row.Vin) + ", ";
        //rowString += QString::number(row.Temperature) + ", ";


        /*QStringList errors = row.errorsList;
        foreach(QString error, errors)
        {
            rowString += error + ", ";
        }*/
        //qDbg << rowString << "\n";
        //rowString += "Errors: ";

        for(int ind = 0; ind < 10; ind++)
        {
            rowString += QString::number(row.errorsArray[ind]) + ", ";
        }

        matrixString += rowString + '\n';
        //qDbg << ", " << *it;
    }
    return matrixString;
}

QString MainWindow::driverMatrixValues_display(vector<driverValuesRow> driverMatrix)
{

    QString matrixString;

    for(vector<driverValuesRow>::iterator it = driverMatrix.begin();
         it != driverMatrix.end();
         ++it )
    {
        QString rowString;
        driverValuesRow row = *it;

        rowString += QString::number(row.Vin) + ", ";
        rowString += QString::number(row.Temperature) + ", ";


        /*QStringList errors = row.errorsList;
        foreach(QString error, errors)
        {
            rowString += error + ", ";
        }*/
        //qDbg << rowString << "\n";
        rowString += "Er: ";
        for(int ind = 0; ind < 10; ind++)
        {
            rowString += QString::number(row.errorsArray[ind]) + ", ";
        }

        matrixString += rowString + '\n';
        //qDbg << ", " << *it;
    }
    return matrixString;
}

bool MainWindow::buscarExpresionRegular_findNextInt(QString expReg, QString fuente, int& match_int)
{

    //QRegularExpression expRegInt_R("J_Y: (\\d+)");

    QRegularExpression RegExp(expReg);
    QRegularExpressionMatch RegExpMatch = RegExp.match(fuente);
    //int indiceJy_Fin
    //int indiceJy_Ini = expRegInt.indexIn(renglonDatos_s);
    if(RegExpMatch.hasMatch() )
    {
        QString match_s = RegExpMatch.captured(1);
        //int match_int = match_s.toInt();
        match_int = match_s.toInt();
        return true;
    }
    else
    {
        return false;
    }
}

bool MainWindow::buscarExpresionRegular_findNextFloat(QString cadHead, QString fuente, float &match_float)
{
    QString expReg = cadHead + ": (-?(\\d+)*(\\.(\\d+))?)";
    QRegularExpression RegExp(expReg);
    QRegularExpressionMatch RegExpMatch = RegExp.match(fuente);
    //int indiceJy_Fin
    //int indiceJy_Ini = expRegInt.indexIn(renglonDatos_s);
    if(RegExpMatch.hasMatch() )
    {
        QString match_s = RegExpMatch.captured(1);
        //int match_int = match_s.toInt();
        match_float = match_s.toFloat();
        return true;
    }
    else
    {
        return false;
    }
}

bool MainWindow::buscarExpresionRegular_PotError(QString fuente, QString& matchString, int& match_int)
{
    // **EPot_I_L: V**"
    // Donde:
    // I: Índice del pot de 0 a 3.
    // L: Puede ser "L" o "H".
    // V: Valor del pot con índice N (Entero positivo).
    QString RegExpTarget = "(\\*\\*" + PotError_header + ")(.+)(\\*\\*)";
    QRegularExpression RegExp(RegExpTarget);
    QRegularExpressionMatch RegExpMatch = RegExp.match(fuente);
    if(RegExpMatch.hasMatch() )
    {
       matchString = RegExpMatch.captured(0);
       /// TODO: B. Definir el índice del pot y ponerlo en la sección correspondiente.
       return true;
    }
    return false;
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


void MainWindow::decodeDriverError(const uint16_t errorRaw, driverValuesRow& row)
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

    QStringList errorsLst = {
            "0SfStrtV",
            "1ReqChIv",
            "2SerlErr",
            "3ComTmOt",
            "4LimSwch",
            "5LowVin",
            "6HighVin",
            "7OverTmp",
            "8MDrvErr",
            "9ErrLinH"  };


    for(uint8_t bit = 0; bit < 10; bit++) // 0 to 9.
    {
        //qDbg << "bit: " << bit;
        uint16_t mask = pow(2, bit);
        //qDbg << "mask: " << mask;

        uint16_t errorBit = errorRaw & mask;
        if(errorBit)
        {
            row.errorsArray[bit] = 1;

            QString errorDesc = errorsLst[bit];
            //qDbg << errorDesc;
            row.errorsList.append(errorDesc);
        }
        else{
            row.errorsArray[bit] = 0;
        }
    }
}

bool MainWindow::Limits_update(int currentValue,    int& min,        int& max,
                                                    QLabel* min_lbl, QLabel* max_lbl)
{
    if(currentValue < 0 || currentValue > 1023)
    {
        return false;
    }
    else
    {
        if( currentValue < min )
        {
            min = currentValue;
            min_lbl->setText(QString::number(min));
        }

        if( currentValue > max )
        {
            max = currentValue;
            max_lbl->setText(QString::number(max));
        }
    }
    return true;
}

void MainWindow::displayInfoJoystick(QString renglonDatos)
{
    //** Joystick Y
    bool jy_Received = buscarExpresionRegular_findNextInt("J_Y: (\\d+)", renglonDatos, valorJy);

    if(jy_Received)
    {
        ui->joystick_Y_lcd->display(valorJy);
        ui->joystickVertical_sld->setValue(valorJy);

        bool limitsValid_Jy = Limits_update(valorJy,    Joy_Y_min,      Joy_Y_max,
                                                        ui->Jy_Min_lbl, ui->Jy_Max_lbl);
        if(!limitsValid_Jy)
        {
            QString msg = "J_y. Valor rcv fuera de valores lógicos (0, 1023)";
            ui->erroresSalida_txt->insertPlainText(msg);
            ui->erroresSalida_txt->insertPlainText(renglonDatos);

            qDebug() << msg;
            qDebug() << "Renglón datos: " << renglonDatos;
        }
    }

    //** Joystick X
    bool Jx_received = buscarExpresionRegular_findNextInt("J_X: (\\d+)", renglonDatos, valorJx);
    if(Jx_received)
    {
        ui->joystick_X_lcd->display(valorJx);
        ui->joystickHorizontal_Sld->setValue(valorJx);

        bool limitsValid_Jx = Limits_update(valorJx,    Joy_X_min,      Joy_X_max,
                                                        ui->Jx_Min_lbl, ui->Jx_Max_lbl);
        if(!limitsValid_Jx)
        {
            ui->erroresSalida_txt->insertPlainText(QString("J_x. Valor rcv fuera de valores lógicos (0, 1023)"));
            ui->erroresSalida_txt->insertPlainText(renglonDatos);
        }
    }

    //** Activado
    bool statusJoystickActivado_Received =
            buscarExpresionRegular_findNextInt(cadJoystickActivado+ ": (-?(\\d+))",
                                         renglonDatos, Joystick_Activado);
    //if(statusJoystickActivado_Received)
    //{
        checkBoxBouncing(ui->joystick_Activado_chk, statusJoystickActivado_Received);
        checkBoxColor(ui->joystick_Activado_chk);
    //}

    //** Desconectado
    QString cadJyDescFull = "(\\*\\*)(" + cadJy_Desc + ")(\\*\\*)";
    bool LED_Joystick_Y_Desconectado = buscarExpresionRegular(cadJyDescFull, renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Joy_Y_Desc, LED_Joystick_Y_Desconectado);
    checkBoxColor_Error(ui->chk_LED_Joy_Y_Desc);

    bool LED_Joystick_X_Desconectado = buscarExpresionRegular("(\\*\\*)(" + cadJx_Desc + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Joy_X_Desc, LED_Joystick_X_Desconectado);
    checkBoxColor_Error(ui->chk_LED_Joy_X_Desc);

    //** OutOfRange
    bool LED_Joystick_Y_OutOfRange = buscarExpresionRegular("(\\*\\*)(" + cadJy_OutOfRange + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Joy_Y_OutR, LED_Joystick_Y_OutOfRange);
    checkBoxColor_Error(ui->chk_LED_Joy_Y_OutR);

    bool LED_Joystick_X_OutOfRange = buscarExpresionRegular("(\\*\\*)(" + cadJx_OutOfRange + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Joy_X_OutR, LED_Joystick_X_OutOfRange);
    checkBoxColor_Error(ui->chk_LED_Joy_X_OutR);

}
void MainWindow::displayInfoButtons(QString renglonDatos)
{
    /// Fix Brake Position.
    buscarExpresionRegular_findNextInt("bFB: (-?(\\d+))",
                                        renglonDatos, statusFixFreno);
    checkBoxBouncing(ui->FixFreno_chk, statusFixFreno);

    /// Modo Carretera
    buscarExpresionRegular_findNextInt("bMC: (-?(\\d+))",
                                        renglonDatos, statusModoCarr);
    checkBoxBouncing(ui->RoadMode_chk, statusModoCarr );

    buscarExpresionRegular_findNextInt("bPU: (-?(\\d+))",
                                         renglonDatos, statusPalancaUp);
    checkBoxBouncing(ui->PalUp_chk, statusPalancaUp);

    buscarExpresionRegular_findNextInt("bPD: (-?(\\d+))",
                                         renglonDatos, statusPalancaDown);
    checkBoxBouncing(ui->PalDown_chk, statusPalancaDown);
}
void MainWindow::displayInfoBrake(QString renglonDatos)
{
    buscarExpresionRegular_findNextInt("B_p: (-?(\\d+))", renglonDatos, B_pos);
    ui->frenoPos_lcd->display(B_pos);

    bool BPosValid = Limits_update(B_pos,
                  Brake_pos_min,                Brake_pos_max,
                  ui->brake_PosLimits_Min_lbl,  ui->brake_PosLimits_Max_lbl);

    if(!BPosValid)
    {
        QString msg = "Brake. Valor rcv fuera de valores lógicos (0, 1023)";
        ui->erroresSalida_txt->insertPlainText(msg);
        ui->erroresSalida_txt->insertPlainText(renglonDatos);
        //customMessageHandler(QtMsgType::QtInfoMsg, msg );
        qDebug() << msg;
        qDebug() << "Renglón datos: " << renglonDatos;
    }

    bool B_tgt_Flag = buscarExpresionRegular_findNextInt("B_t: (-?(\\d+))", renglonDatos, B_tgt);
    if(B_tgt_Flag)   ui->frenoDes_lcd->display(B_tgt);

    bool B_e_Flag = buscarExpresionRegular_findNextInt("B_e: (-?(\\d+))", renglonDatos, B_Pos_Error);
    if(B_e_Flag)    ui->Freno_lcdError->display(B_Pos_Error);

    bool B_c_Flag =  buscarExpresionRegular_findNextInt("B_c: (-?(\\d+))", renglonDatos, B_Ctrl);
    // -?(\\d+) = Uno o ningún signo menos, seguido de uno o más dígitos.
    if(B_c_Flag) {
        ui->frenoControl_lcd->display(B_Ctrl);
        ui->FrenoControl_Slider->setValue(B_Ctrl);
    }

    //** Brake Activado
    bool flagB_Act = buscarExpresionRegular_findNextInt(cadBrakeActivado + ": (-?(\\d+))",
                                                renglonDatos, B_Activado);
    checkBoxBouncing(ui->Freno_Activado_chk, flagB_Act);
    checkBoxColor(ui->Freno_Activado_chk);

    //** Brake Disconnected
    bool LED_Freno_Desconectado = buscarExpresionRegular("(\\*\\*)(" + cadBrakeDesc + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Freno_Desc, LED_Freno_Desconectado);
    checkBoxColor_Error(ui->chk_LED_Freno_Desc);

    //** Brake Inhibido
    buscarExpresionRegular_findNextInt(cadBrakeInhibido + ": (-?(\\d+))",
                                         renglonDatos, B_Inhibido);
    checkBoxBouncing(ui->Freno_Inhibido_chk, B_Inhibido);
    checkBoxColor_Error(ui->Freno_Inhibido_chk);

    //** Brake OutOfRange
    bool LED_Freno_OutOfRange = buscarExpresionRegular("(\\*\\*)(" + cadBrake_OutOfRange + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Freno_OutR, LED_Freno_OutOfRange);
    checkBoxColor_Error(ui->chk_LED_Freno_OutR);


    //** Brake Driver Info
    driverValuesRow brake_row;
    //QStringList brake_errors_list;


    bool B_Vin_found = buscarExpresionRegular_findNextInt(cadBrake_VIN + ": (-?(\\d+))",
                                                            renglonDatos, B_Vin);
    bool B_Temp_found = buscarExpresionRegular_findNextInt(cadBrake_Temp  + ": (-?(\\d+))",
                                                            renglonDatos, B_Temp);
    bool B_Driver_Errors_found = buscarExpresionRegular_findNextInt(cadBrake_Error + ": (-?(\\d+))",
                                                            renglonDatos, B_Driver_Errors);


    if(B_Vin_found)
    {
        // When turned off the serial bus of the drivers return 65535.
        if(B_Vin > -1) // 1000 mV = 1V
        {

            float B_Vin_f = (float)B_Vin / 1000.0; // Received en mV.
            ui->Brake_VIN_lbl->setText(QString::number(B_Vin_f));
            brake_row.Vin = B_Vin_f;
        }
        else
        {
            ui->Brake_VIN_lbl->setText("NA");
        }
    }


    if(B_Temp_found)
    {
        if(B_Temp > -1)
        {
            //if(B_Temp > 100) //100 = 10 °C
            float B_Temp_f = (float)B_Temp / 10.0; // Received in 0.1 °C
            ui->Brake_Temp_lbl->setText(QString::number(B_Temp_f));
            brake_row.Temperature = B_Temp_f;
            ui->Brake_Error_lbl->setText(QString::number(B_Driver_Errors));
        }
        else
        {
            ui->Brake_Error_lbl->setText("NA");
        }
    }
        //decodeDriverError(B_Errors_Driver, brake_errors_list);

    if(B_Driver_Errors_found)
    {
        decodeDriverError((uint16_t)B_Driver_Errors, brake_row);
        driverMatrixValues_insert(brake_driverValuesMatrix, brake_row);

        if(B_Driver_Errors > -1)
        {
            if(ui->brake_ShowInfo_rBtn->isChecked())
            {
                //driverMatrixErrors_gridLayoutDisplay(ui->driverErrorsValues_gridLayout, brake_driverValuesMatrix);
                driverMatrixValues_gridLayoutDisplay(ui->driverErrorsHeaders_gridLayout,
                                                     brake_driverValuesMatrix);
                QString brake_MatrixString = driverMatrixValues_display(brake_driverValuesMatrix);
                //QString brake_MatrixString = driverMatrixErrors_display(brake_driverValuesMatrix);
                ui->driversValues_txt->insertPlainText(brake_MatrixString);
            }
        }
        else
        {
            // Se recibió valor de -1
            //QString brake_comm_error = "NA";
            //ui->driversValues_txt->insertPlainText(brake_comm_error);
            ui->Brake_Error_lbl->setText("NA");
        }
    }

}
void MainWindow::displayInfoAccel(QString renglonDatos)
{
    //** Control info
    buscarExpresionRegular_findNextInt("A_p: (-?(\\d+))", renglonDatos, A_pos);
    ui->aceleradorPos_lcd->display(A_pos);

    bool AccPosValid = Limits_update(A_pos, Accel_pos_min, Accel_pos_max,
                  ui->Accel_PosLimits_Min_lbl, ui->Accel_PosLimits_Max_lbl);

     if(!AccPosValid)
     {
         QString msg = "Accel. Valor rcv fuera de valores lógicos (0, 1023)";
         ui->erroresSalida_txt->insertPlainText(msg);
         ui->erroresSalida_txt->insertPlainText(renglonDatos);

         qDebug() << msg;
         qDebug() << "Renglón datos: " << renglonDatos;
     }

    buscarExpresionRegular_findNextInt("A_t: (-?(\\d+))", renglonDatos, A_tgt);
    ui->aceleradorDes_lcd->display(A_tgt);

    buscarExpresionRegular_findNextInt("A_e: (-?(\\d+))", renglonDatos, A_Pos_Error);
    ui->Acelerador_lcdError->display(A_Pos_Error);

    buscarExpresionRegular_findNextInt("A_c: (-?(\\d+))", renglonDatos, A_Ctrl);
    ui->aceleradorControl_lcd->display(A_Ctrl);
    ui->AceleradorControl_Slider->setValue(A_Ctrl);

    //** Accel Activated
    bool flagAccelAct = buscarExpresionRegular_findNextInt(cadAcelActivado + ": (-?(\\d+))",
                                                renglonDatos, A_Activado);
    //qDbg << "statusAcelActivado" << statusAcelActivado;
    checkBoxBouncing(ui->Acel_Activado_chk, flagAccelAct);
    checkBoxColor(ui->Acel_Activado_chk);

    //** Inhibido
    buscarExpresionRegular_findNextInt(cadAcelInhibido + ": (-?(\\d+))",
                                                 renglonDatos, A_Inhibido);
    checkBoxBouncing(ui->Acel_Inhibido_chk, A_Inhibido);
    checkBoxColor_Error(ui->Acel_Inhibido_chk);

    //** Accelerator Desconectado
    bool LED_Acelerador_Desconectado = buscarExpresionRegular("(\\*\\*)(" + cadAcel_Desc + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Acel_Desc, LED_Acelerador_Desconectado);
    checkBoxColor_Error(ui->chk_LED_Acel_Desc);

    //bool LED_Acel_OutOfRange = buscarExpresionRegular("(\\*\\*)(Acelerador_OutOfRange)(\\*\\*)", renglonDatos);
    bool LED_Acel_OutOfRange = buscarExpresionRegular("(\\*\\*)(" + cadAcel_OutOfRange + ")(\\*\\*)", renglonDatos);
    checkBoxBouncing_Errors(ui->chk_LED_Acel_OutR, LED_Acel_OutOfRange);
    checkBoxColor_Error(ui->chk_LED_Acel_OutR);

    // **Info driver
    driverValuesRow accel_row;
    //QStringList accel_errors_list;

    bool A_Vin_found = buscarExpresionRegular_findNextInt(cadAccel_VIN + ": (-?(\\d+))",
                                                renglonDatos, A_Vin);
    bool A_Temp_found  = buscarExpresionRegular_findNextInt(cadAccel_Temp  + ": (-?(\\d+))",
                                                renglonDatos, A_Temp);
    bool A_Driver_Errors_found = buscarExpresionRegular_findNextInt(cadAccel_Error + ": (-?(\\d+))",
                                                renglonDatos, A_Driver_Errors);

    if(A_Vin_found)
    {
        float A_Vin_f = (float)A_Vin / 1000.0; // Received en mV.
        ui->Accel_Vin_lbl->setText(QString::number(A_Vin_f));
        accel_row.Vin = A_Vin_f;
    }

    if(A_Temp_found)
    {
        float A_Temp_f = (float)A_Temp / 10.0; // Received in 0.1 °C
        ui->Accel_Temp_lbl->setText(QString::number(A_Temp_f));
        accel_row.Temperature = A_Temp_f;
    }

    if(A_Driver_Errors_found)
    {
        ui->Accel_Error_lbl->setText(QString::number(A_Driver_Errors));

        decodeDriverError(A_Driver_Errors, accel_row);
        driverMatrixValues_insert(accel_driverValuesMatrix, accel_row);

        if(ui->accel_ShowInfo_rBtn->isChecked())
        {
            driverMatrixValues_gridLayoutDisplay(ui->driverErrorsHeaders_gridLayout,
                                                 accel_driverValuesMatrix);

            QString accel_MatrixString = driverMatrixValues_display(accel_driverValuesMatrix);
            ui->driversValues_txt->insertPlainText(accel_MatrixString);
        }

    }

}

void MainWindow::displayInfoSteer(QString renglonDatos)
{

    buscarExpresionRegular_findNextInt(cadVolanteControl + ": (-?(\\d+))",
                                         renglonDatos, V_Ctrl);
    //qDebug() << "V_Ctrl: " << V_Ctrl;
    ui->volante_lcd->display(V_Ctrl);
    ui->VolanteControl_Dial->setValue(V_Ctrl);


    bool V_cadActiv_found = buscarExpresionRegular_findNextInt(cadVolanteActivado + ": (-?(\\d+))",
                                         renglonDatos, V_Activado);
    checkBoxBouncing(ui->volante_Activado_chk, V_cadActiv_found);
    checkBoxColor(ui->volante_Activado_chk);

    buscarExpresionRegular_findNextInt(cadVolanteModo + ": (-?(\\d+))",
                                         renglonDatos, V_Mode);
    ui->VolanteModo_cmb->setCurrentIndex(V_Mode);
    if(V_Mode == 0)    { // Modo Inhibido.
        checkBoxBouncing(ui->volante_Inhibido_chk, true);

    } else {
        checkBoxBouncing(ui->volante_Inhibido_chk, false);
    }
    checkBoxColor_Error(ui->volante_Inhibido_chk);

    // **Info driver
    driverValuesRow steer_row;

    bool V_Vin_found = buscarExpresionRegular_findNextInt(cadSteer_VIN + ": (-?(\\d+))",
                                                    renglonDatos, V_Vin);
    bool V_Temp_found = buscarExpresionRegular_findNextInt(cadSteer_Temp  + ": (-?(\\d+))",
                                                    renglonDatos, V_Temp);
    bool V_Driver_Errors_found = buscarExpresionRegular_findNextInt(cadSteer_Error + ": (-?(\\d+))",
                                                    renglonDatos, V_Driver_Errors);


    if(V_Vin_found)
    {
        float V_Vin_f = (float)V_Vin / 1000.0; // Received en mV.
        ui->Steer_Vin_lbl->setText(QString::number(V_Vin_f));
        steer_row.Vin = V_Vin_f;
    }

    if(V_Temp_found)
    {
        float V_Temp_f = (float)V_Temp / 10.0; // Received in 0.1 °C
        ui->Steer_Temp_lbl->setText(QString::number(V_Temp_f));
        steer_row.Temperature = V_Temp_f;
        ui->Steer_Error_lbl->setText(QString::number(V_Driver_Errors));
    }

    if(V_Driver_Errors_found )
    {
        decodeDriverError(V_Driver_Errors, steer_row);
        driverMatrixValues_insert(steer_driverValuesMatrix, steer_row);

        if(ui->steer_ShowInfo_rBtn->isChecked())
        {
            driverMatrixValues_gridLayoutDisplay(ui->driverErrorsHeaders_gridLayout, steer_driverValuesMatrix);

            QString steer_MatrixString = driverMatrixValues_display(steer_driverValuesMatrix);
            ui->driversValues_txt->insertPlainText(steer_MatrixString);
        }
    }

    //if(ui->steer_ShowInfo_rBtn->isChecked() && (!V_Vin_found || !))
    //{
}


void MainWindow::displayInfoShiftGear(QString renglonDatos)
{
    bool shiftAct = buscarExpresionRegular_findNextInt(cadPalancaActivada + ": (-?(\\d+))",
                                            renglonDatos, ShiftGear_Activated);

    checkBoxBouncing(ui->palanca_Activada_chk, shiftAct);
    checkBoxColor(ui->palanca_Activada_chk);

}
void MainWindow::displaySystemInfo(QString renglonDatos)
{

    //** System Status
    bool systemStatusFound =
            buscarExpresionRegular_findNextInt("edo: (\\d+)", renglonDatos, SystemStatusNum);
    //qDebug() << "Edo Sistema: " << edoSistema;
    if(!systemStatusFound)
    {
        SystemStatusNum = 7; // (NA)
    }

    QStringList estadosSistema = {"OK", "Mnt Req", "Return Home", "Safe Parking",
                                  "Immediate Stop", "Emergency Stop", "Emergency Braking", "NA"};
    QString edoSist = estadosSistema[SystemStatusNum];

    QString edoSistema_str = QString::number(SystemStatusNum) + ": " + edoSist;
    ui->estadoSistema_lbl->setText(edoSistema_str);

    //** T, T_min and T_max
    bool T_found = buscarExpresionRegular_findNextInt(cadT + ":(\\d+)", renglonDatos, T_sys);
    ui->T_lbl->setText(QString::number(T_sys));

    if(T_found) {
        Limits_update(T_sys, T_min, T_max,
                  ui->T_min_lbl, ui->T_max_lbl);
    }

    //** Normal Defines
    buscarExpresionRegular_findNextInt(cadNormalDefines + ": (\\d+)",
                                         renglonDatos, normalDefines);

    checkBoxBouncing(ui->normalDefines_chk, normalDefines);
    checkBoxColor(ui->normalDefines_chk);
}


void MainWindow::displayTemperature(QString renglonDatos)
{
    float Micro_TempC;
    bool Micro_TempC_Found = buscarExpresionRegular_findNextFloat(cadTemp_uC, renglonDatos, Micro_TempC);
    if(Micro_TempC_Found)
    {
        ui->Temp_uC_lbl->setText(QString::number(Micro_TempC));
    }
    else
    {
        qDebug() << "Tm_uC not found";
    }

    float Therm1_TempC;
    float Therm1Temp_Found = buscarExpresionRegular_findNextFloat(cadTemp_Therm1, renglonDatos, Therm1_TempC);
    if(Therm1Temp_Found)
    {
        ui->Temp_Therm1_lbl->setText(QString::number(Therm1_TempC));
    }


    float Therm2_TempC;
    float Therm2Temp_Found = buscarExpresionRegular_findNextFloat(cadTemp_Therm2, renglonDatos, Therm2_TempC);
    if(Therm2Temp_Found)
    {
        ui->Temp_Therm2_lbl->setText(QString::number(Therm2_TempC));
    }
}

void MainWindow::displayPotsErrors(QString renglonDatos)
{
    QString matchPotError;
    int potIndex;
    bool potError = buscarExpresionRegular_PotError(renglonDatos, matchPotError, potIndex);
    if(potError)
    {
        ui->erroresSalida_txt->insertPlainText(matchPotError);
        ui->erroresSalida_txt->insertPlainText("\n");
        qDebug() << "ErrorPot:" << matchPotError;
    }
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

void MainWindow::checkBoxBouncing(QCheckBox *chkBox, bool statusRcv)
{
    // Atención que -1 se considera true.

    bool chkStatus = chkBox->checkState();

    if(statusRcv && !chkStatus)
    {
        chkBox->setChecked(true);
    }
    else if(!statusRcv && chkStatus)
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

void MainWindow::checkBoxColor_Error(QCheckBox * chkBox)
{
    bool status = chkBox->isChecked();
    if(status)
    {
        chkBox->setStyleSheet("background-color: rgb(255, 85, 0);\ncolor: rgb(255, 255, 0);");
    }else {
        chkBox->setStyleSheet("background-color: rgb(0, 85, 255);\ncolor: rgb(255, 255, 0);");
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


/// Communication functions
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
        fillPortsInfo();
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
    //if(!ui->btnConectar->isEnabled())
    if(serial->isOpen()  &&  serial->isReadable())
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
        }
    }
}

void MainWindow::escribir(const char* datos)
{
    #if CERRAR_PUERTO_SERIAL
    serial->open(QIODevice::ReadWrite); //Ya debe estar abierto.
    #endif
    if(serial->isOpen()  &&  serial->isWritable())
    {
        //qDebug() << datos;
        //serial->write(datos.toStdString().c_str());
        serial->write(datos);

        if(serial->flush()) {
            qDebug() << "ok";
        }
        #if CERRAR_PUERTO_SERIAL
        serial->close(); //Probar sin cerrar.
        #endif
    }
    else
    {
        qDebug() << "Error: Puerto cerrado.";
    }
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

void MainWindow::showPortInfo(int idx)
{
    // Mostrar la información del puerto en la etiqueta lblDescripción
    if(idx != -1)
    {
        QStringList list = ui->cmbSerialPortSelector->itemData(idx).toStringList();
        ui->lblDescripcion->setText(tr("Descripción: %1").arg(list.at(1)));
    }
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


/*void MainWindow::dibujarVolante(float anguloGrados)
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
}*/


bool MainWindow::saveRanges()
{
    QString dataFileName = "./rangeValues.txt";
    QFile file(dataFileName);

    if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream stream(&file);

        stream << "Jy_Min:" << Joy_Y_min << endl;
        stream << "Jy_Max:" << Joy_Y_max << endl;

        stream << "Jx_Min:" << Joy_X_min << endl;
        stream << "Jx_Max:" << Joy_X_max << endl << endl;

        stream << "Brake_Pos_Min:" << Brake_pos_min << endl;
        stream << "Brake_Pos_Max:" << Brake_pos_max << endl << endl;

        stream << "Accel_Pos_Max:" << Accel_pos_max << endl;
        stream << "Accel_Pos_Min:" << Accel_pos_min << endl;
    }

    file.close();
    QMessageBox::information(this, "Datos guardados", "The range data is saved. Hopefully... you better check pal");
    //msgClosing.show();
}


void MainWindow::on_actionGuardar_rangos_triggered()
{
    saveRanges();
}

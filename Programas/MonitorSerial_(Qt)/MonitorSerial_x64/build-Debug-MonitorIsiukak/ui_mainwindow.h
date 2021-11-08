/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConfigurar;
    QAction *actionBuscar_puertos;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *valores_y_Conexion_Widget;
    QHBoxLayout *Valores_Widget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblDescripcion;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *cmbBaudRate;
    QComboBox *cmbSerialPortSelector;
    QHBoxLayout *horizontalLayout;
    QGroupBox *grp_Joystick;
    QVBoxLayout *verticalLayout_6;
    QFormLayout *formLayout_2;
    QLabel *joystick_X_lbl;
    QLCDNumber *joystick_X_lcd;
    QLabel *joystick_Y_lbl;
    QLCDNumber *joystick_Y_lcd;
    QVBoxLayout *verticalLayout_10;
    QSlider *joystickVertical_sld;
    QSlider *joystickHorizontal_Sld;
    QGroupBox *grp_Volante;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_11;
    QFormLayout *formLayout;
    QLabel *valorVolante_lbl;
    QLCDNumber *volante_lcd;
    QDial *VolanteControl_Dial;
    QSlider *horizontalSlider_2;
    QGroupBox *grp_Acelerador;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *frmLay_Acelerador;
    QLabel *valorAcelerador_lbl;
    QLCDNumber *aceleradorPos_lcd;
    QLabel *label_3;
    QLabel *label_4;
    QLCDNumber *aceleradorDes_lcd;
    QLCDNumber *aceleradorControl_lcd;
    QLabel *label_5;
    QLCDNumber *Acelerador_lcdError;
    QSlider *AceleradorControl_Slider;
    QGroupBox *grp_Freno;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *frmLay_Freno;
    QLabel *valorFreno_lbl;
    QLCDNumber *frenoPos_lcd;
    QLabel *label;
    QLCDNumber *frenoDes_lcd;
    QLCDNumber *Freno_lcdError;
    QLabel *Freno_lblError;
    QLCDNumber *frenoControl_lcd;
    QLabel *label_2;
    QSlider *FrenoControl_Slider;
    QGroupBox *grp_Botones;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *FixFreno_chk;
    QCheckBox *PalUp_chk;
    QCheckBox *PalDown_chk;
    QCheckBox *RoadMode_chk;
    QGroupBox *grp_LEDs;
    QVBoxLayout *verticalLayout_13;
    QGridLayout *gridLayout;
    QCheckBox *chk_LED_Joy_X_Desc;
    QCheckBox *chk_LED_Joy_Y_Desc;
    QCheckBox *chk_LED_Joy_X_OutR;
    QCheckBox *chk_LED_Freno_Desc;
    QCheckBox *chk_LED_Freno_OutR;
    QCheckBox *chk_LED_Acel_Desc;
    QCheckBox *chk_LED_Joy_Y_OutR;
    QCheckBox *chk_LED_Acel_OutR;
    QLabel *lblLEDsError_Desc;
    QLabel *lblLEDsError_OutRange;
    QWidget *ConexionConfigForm_Widget;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lblEstadoSistema;
    QLabel *estadoSistema_lbl;
    QPlainTextEdit *erroresSalida_txt;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnParoEmergencia;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnConectar;
    QPushButton *btnDesconectar;
    QWidget *SalidaConsola_Widget;
    QHBoxLayout *horizontalLayout_5;
    QPlainTextEdit *InfoSalida_txt;
    QMenuBar *menuBar;
    QMenu *menuConfiguraci_n;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1073, 625);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionConfigurar = new QAction(MainWindow);
        actionConfigurar->setObjectName(QString::fromUtf8("actionConfigurar"));
        actionBuscar_puertos = new QAction(MainWindow);
        actionBuscar_puertos->setObjectName(QString::fromUtf8("actionBuscar_puertos"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        valores_y_Conexion_Widget = new QWidget(centralWidget);
        valores_y_Conexion_Widget->setObjectName(QString::fromUtf8("valores_y_Conexion_Widget"));
        sizePolicy.setHeightForWidth(valores_y_Conexion_Widget->sizePolicy().hasHeightForWidth());
        valores_y_Conexion_Widget->setSizePolicy(sizePolicy);
        Valores_Widget = new QHBoxLayout(valores_y_Conexion_Widget);
        Valores_Widget->setSpacing(6);
        Valores_Widget->setContentsMargins(11, 11, 11, 11);
        Valores_Widget->setObjectName(QString::fromUtf8("Valores_Widget"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lblDescripcion = new QLabel(valores_y_Conexion_Widget);
        lblDescripcion->setObjectName(QString::fromUtf8("lblDescripcion"));

        horizontalLayout_4->addWidget(lblDescripcion);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cmbBaudRate = new QComboBox(valores_y_Conexion_Widget);
        cmbBaudRate->setObjectName(QString::fromUtf8("cmbBaudRate"));

        horizontalLayout_2->addWidget(cmbBaudRate);

        cmbSerialPortSelector = new QComboBox(valores_y_Conexion_Widget);
        cmbSerialPortSelector->addItem(QString());
        cmbSerialPortSelector->addItem(QString());
        cmbSerialPortSelector->addItem(QString());
        cmbSerialPortSelector->addItem(QString());
        cmbSerialPortSelector->addItem(QString());
        cmbSerialPortSelector->setObjectName(QString::fromUtf8("cmbSerialPortSelector"));

        horizontalLayout_2->addWidget(cmbSerialPortSelector);


        horizontalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_7->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        grp_Joystick = new QGroupBox(valores_y_Conexion_Widget);
        grp_Joystick->setObjectName(QString::fromUtf8("grp_Joystick"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(grp_Joystick->sizePolicy().hasHeightForWidth());
        grp_Joystick->setSizePolicy(sizePolicy1);
        verticalLayout_6 = new QVBoxLayout(grp_Joystick);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        joystick_X_lbl = new QLabel(grp_Joystick);
        joystick_X_lbl->setObjectName(QString::fromUtf8("joystick_X_lbl"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(joystick_X_lbl->sizePolicy().hasHeightForWidth());
        joystick_X_lbl->setSizePolicy(sizePolicy2);
        joystick_X_lbl->setMinimumSize(QSize(10, 50));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, joystick_X_lbl);

        joystick_X_lcd = new QLCDNumber(grp_Joystick);
        joystick_X_lcd->setObjectName(QString::fromUtf8("joystick_X_lcd"));
        joystick_X_lcd->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(joystick_X_lcd->sizePolicy().hasHeightForWidth());
        joystick_X_lcd->setSizePolicy(sizePolicy3);
        joystick_X_lcd->setMinimumSize(QSize(50, 40));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        joystick_X_lcd->setFont(font);
        joystick_X_lcd->setDigitCount(4);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, joystick_X_lcd);

        joystick_Y_lbl = new QLabel(grp_Joystick);
        joystick_Y_lbl->setObjectName(QString::fromUtf8("joystick_Y_lbl"));
        sizePolicy2.setHeightForWidth(joystick_Y_lbl->sizePolicy().hasHeightForWidth());
        joystick_Y_lbl->setSizePolicy(sizePolicy2);
        joystick_Y_lbl->setMinimumSize(QSize(10, 50));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, joystick_Y_lbl);

        joystick_Y_lcd = new QLCDNumber(grp_Joystick);
        joystick_Y_lcd->setObjectName(QString::fromUtf8("joystick_Y_lcd"));
        sizePolicy3.setHeightForWidth(joystick_Y_lcd->sizePolicy().hasHeightForWidth());
        joystick_Y_lcd->setSizePolicy(sizePolicy3);
        joystick_Y_lcd->setMinimumSize(QSize(50, 50));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        joystick_Y_lcd->setFont(font1);
        joystick_Y_lcd->setDigitCount(4);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, joystick_Y_lcd);


        verticalLayout_6->addLayout(formLayout_2);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        joystickVertical_sld = new QSlider(grp_Joystick);
        joystickVertical_sld->setObjectName(QString::fromUtf8("joystickVertical_sld"));
        joystickVertical_sld->setMinimumSize(QSize(0, 60));
        joystickVertical_sld->setMinimum(370);
        joystickVertical_sld->setMaximum(640);
        joystickVertical_sld->setPageStep(36);
        joystickVertical_sld->setValue(512);
        joystickVertical_sld->setOrientation(Qt::Vertical);
        joystickVertical_sld->setTickPosition(QSlider::TicksBelow);

        verticalLayout_10->addWidget(joystickVertical_sld);

        joystickHorizontal_Sld = new QSlider(grp_Joystick);
        joystickHorizontal_Sld->setObjectName(QString::fromUtf8("joystickHorizontal_Sld"));
        joystickHorizontal_Sld->setMinimum(374);
        joystickHorizontal_Sld->setMaximum(640);
        joystickHorizontal_Sld->setPageStep(33);
        joystickHorizontal_Sld->setValue(512);
        joystickHorizontal_Sld->setOrientation(Qt::Horizontal);
        joystickHorizontal_Sld->setTickPosition(QSlider::TicksAbove);

        verticalLayout_10->addWidget(joystickHorizontal_Sld);


        verticalLayout_6->addLayout(verticalLayout_10);


        horizontalLayout->addWidget(grp_Joystick);

        grp_Volante = new QGroupBox(valores_y_Conexion_Widget);
        grp_Volante->setObjectName(QString::fromUtf8("grp_Volante"));
        sizePolicy1.setHeightForWidth(grp_Volante->sizePolicy().hasHeightForWidth());
        grp_Volante->setSizePolicy(sizePolicy1);
        verticalLayout_5 = new QVBoxLayout(grp_Volante);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        valorVolante_lbl = new QLabel(grp_Volante);
        valorVolante_lbl->setObjectName(QString::fromUtf8("valorVolante_lbl"));
        valorVolante_lbl->setMinimumSize(QSize(28, 0));

        formLayout->setWidget(0, QFormLayout::LabelRole, valorVolante_lbl);

        volante_lcd = new QLCDNumber(grp_Volante);
        volante_lcd->setObjectName(QString::fromUtf8("volante_lcd"));
        sizePolicy.setHeightForWidth(volante_lcd->sizePolicy().hasHeightForWidth());
        volante_lcd->setSizePolicy(sizePolicy);
        volante_lcd->setMinimumSize(QSize(65, 60));
        QFont font2;
        font2.setPointSize(14);
        volante_lcd->setFont(font2);

        formLayout->setWidget(0, QFormLayout::FieldRole, volante_lcd);


        verticalLayout_11->addLayout(formLayout);


        verticalLayout_5->addLayout(verticalLayout_11);

        VolanteControl_Dial = new QDial(grp_Volante);
        VolanteControl_Dial->setObjectName(QString::fromUtf8("VolanteControl_Dial"));
        VolanteControl_Dial->setAutoFillBackground(false);
        VolanteControl_Dial->setMinimum(-3200);
        VolanteControl_Dial->setMaximum(3200);
        VolanteControl_Dial->setSingleStep(100);
        VolanteControl_Dial->setPageStep(400);
        VolanteControl_Dial->setInvertedAppearance(false);

        verticalLayout_5->addWidget(VolanteControl_Dial);

        horizontalSlider_2 = new QSlider(grp_Volante);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setEnabled(false);
        horizontalSlider_2->setMinimum(-3200);
        horizontalSlider_2->setMaximum(3200);
        horizontalSlider_2->setSingleStep(100);
        horizontalSlider_2->setPageStep(800);
        horizontalSlider_2->setTracking(true);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_2->setInvertedAppearance(false);
        horizontalSlider_2->setInvertedControls(false);
        horizontalSlider_2->setTickPosition(QSlider::TicksAbove);
        horizontalSlider_2->setTickInterval(800);

        verticalLayout_5->addWidget(horizontalSlider_2);


        horizontalLayout->addWidget(grp_Volante);

        grp_Acelerador = new QGroupBox(valores_y_Conexion_Widget);
        grp_Acelerador->setObjectName(QString::fromUtf8("grp_Acelerador"));
        sizePolicy1.setHeightForWidth(grp_Acelerador->sizePolicy().hasHeightForWidth());
        grp_Acelerador->setSizePolicy(sizePolicy1);
        grp_Acelerador->setFlat(false);
        verticalLayout_4 = new QVBoxLayout(grp_Acelerador);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        frmLay_Acelerador = new QFormLayout();
        frmLay_Acelerador->setSpacing(6);
        frmLay_Acelerador->setObjectName(QString::fromUtf8("frmLay_Acelerador"));
        valorAcelerador_lbl = new QLabel(grp_Acelerador);
        valorAcelerador_lbl->setObjectName(QString::fromUtf8("valorAcelerador_lbl"));

        frmLay_Acelerador->setWidget(0, QFormLayout::LabelRole, valorAcelerador_lbl);

        aceleradorPos_lcd = new QLCDNumber(grp_Acelerador);
        aceleradorPos_lcd->setObjectName(QString::fromUtf8("aceleradorPos_lcd"));
        sizePolicy.setHeightForWidth(aceleradorPos_lcd->sizePolicy().hasHeightForWidth());
        aceleradorPos_lcd->setSizePolicy(sizePolicy);
        aceleradorPos_lcd->setMinimumSize(QSize(55, 40));
        aceleradorPos_lcd->setFont(font1);

        frmLay_Acelerador->setWidget(0, QFormLayout::FieldRole, aceleradorPos_lcd);

        label_3 = new QLabel(grp_Acelerador);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        frmLay_Acelerador->setWidget(1, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(grp_Acelerador);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        frmLay_Acelerador->setWidget(3, QFormLayout::LabelRole, label_4);

        aceleradorDes_lcd = new QLCDNumber(grp_Acelerador);
        aceleradorDes_lcd->setObjectName(QString::fromUtf8("aceleradorDes_lcd"));
        sizePolicy.setHeightForWidth(aceleradorDes_lcd->sizePolicy().hasHeightForWidth());
        aceleradorDes_lcd->setSizePolicy(sizePolicy);
        aceleradorDes_lcd->setMinimumSize(QSize(0, 30));
        aceleradorDes_lcd->setFont(font2);

        frmLay_Acelerador->setWidget(1, QFormLayout::FieldRole, aceleradorDes_lcd);

        aceleradorControl_lcd = new QLCDNumber(grp_Acelerador);
        aceleradorControl_lcd->setObjectName(QString::fromUtf8("aceleradorControl_lcd"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(aceleradorControl_lcd->sizePolicy().hasHeightForWidth());
        aceleradorControl_lcd->setSizePolicy(sizePolicy4);
        aceleradorControl_lcd->setMinimumSize(QSize(0, 30));
        aceleradorControl_lcd->setFont(font2);

        frmLay_Acelerador->setWidget(3, QFormLayout::FieldRole, aceleradorControl_lcd);

        label_5 = new QLabel(grp_Acelerador);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        frmLay_Acelerador->setWidget(2, QFormLayout::LabelRole, label_5);

        Acelerador_lcdError = new QLCDNumber(grp_Acelerador);
        Acelerador_lcdError->setObjectName(QString::fromUtf8("Acelerador_lcdError"));
        sizePolicy.setHeightForWidth(Acelerador_lcdError->sizePolicy().hasHeightForWidth());
        Acelerador_lcdError->setSizePolicy(sizePolicy);
        Acelerador_lcdError->setMinimumSize(QSize(0, 30));

        frmLay_Acelerador->setWidget(2, QFormLayout::FieldRole, Acelerador_lcdError);


        verticalLayout_4->addLayout(frmLay_Acelerador);

        AceleradorControl_Slider = new QSlider(grp_Acelerador);
        AceleradorControl_Slider->setObjectName(QString::fromUtf8("AceleradorControl_Slider"));
        AceleradorControl_Slider->setMinimum(-3200);
        AceleradorControl_Slider->setMaximum(3200);
        AceleradorControl_Slider->setSingleStep(100);
        AceleradorControl_Slider->setPageStep(800);
        AceleradorControl_Slider->setOrientation(Qt::Horizontal);
        AceleradorControl_Slider->setTickPosition(QSlider::TicksAbove);

        verticalLayout_4->addWidget(AceleradorControl_Slider);


        horizontalLayout->addWidget(grp_Acelerador);

        grp_Freno = new QGroupBox(valores_y_Conexion_Widget);
        grp_Freno->setObjectName(QString::fromUtf8("grp_Freno"));
        sizePolicy1.setHeightForWidth(grp_Freno->sizePolicy().hasHeightForWidth());
        grp_Freno->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(grp_Freno);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frmLay_Freno = new QFormLayout();
        frmLay_Freno->setSpacing(6);
        frmLay_Freno->setObjectName(QString::fromUtf8("frmLay_Freno"));
        valorFreno_lbl = new QLabel(grp_Freno);
        valorFreno_lbl->setObjectName(QString::fromUtf8("valorFreno_lbl"));
        valorFreno_lbl->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(0, QFormLayout::LabelRole, valorFreno_lbl);

        frenoPos_lcd = new QLCDNumber(grp_Freno);
        frenoPos_lcd->setObjectName(QString::fromUtf8("frenoPos_lcd"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(frenoPos_lcd->sizePolicy().hasHeightForWidth());
        frenoPos_lcd->setSizePolicy(sizePolicy5);
        frenoPos_lcd->setMinimumSize(QSize(55, 40));
        frenoPos_lcd->setFont(font1);

        frmLay_Freno->setWidget(0, QFormLayout::FieldRole, frenoPos_lcd);

        label = new QLabel(grp_Freno);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(1, QFormLayout::LabelRole, label);

        frenoDes_lcd = new QLCDNumber(grp_Freno);
        frenoDes_lcd->setObjectName(QString::fromUtf8("frenoDes_lcd"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(frenoDes_lcd->sizePolicy().hasHeightForWidth());
        frenoDes_lcd->setSizePolicy(sizePolicy6);
        frenoDes_lcd->setMinimumSize(QSize(0, 30));
        frenoDes_lcd->setFont(font1);

        frmLay_Freno->setWidget(1, QFormLayout::FieldRole, frenoDes_lcd);

        Freno_lcdError = new QLCDNumber(grp_Freno);
        Freno_lcdError->setObjectName(QString::fromUtf8("Freno_lcdError"));
        Freno_lcdError->setMinimumSize(QSize(0, 30));

        frmLay_Freno->setWidget(2, QFormLayout::FieldRole, Freno_lcdError);

        Freno_lblError = new QLabel(grp_Freno);
        Freno_lblError->setObjectName(QString::fromUtf8("Freno_lblError"));

        frmLay_Freno->setWidget(2, QFormLayout::LabelRole, Freno_lblError);

        frenoControl_lcd = new QLCDNumber(grp_Freno);
        frenoControl_lcd->setObjectName(QString::fromUtf8("frenoControl_lcd"));
        frenoControl_lcd->setEnabled(true);
        sizePolicy6.setHeightForWidth(frenoControl_lcd->sizePolicy().hasHeightForWidth());
        frenoControl_lcd->setSizePolicy(sizePolicy6);
        frenoControl_lcd->setMinimumSize(QSize(30, 30));
        frenoControl_lcd->setFont(font1);
        frenoControl_lcd->setSmallDecimalPoint(false);
        frenoControl_lcd->setDigitCount(5);

        frmLay_Freno->setWidget(3, QFormLayout::FieldRole, frenoControl_lcd);

        label_2 = new QLabel(grp_Freno);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(3, QFormLayout::LabelRole, label_2);


        verticalLayout_2->addLayout(frmLay_Freno);

        FrenoControl_Slider = new QSlider(grp_Freno);
        FrenoControl_Slider->setObjectName(QString::fromUtf8("FrenoControl_Slider"));
        FrenoControl_Slider->setMinimum(-3200);
        FrenoControl_Slider->setMaximum(3200);
        FrenoControl_Slider->setSingleStep(100);
        FrenoControl_Slider->setPageStep(800);
        FrenoControl_Slider->setOrientation(Qt::Horizontal);
        FrenoControl_Slider->setTickPosition(QSlider::TicksAbove);

        verticalLayout_2->addWidget(FrenoControl_Slider);


        horizontalLayout->addWidget(grp_Freno);

        grp_Botones = new QGroupBox(valores_y_Conexion_Widget);
        grp_Botones->setObjectName(QString::fromUtf8("grp_Botones"));
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(grp_Botones->sizePolicy().hasHeightForWidth());
        grp_Botones->setSizePolicy(sizePolicy7);
        grp_Botones->setMaximumSize(QSize(16777215, 240));
        verticalLayout_9 = new QVBoxLayout(grp_Botones);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        FixFreno_chk = new QCheckBox(grp_Botones);
        FixFreno_chk->setObjectName(QString::fromUtf8("FixFreno_chk"));
        sizePolicy2.setHeightForWidth(FixFreno_chk->sizePolicy().hasHeightForWidth());
        FixFreno_chk->setSizePolicy(sizePolicy2);
        FixFreno_chk->setMinimumSize(QSize(20, 0));

        verticalLayout_8->addWidget(FixFreno_chk);

        PalUp_chk = new QCheckBox(grp_Botones);
        PalUp_chk->setObjectName(QString::fromUtf8("PalUp_chk"));
        sizePolicy2.setHeightForWidth(PalUp_chk->sizePolicy().hasHeightForWidth());
        PalUp_chk->setSizePolicy(sizePolicy2);
        PalUp_chk->setMinimumSize(QSize(20, 0));

        verticalLayout_8->addWidget(PalUp_chk);

        PalDown_chk = new QCheckBox(grp_Botones);
        PalDown_chk->setObjectName(QString::fromUtf8("PalDown_chk"));
        sizePolicy2.setHeightForWidth(PalDown_chk->sizePolicy().hasHeightForWidth());
        PalDown_chk->setSizePolicy(sizePolicy2);
        PalDown_chk->setMinimumSize(QSize(20, 0));

        verticalLayout_8->addWidget(PalDown_chk);

        RoadMode_chk = new QCheckBox(grp_Botones);
        RoadMode_chk->setObjectName(QString::fromUtf8("RoadMode_chk"));
        sizePolicy2.setHeightForWidth(RoadMode_chk->sizePolicy().hasHeightForWidth());
        RoadMode_chk->setSizePolicy(sizePolicy2);
        RoadMode_chk->setMinimumSize(QSize(20, 0));

        verticalLayout_8->addWidget(RoadMode_chk);


        verticalLayout_9->addLayout(verticalLayout_8);


        horizontalLayout->addWidget(grp_Botones);

        grp_LEDs = new QGroupBox(valores_y_Conexion_Widget);
        grp_LEDs->setObjectName(QString::fromUtf8("grp_LEDs"));
        sizePolicy.setHeightForWidth(grp_LEDs->sizePolicy().hasHeightForWidth());
        grp_LEDs->setSizePolicy(sizePolicy);
        grp_LEDs->setMaximumSize(QSize(16777215, 240));
        verticalLayout_13 = new QVBoxLayout(grp_LEDs);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        chk_LED_Joy_X_Desc = new QCheckBox(grp_LEDs);
        chk_LED_Joy_X_Desc->setObjectName(QString::fromUtf8("chk_LED_Joy_X_Desc"));
        sizePolicy1.setHeightForWidth(chk_LED_Joy_X_Desc->sizePolicy().hasHeightForWidth());
        chk_LED_Joy_X_Desc->setSizePolicy(sizePolicy1);
        chk_LED_Joy_X_Desc->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(chk_LED_Joy_X_Desc, 2, 0, 1, 1);

        chk_LED_Joy_Y_Desc = new QCheckBox(grp_LEDs);
        chk_LED_Joy_Y_Desc->setObjectName(QString::fromUtf8("chk_LED_Joy_Y_Desc"));
        sizePolicy1.setHeightForWidth(chk_LED_Joy_Y_Desc->sizePolicy().hasHeightForWidth());
        chk_LED_Joy_Y_Desc->setSizePolicy(sizePolicy1);
        chk_LED_Joy_Y_Desc->setMinimumSize(QSize(40, 0));

        gridLayout->addWidget(chk_LED_Joy_Y_Desc, 1, 0, 1, 1);

        chk_LED_Joy_X_OutR = new QCheckBox(grp_LEDs);
        chk_LED_Joy_X_OutR->setObjectName(QString::fromUtf8("chk_LED_Joy_X_OutR"));
        QSizePolicy sizePolicy8(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(chk_LED_Joy_X_OutR->sizePolicy().hasHeightForWidth());
        chk_LED_Joy_X_OutR->setSizePolicy(sizePolicy8);
        chk_LED_Joy_X_OutR->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(chk_LED_Joy_X_OutR, 2, 1, 1, 1);

        chk_LED_Freno_Desc = new QCheckBox(grp_LEDs);
        chk_LED_Freno_Desc->setObjectName(QString::fromUtf8("chk_LED_Freno_Desc"));
        sizePolicy1.setHeightForWidth(chk_LED_Freno_Desc->sizePolicy().hasHeightForWidth());
        chk_LED_Freno_Desc->setSizePolicy(sizePolicy1);
        chk_LED_Freno_Desc->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(chk_LED_Freno_Desc, 4, 0, 1, 1);

        chk_LED_Freno_OutR = new QCheckBox(grp_LEDs);
        chk_LED_Freno_OutR->setObjectName(QString::fromUtf8("chk_LED_Freno_OutR"));
        sizePolicy8.setHeightForWidth(chk_LED_Freno_OutR->sizePolicy().hasHeightForWidth());
        chk_LED_Freno_OutR->setSizePolicy(sizePolicy8);
        chk_LED_Freno_OutR->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(chk_LED_Freno_OutR, 4, 1, 1, 1);

        chk_LED_Acel_Desc = new QCheckBox(grp_LEDs);
        chk_LED_Acel_Desc->setObjectName(QString::fromUtf8("chk_LED_Acel_Desc"));
        sizePolicy1.setHeightForWidth(chk_LED_Acel_Desc->sizePolicy().hasHeightForWidth());
        chk_LED_Acel_Desc->setSizePolicy(sizePolicy1);
        chk_LED_Acel_Desc->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(chk_LED_Acel_Desc, 5, 0, 1, 1);

        chk_LED_Joy_Y_OutR = new QCheckBox(grp_LEDs);
        chk_LED_Joy_Y_OutR->setObjectName(QString::fromUtf8("chk_LED_Joy_Y_OutR"));
        sizePolicy8.setHeightForWidth(chk_LED_Joy_Y_OutR->sizePolicy().hasHeightForWidth());
        chk_LED_Joy_Y_OutR->setSizePolicy(sizePolicy8);
        chk_LED_Joy_Y_OutR->setMinimumSize(QSize(40, 0));

        gridLayout->addWidget(chk_LED_Joy_Y_OutR, 1, 1, 1, 1);

        chk_LED_Acel_OutR = new QCheckBox(grp_LEDs);
        chk_LED_Acel_OutR->setObjectName(QString::fromUtf8("chk_LED_Acel_OutR"));
        sizePolicy8.setHeightForWidth(chk_LED_Acel_OutR->sizePolicy().hasHeightForWidth());
        chk_LED_Acel_OutR->setSizePolicy(sizePolicy8);
        chk_LED_Acel_OutR->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(chk_LED_Acel_OutR, 5, 1, 1, 1);

        lblLEDsError_Desc = new QLabel(grp_LEDs);
        lblLEDsError_Desc->setObjectName(QString::fromUtf8("lblLEDsError_Desc"));
        sizePolicy.setHeightForWidth(lblLEDsError_Desc->sizePolicy().hasHeightForWidth());
        lblLEDsError_Desc->setSizePolicy(sizePolicy);
        lblLEDsError_Desc->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(lblLEDsError_Desc, 0, 0, 1, 1);

        lblLEDsError_OutRange = new QLabel(grp_LEDs);
        lblLEDsError_OutRange->setObjectName(QString::fromUtf8("lblLEDsError_OutRange"));
        sizePolicy8.setHeightForWidth(lblLEDsError_OutRange->sizePolicy().hasHeightForWidth());
        lblLEDsError_OutRange->setSizePolicy(sizePolicy8);
        lblLEDsError_OutRange->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(lblLEDsError_OutRange, 0, 1, 1, 1);


        verticalLayout_13->addLayout(gridLayout);


        horizontalLayout->addWidget(grp_LEDs);


        verticalLayout_7->addLayout(horizontalLayout);


        Valores_Widget->addLayout(verticalLayout_7);

        ConexionConfigForm_Widget = new QWidget(valores_y_Conexion_Widget);
        ConexionConfigForm_Widget->setObjectName(QString::fromUtf8("ConexionConfigForm_Widget"));
        sizePolicy.setHeightForWidth(ConexionConfigForm_Widget->sizePolicy().hasHeightForWidth());
        ConexionConfigForm_Widget->setSizePolicy(sizePolicy);
        verticalLayout_12 = new QVBoxLayout(ConexionConfigForm_Widget);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        lblEstadoSistema = new QLabel(ConexionConfigForm_Widget);
        lblEstadoSistema->setObjectName(QString::fromUtf8("lblEstadoSistema"));
        QFont font3;
        font3.setPointSize(13);
        lblEstadoSistema->setFont(font3);

        horizontalLayout_6->addWidget(lblEstadoSistema);

        estadoSistema_lbl = new QLabel(ConexionConfigForm_Widget);
        estadoSistema_lbl->setObjectName(QString::fromUtf8("estadoSistema_lbl"));
        estadoSistema_lbl->setMinimumSize(QSize(0, 50));
        QFont font4;
        font4.setPointSize(16);
        estadoSistema_lbl->setFont(font4);

        horizontalLayout_6->addWidget(estadoSistema_lbl);


        verticalLayout_12->addLayout(horizontalLayout_6);

        erroresSalida_txt = new QPlainTextEdit(ConexionConfigForm_Widget);
        erroresSalida_txt->setObjectName(QString::fromUtf8("erroresSalida_txt"));
        QSizePolicy sizePolicy9(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(erroresSalida_txt->sizePolicy().hasHeightForWidth());
        erroresSalida_txt->setSizePolicy(sizePolicy9);
        erroresSalida_txt->setMinimumSize(QSize(265, 0));
        erroresSalida_txt->setBaseSize(QSize(300, 0));

        verticalLayout_12->addWidget(erroresSalida_txt);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnParoEmergencia = new QPushButton(ConexionConfigForm_Widget);
        btnParoEmergencia->setObjectName(QString::fromUtf8("btnParoEmergencia"));
        sizePolicy.setHeightForWidth(btnParoEmergencia->sizePolicy().hasHeightForWidth());
        btnParoEmergencia->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(btnParoEmergencia);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        btnConectar = new QPushButton(ConexionConfigForm_Widget);
        btnConectar->setObjectName(QString::fromUtf8("btnConectar"));
        btnConectar->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnConectar->setIcon(icon);

        verticalLayout_3->addWidget(btnConectar);

        btnDesconectar = new QPushButton(ConexionConfigForm_Widget);
        btnDesconectar->setObjectName(QString::fromUtf8("btnDesconectar"));
        btnDesconectar->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDesconectar->setIcon(icon1);

        verticalLayout_3->addWidget(btnDesconectar);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout_12->addLayout(horizontalLayout_3);


        Valores_Widget->addWidget(ConexionConfigForm_Widget);


        verticalLayout->addWidget(valores_y_Conexion_Widget);

        SalidaConsola_Widget = new QWidget(centralWidget);
        SalidaConsola_Widget->setObjectName(QString::fromUtf8("SalidaConsola_Widget"));
        sizePolicy.setHeightForWidth(SalidaConsola_Widget->sizePolicy().hasHeightForWidth());
        SalidaConsola_Widget->setSizePolicy(sizePolicy);
        horizontalLayout_5 = new QHBoxLayout(SalidaConsola_Widget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        InfoSalida_txt = new QPlainTextEdit(SalidaConsola_Widget);
        InfoSalida_txt->setObjectName(QString::fromUtf8("InfoSalida_txt"));
        InfoSalida_txt->setEnabled(false);
        QSizePolicy sizePolicy10(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(InfoSalida_txt->sizePolicy().hasHeightForWidth());
        InfoSalida_txt->setSizePolicy(sizePolicy10);
        InfoSalida_txt->setMinimumSize(QSize(0, 0));

        horizontalLayout_5->addWidget(InfoSalida_txt);


        verticalLayout->addWidget(SalidaConsola_Widget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1073, 22));
        sizePolicy5.setHeightForWidth(menuBar->sizePolicy().hasHeightForWidth());
        menuBar->setSizePolicy(sizePolicy5);
        menuConfiguraci_n = new QMenu(menuBar);
        menuConfiguraci_n->setObjectName(QString::fromUtf8("menuConfiguraci_n"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuConfiguraci_n->menuAction());
        menuConfiguraci_n->addAction(actionConfigurar);
        menuConfiguraci_n->addAction(actionBuscar_puertos);

        retranslateUi(MainWindow);

        cmbBaudRate->setCurrentIndex(-1);
        cmbSerialPortSelector->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Monitor Serial Isiukak", nullptr));
        actionConfigurar->setText(QApplication::translate("MainWindow", "Configurar", nullptr));
        actionBuscar_puertos->setText(QApplication::translate("MainWindow", "Buscar puertos", nullptr));
        lblDescripcion->setText(QApplication::translate("MainWindow", "Descripci\303\263n:", nullptr));
        cmbSerialPortSelector->setItemText(0, QApplication::translate("MainWindow", "/dev/ttyUSB0", nullptr));
        cmbSerialPortSelector->setItemText(1, QApplication::translate("MainWindow", "/dev/ttyUSB1", nullptr));
        cmbSerialPortSelector->setItemText(2, QApplication::translate("MainWindow", "/dev/ttyUSB2", nullptr));
        cmbSerialPortSelector->setItemText(3, QApplication::translate("MainWindow", "/dev/ttyACM0", nullptr));
        cmbSerialPortSelector->setItemText(4, QApplication::translate("MainWindow", "/dev/ttyACM1", nullptr));

        grp_Joystick->setTitle(QApplication::translate("MainWindow", "Joystick", nullptr));
        joystick_X_lbl->setText(QApplication::translate("MainWindow", "J_ X:", nullptr));
        joystick_Y_lbl->setText(QApplication::translate("MainWindow", "J_Y:", nullptr));
        grp_Volante->setTitle(QApplication::translate("MainWindow", "Volante", nullptr));
        valorVolante_lbl->setText(QApplication::translate("MainWindow", "Ctrl:", nullptr));
        grp_Acelerador->setTitle(QApplication::translate("MainWindow", "Acelerador", nullptr));
        valorAcelerador_lbl->setText(QApplication::translate("MainWindow", "Pos:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Des:", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Ctrl:", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Error", nullptr));
        grp_Freno->setTitle(QApplication::translate("MainWindow", "Freno", nullptr));
        valorFreno_lbl->setText(QApplication::translate("MainWindow", "Pos:", nullptr));
        label->setText(QApplication::translate("MainWindow", "Des:", nullptr));
        Freno_lblError->setText(QApplication::translate("MainWindow", "Error", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Ctrl", nullptr));
        grp_Botones->setTitle(QApplication::translate("MainWindow", "Botones", nullptr));
        FixFreno_chk->setText(QApplication::translate("MainWindow", "Fix Freno", nullptr));
        PalUp_chk->setText(QApplication::translate("MainWindow", "Pal Up", nullptr));
        PalDown_chk->setText(QApplication::translate("MainWindow", "Pal Down", nullptr));
        RoadMode_chk->setText(QApplication::translate("MainWindow", "Modo Road", nullptr));
        grp_LEDs->setTitle(QApplication::translate("MainWindow", "LEDs Error", nullptr));
        chk_LED_Joy_X_Desc->setText(QApplication::translate("MainWindow", "JX_Desc", nullptr));
        chk_LED_Joy_Y_Desc->setText(QApplication::translate("MainWindow", "JY_Desc", nullptr));
        chk_LED_Joy_X_OutR->setText(QApplication::translate("MainWindow", "JX_OutR", nullptr));
        chk_LED_Freno_Desc->setText(QApplication::translate("MainWindow", "Freno_Desc", nullptr));
        chk_LED_Freno_OutR->setText(QApplication::translate("MainWindow", "Freno_OutR", nullptr));
        chk_LED_Acel_Desc->setText(QApplication::translate("MainWindow", "Acel_Desc", nullptr));
        chk_LED_Joy_Y_OutR->setText(QApplication::translate("MainWindow", "JY_OutR", nullptr));
        chk_LED_Acel_OutR->setText(QApplication::translate("MainWindow", "Acel_OutR", nullptr));
        lblLEDsError_Desc->setText(QApplication::translate("MainWindow", "Desc", nullptr));
        lblLEDsError_OutRange->setText(QApplication::translate("MainWindow", "OutR", nullptr));
        lblEstadoSistema->setText(QApplication::translate("MainWindow", "Estado: ", nullptr));
        estadoSistema_lbl->setText(QApplication::translate("MainWindow", "E0: OK", nullptr));
        erroresSalida_txt->setPlainText(QString());
        btnParoEmergencia->setText(QApplication::translate("MainWindow", "Paro de emergencia", nullptr));
        btnConectar->setText(QString());
        btnDesconectar->setText(QString());
        InfoSalida_txt->setPlainText(QString());
        menuConfiguraci_n->setTitle(QApplication::translate("MainWindow", "Configuraci\303\263n", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

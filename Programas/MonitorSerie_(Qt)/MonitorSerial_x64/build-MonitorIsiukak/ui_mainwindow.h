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
#include <QtWidgets/QSpacerItem>
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
    QHBoxLayout *horizontalLayout;
    QGroupBox *grp_Joystick;
    QVBoxLayout *verticalLayout_6;
    QFormLayout *formLayout_2;
    QLabel *joystick_X_lbl;
    QLCDNumber *joystick_X_lcd;
    QLabel *joystick_Y_lbl;
    QLCDNumber *joystick_Y_lcd;
    QVBoxLayout *verticalLayout_10;
    QSlider *verticalSlider;
    QSlider *horizontalSlider;
    QGroupBox *grp_Volante;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_11;
    QFormLayout *formLayout;
    QLabel *valorVolante_lbl;
    QLCDNumber *volante_lcd;
    QDial *dial;
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
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *FixFreno_chk;
    QCheckBox *PalUp_chk;
    QCheckBox *PalDown_chk;
    QCheckBox *RoadMode_chk;
    QSpacerItem *valoresYConexion_Spacer;
    QWidget *ConexionConfigForm_Widget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *Conectar_HLay;
    QPushButton *btnConectar;
    QPushButton *btnDesconectar;
    QLabel *lblDescripcion;
    QComboBox *cmbBaudRate;
    QComboBox *cmbSerialPortSelector;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnParoEmergencia;
    QWidget *SalidaConsola_Widget;
    QHBoxLayout *horizontalLayout_5;
    QPlainTextEdit *InfoSalida_txt;
    QPlainTextEdit *erroresSalida_txt;
    QMenuBar *menuBar;
    QMenu *menuConfiguraci_n;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1180, 552);
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
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(valores_y_Conexion_Widget->sizePolicy().hasHeightForWidth());
        valores_y_Conexion_Widget->setSizePolicy(sizePolicy);
        valores_y_Conexion_Widget->setMinimumSize(QSize(0, 0));
        Valores_Widget = new QHBoxLayout(valores_y_Conexion_Widget);
        Valores_Widget->setSpacing(6);
        Valores_Widget->setContentsMargins(11, 11, 11, 11);
        Valores_Widget->setObjectName(QString::fromUtf8("Valores_Widget"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        grp_Joystick = new QGroupBox(valores_y_Conexion_Widget);
        grp_Joystick->setObjectName(QString::fromUtf8("grp_Joystick"));
        verticalLayout_6 = new QVBoxLayout(grp_Joystick);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        joystick_X_lbl = new QLabel(grp_Joystick);
        joystick_X_lbl->setObjectName(QString::fromUtf8("joystick_X_lbl"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(joystick_X_lbl->sizePolicy().hasHeightForWidth());
        joystick_X_lbl->setSizePolicy(sizePolicy1);
        joystick_X_lbl->setMinimumSize(QSize(10, 50));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, joystick_X_lbl);

        joystick_X_lcd = new QLCDNumber(grp_Joystick);
        joystick_X_lcd->setObjectName(QString::fromUtf8("joystick_X_lcd"));
        joystick_X_lcd->setEnabled(true);
        sizePolicy1.setHeightForWidth(joystick_X_lcd->sizePolicy().hasHeightForWidth());
        joystick_X_lcd->setSizePolicy(sizePolicy1);
        joystick_X_lcd->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        joystick_X_lcd->setFont(font);
        joystick_X_lcd->setDigitCount(4);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, joystick_X_lcd);

        joystick_Y_lbl = new QLabel(grp_Joystick);
        joystick_Y_lbl->setObjectName(QString::fromUtf8("joystick_Y_lbl"));
        sizePolicy1.setHeightForWidth(joystick_Y_lbl->sizePolicy().hasHeightForWidth());
        joystick_Y_lbl->setSizePolicy(sizePolicy1);
        joystick_Y_lbl->setMinimumSize(QSize(10, 50));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, joystick_Y_lbl);

        joystick_Y_lcd = new QLCDNumber(grp_Joystick);
        joystick_Y_lcd->setObjectName(QString::fromUtf8("joystick_Y_lcd"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(joystick_Y_lcd->sizePolicy().hasHeightForWidth());
        joystick_Y_lcd->setSizePolicy(sizePolicy2);
        joystick_Y_lcd->setMinimumSize(QSize(0, 50));
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
        verticalSlider = new QSlider(grp_Joystick);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setMinimumSize(QSize(0, 60));
        verticalSlider->setMinimum(370);
        verticalSlider->setMaximum(640);
        verticalSlider->setValue(512);
        verticalSlider->setOrientation(Qt::Vertical);

        verticalLayout_10->addWidget(verticalSlider);

        horizontalSlider = new QSlider(grp_Joystick);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(374);
        horizontalSlider->setMaximum(640);
        horizontalSlider->setValue(512);
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_10->addWidget(horizontalSlider);


        verticalLayout_6->addLayout(verticalLayout_10);


        horizontalLayout->addWidget(grp_Joystick);

        grp_Volante = new QGroupBox(valores_y_Conexion_Widget);
        grp_Volante->setObjectName(QString::fromUtf8("grp_Volante"));
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

        formLayout->setWidget(0, QFormLayout::LabelRole, valorVolante_lbl);

        volante_lcd = new QLCDNumber(grp_Volante);
        volante_lcd->setObjectName(QString::fromUtf8("volante_lcd"));
        sizePolicy1.setHeightForWidth(volante_lcd->sizePolicy().hasHeightForWidth());
        volante_lcd->setSizePolicy(sizePolicy1);
        volante_lcd->setMinimumSize(QSize(0, 30));
        QFont font2;
        font2.setPointSize(14);
        volante_lcd->setFont(font2);

        formLayout->setWidget(0, QFormLayout::FieldRole, volante_lcd);


        verticalLayout_11->addLayout(formLayout);


        verticalLayout_5->addLayout(verticalLayout_11);

        dial = new QDial(grp_Volante);
        dial->setObjectName(QString::fromUtf8("dial"));
        dial->setAutoFillBackground(false);
        dial->setMinimum(-3200);
        dial->setMaximum(3200);
        dial->setSingleStep(100);
        dial->setPageStep(400);
        dial->setInvertedAppearance(false);

        verticalLayout_5->addWidget(dial);

        horizontalSlider_2 = new QSlider(grp_Volante);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
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
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(aceleradorPos_lcd->sizePolicy().hasHeightForWidth());
        aceleradorPos_lcd->setSizePolicy(sizePolicy3);
        aceleradorPos_lcd->setMinimumSize(QSize(0, 30));
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
        sizePolicy2.setHeightForWidth(aceleradorDes_lcd->sizePolicy().hasHeightForWidth());
        aceleradorDes_lcd->setSizePolicy(sizePolicy2);
        aceleradorDes_lcd->setMinimumSize(QSize(0, 30));
        aceleradorDes_lcd->setFont(font2);

        frmLay_Acelerador->setWidget(1, QFormLayout::FieldRole, aceleradorDes_lcd);

        aceleradorControl_lcd = new QLCDNumber(grp_Acelerador);
        aceleradorControl_lcd->setObjectName(QString::fromUtf8("aceleradorControl_lcd"));
        sizePolicy3.setHeightForWidth(aceleradorControl_lcd->sizePolicy().hasHeightForWidth());
        aceleradorControl_lcd->setSizePolicy(sizePolicy3);
        aceleradorControl_lcd->setMinimumSize(QSize(0, 30));
        aceleradorControl_lcd->setFont(font2);

        frmLay_Acelerador->setWidget(3, QFormLayout::FieldRole, aceleradorControl_lcd);

        label_5 = new QLabel(grp_Acelerador);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        frmLay_Acelerador->setWidget(2, QFormLayout::LabelRole, label_5);

        Acelerador_lcdError = new QLCDNumber(grp_Acelerador);
        Acelerador_lcdError->setObjectName(QString::fromUtf8("Acelerador_lcdError"));
        sizePolicy2.setHeightForWidth(Acelerador_lcdError->sizePolicy().hasHeightForWidth());
        Acelerador_lcdError->setSizePolicy(sizePolicy2);
        Acelerador_lcdError->setMinimumSize(QSize(0, 30));

        frmLay_Acelerador->setWidget(2, QFormLayout::FieldRole, Acelerador_lcdError);


        verticalLayout_4->addLayout(frmLay_Acelerador);

        AceleradorControl_Slider = new QSlider(grp_Acelerador);
        AceleradorControl_Slider->setObjectName(QString::fromUtf8("AceleradorControl_Slider"));
        AceleradorControl_Slider->setMinimum(-3200);
        AceleradorControl_Slider->setMaximum(3200);
        AceleradorControl_Slider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(AceleradorControl_Slider);


        horizontalLayout->addWidget(grp_Acelerador);

        grp_Freno = new QGroupBox(valores_y_Conexion_Widget);
        grp_Freno->setObjectName(QString::fromUtf8("grp_Freno"));
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
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(frenoPos_lcd->sizePolicy().hasHeightForWidth());
        frenoPos_lcd->setSizePolicy(sizePolicy4);
        frenoPos_lcd->setMinimumSize(QSize(0, 30));
        frenoPos_lcd->setFont(font1);

        frmLay_Freno->setWidget(0, QFormLayout::FieldRole, frenoPos_lcd);

        label = new QLabel(grp_Freno);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(1, QFormLayout::LabelRole, label);

        frenoDes_lcd = new QLCDNumber(grp_Freno);
        frenoDes_lcd->setObjectName(QString::fromUtf8("frenoDes_lcd"));
        sizePolicy1.setHeightForWidth(frenoDes_lcd->sizePolicy().hasHeightForWidth());
        frenoDes_lcd->setSizePolicy(sizePolicy1);
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
        sizePolicy1.setHeightForWidth(frenoControl_lcd->sizePolicy().hasHeightForWidth());
        frenoControl_lcd->setSizePolicy(sizePolicy1);
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
        FrenoControl_Slider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(FrenoControl_Slider);


        horizontalLayout->addWidget(grp_Freno);

        groupBox = new QGroupBox(valores_y_Conexion_Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_9 = new QVBoxLayout(groupBox);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        FixFreno_chk = new QCheckBox(groupBox);
        FixFreno_chk->setObjectName(QString::fromUtf8("FixFreno_chk"));

        verticalLayout_8->addWidget(FixFreno_chk);

        PalUp_chk = new QCheckBox(groupBox);
        PalUp_chk->setObjectName(QString::fromUtf8("PalUp_chk"));

        verticalLayout_8->addWidget(PalUp_chk);

        PalDown_chk = new QCheckBox(groupBox);
        PalDown_chk->setObjectName(QString::fromUtf8("PalDown_chk"));

        verticalLayout_8->addWidget(PalDown_chk);

        RoadMode_chk = new QCheckBox(groupBox);
        RoadMode_chk->setObjectName(QString::fromUtf8("RoadMode_chk"));

        verticalLayout_8->addWidget(RoadMode_chk);


        verticalLayout_9->addLayout(verticalLayout_8);


        horizontalLayout->addWidget(groupBox);


        verticalLayout_7->addLayout(horizontalLayout);


        Valores_Widget->addLayout(verticalLayout_7);

        valoresYConexion_Spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Valores_Widget->addItem(valoresYConexion_Spacer);

        ConexionConfigForm_Widget = new QWidget(valores_y_Conexion_Widget);
        ConexionConfigForm_Widget->setObjectName(QString::fromUtf8("ConexionConfigForm_Widget"));
        sizePolicy4.setHeightForWidth(ConexionConfigForm_Widget->sizePolicy().hasHeightForWidth());
        ConexionConfigForm_Widget->setSizePolicy(sizePolicy4);
        verticalLayout_3 = new QVBoxLayout(ConexionConfigForm_Widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        Conectar_HLay = new QHBoxLayout();
        Conectar_HLay->setSpacing(6);
        Conectar_HLay->setObjectName(QString::fromUtf8("Conectar_HLay"));
        btnConectar = new QPushButton(ConexionConfigForm_Widget);
        btnConectar->setObjectName(QString::fromUtf8("btnConectar"));
        btnConectar->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnConectar->setIcon(icon);

        Conectar_HLay->addWidget(btnConectar);

        btnDesconectar = new QPushButton(ConexionConfigForm_Widget);
        btnDesconectar->setObjectName(QString::fromUtf8("btnDesconectar"));
        btnDesconectar->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDesconectar->setIcon(icon1);

        Conectar_HLay->addWidget(btnDesconectar);

        lblDescripcion = new QLabel(ConexionConfigForm_Widget);
        lblDescripcion->setObjectName(QString::fromUtf8("lblDescripcion"));

        Conectar_HLay->addWidget(lblDescripcion);

        cmbBaudRate = new QComboBox(ConexionConfigForm_Widget);
        cmbBaudRate->setObjectName(QString::fromUtf8("cmbBaudRate"));

        Conectar_HLay->addWidget(cmbBaudRate);

        cmbSerialPortSelector = new QComboBox(ConexionConfigForm_Widget);
        cmbSerialPortSelector->addItem(QString());
        cmbSerialPortSelector->addItem(QString());
        cmbSerialPortSelector->addItem(QString());
        cmbSerialPortSelector->addItem(QString());
        cmbSerialPortSelector->addItem(QString());
        cmbSerialPortSelector->setObjectName(QString::fromUtf8("cmbSerialPortSelector"));

        Conectar_HLay->addWidget(cmbSerialPortSelector);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Conectar_HLay->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(Conectar_HLay);

        btnParoEmergencia = new QPushButton(ConexionConfigForm_Widget);
        btnParoEmergencia->setObjectName(QString::fromUtf8("btnParoEmergencia"));
        sizePolicy2.setHeightForWidth(btnParoEmergencia->sizePolicy().hasHeightForWidth());
        btnParoEmergencia->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(btnParoEmergencia);


        Valores_Widget->addWidget(ConexionConfigForm_Widget);


        verticalLayout->addWidget(valores_y_Conexion_Widget);

        SalidaConsola_Widget = new QWidget(centralWidget);
        SalidaConsola_Widget->setObjectName(QString::fromUtf8("SalidaConsola_Widget"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(SalidaConsola_Widget->sizePolicy().hasHeightForWidth());
        SalidaConsola_Widget->setSizePolicy(sizePolicy5);
        horizontalLayout_5 = new QHBoxLayout(SalidaConsola_Widget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        InfoSalida_txt = new QPlainTextEdit(SalidaConsola_Widget);
        InfoSalida_txt->setObjectName(QString::fromUtf8("InfoSalida_txt"));

        horizontalLayout_5->addWidget(InfoSalida_txt);

        erroresSalida_txt = new QPlainTextEdit(SalidaConsola_Widget);
        erroresSalida_txt->setObjectName(QString::fromUtf8("erroresSalida_txt"));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(erroresSalida_txt->sizePolicy().hasHeightForWidth());
        erroresSalida_txt->setSizePolicy(sizePolicy6);
        erroresSalida_txt->setMinimumSize(QSize(300, 0));
        erroresSalida_txt->setBaseSize(QSize(300, 0));

        horizontalLayout_5->addWidget(erroresSalida_txt);


        verticalLayout->addWidget(SalidaConsola_Widget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1180, 22));
        menuConfiguraci_n = new QMenu(menuBar);
        menuConfiguraci_n->setObjectName(QString::fromUtf8("menuConfiguraci_n"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionConfigurar->setText(QApplication::translate("MainWindow", "Configurar", nullptr));
        actionBuscar_puertos->setText(QApplication::translate("MainWindow", "Buscar puertos", nullptr));
        grp_Joystick->setTitle(QApplication::translate("MainWindow", "Joystick", nullptr));
        joystick_X_lbl->setText(QApplication::translate("MainWindow", "J_ X:", nullptr));
        joystick_Y_lbl->setText(QApplication::translate("MainWindow", "J_Y:", nullptr));
        grp_Volante->setTitle(QApplication::translate("MainWindow", "Volante", nullptr));
        valorVolante_lbl->setText(QApplication::translate("MainWindow", "Valor:", nullptr));
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
        groupBox->setTitle(QApplication::translate("MainWindow", "Botones", nullptr));
        FixFreno_chk->setText(QApplication::translate("MainWindow", "Fix Freno", nullptr));
        PalUp_chk->setText(QApplication::translate("MainWindow", "Pal Up", nullptr));
        PalDown_chk->setText(QApplication::translate("MainWindow", "Pal Down", nullptr));
        RoadMode_chk->setText(QApplication::translate("MainWindow", "Modo Road", nullptr));
        btnConectar->setText(QString());
        btnDesconectar->setText(QString());
        lblDescripcion->setText(QApplication::translate("MainWindow", "Descripci\303\263n:", nullptr));
        cmbSerialPortSelector->setItemText(0, QApplication::translate("MainWindow", "/dev/ttyUSB0", nullptr));
        cmbSerialPortSelector->setItemText(1, QApplication::translate("MainWindow", "/dev/ttyUSB1", nullptr));
        cmbSerialPortSelector->setItemText(2, QApplication::translate("MainWindow", "/dev/ttyUSB2", nullptr));
        cmbSerialPortSelector->setItemText(3, QApplication::translate("MainWindow", "/dev/ttyACM0", nullptr));
        cmbSerialPortSelector->setItemText(4, QApplication::translate("MainWindow", "/dev/ttyACM1", nullptr));

        btnParoEmergencia->setText(QApplication::translate("MainWindow", "Paro de emergencia", nullptr));
        InfoSalida_txt->setPlainText(QString());
        erroresSalida_txt->setPlainText(QString());
        menuConfiguraci_n->setTitle(QApplication::translate("MainWindow", "Configuraci\303\263n", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

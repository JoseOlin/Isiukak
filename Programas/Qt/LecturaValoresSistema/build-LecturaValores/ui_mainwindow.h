/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
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
    QLCDNumber *joystick_Y_lcd;
    QLabel *joystick_Y_lbl;
    QGroupBox *grp_Volante;
    QVBoxLayout *verticalLayout_5;
    QFormLayout *formLayout;
    QLabel *valorVolante_lbl;
    QLCDNumber *volante_lcd;
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
    QGroupBox *grp_Freno;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *frmLay_Freno;
    QLabel *valorFreno_lbl;
    QLCDNumber *frenoPos_lcd;
    QLabel *label;
    QLabel *label_2;
    QLCDNumber *frenoDes_lcd;
    QLCDNumber *frenoControl_lcd;
    QLabel *Freno_lblError;
    QLCDNumber *Freno_lcdError;
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1046, 431);
        actionConfigurar = new QAction(MainWindow);
        actionConfigurar->setObjectName(QStringLiteral("actionConfigurar"));
        actionBuscar_puertos = new QAction(MainWindow);
        actionBuscar_puertos->setObjectName(QStringLiteral("actionBuscar_puertos"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        valores_y_Conexion_Widget = new QWidget(centralWidget);
        valores_y_Conexion_Widget->setObjectName(QStringLiteral("valores_y_Conexion_Widget"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(valores_y_Conexion_Widget->sizePolicy().hasHeightForWidth());
        valores_y_Conexion_Widget->setSizePolicy(sizePolicy);
        valores_y_Conexion_Widget->setMinimumSize(QSize(0, 0));
        Valores_Widget = new QHBoxLayout(valores_y_Conexion_Widget);
        Valores_Widget->setSpacing(6);
        Valores_Widget->setContentsMargins(11, 11, 11, 11);
        Valores_Widget->setObjectName(QStringLiteral("Valores_Widget"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        grp_Joystick = new QGroupBox(valores_y_Conexion_Widget);
        grp_Joystick->setObjectName(QStringLiteral("grp_Joystick"));
        verticalLayout_6 = new QVBoxLayout(grp_Joystick);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        joystick_X_lbl = new QLabel(grp_Joystick);
        joystick_X_lbl->setObjectName(QStringLiteral("joystick_X_lbl"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(joystick_X_lbl->sizePolicy().hasHeightForWidth());
        joystick_X_lbl->setSizePolicy(sizePolicy1);
        joystick_X_lbl->setMinimumSize(QSize(10, 0));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, joystick_X_lbl);

        joystick_X_lcd = new QLCDNumber(grp_Joystick);
        joystick_X_lcd->setObjectName(QStringLiteral("joystick_X_lcd"));
        joystick_X_lcd->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(joystick_X_lcd->sizePolicy().hasHeightForWidth());
        joystick_X_lcd->setSizePolicy(sizePolicy2);
        joystick_X_lcd->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        joystick_X_lcd->setFont(font);
        joystick_X_lcd->setDigitCount(4);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, joystick_X_lcd);

        joystick_Y_lcd = new QLCDNumber(grp_Joystick);
        joystick_Y_lcd->setObjectName(QStringLiteral("joystick_Y_lcd"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(joystick_Y_lcd->sizePolicy().hasHeightForWidth());
        joystick_Y_lcd->setSizePolicy(sizePolicy3);
        joystick_Y_lcd->setMinimumSize(QSize(0, 30));
        joystick_Y_lcd->setFont(font);
        joystick_Y_lcd->setDigitCount(4);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, joystick_Y_lcd);

        joystick_Y_lbl = new QLabel(grp_Joystick);
        joystick_Y_lbl->setObjectName(QStringLiteral("joystick_Y_lbl"));
        sizePolicy1.setHeightForWidth(joystick_Y_lbl->sizePolicy().hasHeightForWidth());
        joystick_Y_lbl->setSizePolicy(sizePolicy1);
        joystick_Y_lbl->setMinimumSize(QSize(10, 0));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, joystick_Y_lbl);


        verticalLayout_6->addLayout(formLayout_2);


        horizontalLayout->addWidget(grp_Joystick);

        grp_Volante = new QGroupBox(valores_y_Conexion_Widget);
        grp_Volante->setObjectName(QStringLiteral("grp_Volante"));
        verticalLayout_5 = new QVBoxLayout(grp_Volante);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        valorVolante_lbl = new QLabel(grp_Volante);
        valorVolante_lbl->setObjectName(QStringLiteral("valorVolante_lbl"));

        formLayout->setWidget(0, QFormLayout::LabelRole, valorVolante_lbl);

        volante_lcd = new QLCDNumber(grp_Volante);
        volante_lcd->setObjectName(QStringLiteral("volante_lcd"));
        volante_lcd->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setPointSize(14);
        volante_lcd->setFont(font1);

        formLayout->setWidget(0, QFormLayout::FieldRole, volante_lcd);


        verticalLayout_5->addLayout(formLayout);


        horizontalLayout->addWidget(grp_Volante);

        grp_Acelerador = new QGroupBox(valores_y_Conexion_Widget);
        grp_Acelerador->setObjectName(QStringLiteral("grp_Acelerador"));
        grp_Acelerador->setFlat(false);
        verticalLayout_4 = new QVBoxLayout(grp_Acelerador);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        frmLay_Acelerador = new QFormLayout();
        frmLay_Acelerador->setSpacing(6);
        frmLay_Acelerador->setObjectName(QStringLiteral("frmLay_Acelerador"));
        valorAcelerador_lbl = new QLabel(grp_Acelerador);
        valorAcelerador_lbl->setObjectName(QStringLiteral("valorAcelerador_lbl"));

        frmLay_Acelerador->setWidget(0, QFormLayout::LabelRole, valorAcelerador_lbl);

        aceleradorPos_lcd = new QLCDNumber(grp_Acelerador);
        aceleradorPos_lcd->setObjectName(QStringLiteral("aceleradorPos_lcd"));
        sizePolicy2.setHeightForWidth(aceleradorPos_lcd->sizePolicy().hasHeightForWidth());
        aceleradorPos_lcd->setSizePolicy(sizePolicy2);
        aceleradorPos_lcd->setMinimumSize(QSize(0, 30));
        aceleradorPos_lcd->setFont(font);

        frmLay_Acelerador->setWidget(0, QFormLayout::FieldRole, aceleradorPos_lcd);

        label_3 = new QLabel(grp_Acelerador);
        label_3->setObjectName(QStringLiteral("label_3"));

        frmLay_Acelerador->setWidget(1, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(grp_Acelerador);
        label_4->setObjectName(QStringLiteral("label_4"));

        frmLay_Acelerador->setWidget(3, QFormLayout::LabelRole, label_4);

        aceleradorDes_lcd = new QLCDNumber(grp_Acelerador);
        aceleradorDes_lcd->setObjectName(QStringLiteral("aceleradorDes_lcd"));
        sizePolicy3.setHeightForWidth(aceleradorDes_lcd->sizePolicy().hasHeightForWidth());
        aceleradorDes_lcd->setSizePolicy(sizePolicy3);
        aceleradorDes_lcd->setMinimumSize(QSize(0, 30));
        aceleradorDes_lcd->setFont(font1);

        frmLay_Acelerador->setWidget(1, QFormLayout::FieldRole, aceleradorDes_lcd);

        aceleradorControl_lcd = new QLCDNumber(grp_Acelerador);
        aceleradorControl_lcd->setObjectName(QStringLiteral("aceleradorControl_lcd"));
        sizePolicy2.setHeightForWidth(aceleradorControl_lcd->sizePolicy().hasHeightForWidth());
        aceleradorControl_lcd->setSizePolicy(sizePolicy2);
        aceleradorControl_lcd->setMinimumSize(QSize(0, 30));
        aceleradorControl_lcd->setFont(font1);

        frmLay_Acelerador->setWidget(3, QFormLayout::FieldRole, aceleradorControl_lcd);

        label_5 = new QLabel(grp_Acelerador);
        label_5->setObjectName(QStringLiteral("label_5"));

        frmLay_Acelerador->setWidget(2, QFormLayout::LabelRole, label_5);

        Acelerador_lcdError = new QLCDNumber(grp_Acelerador);
        Acelerador_lcdError->setObjectName(QStringLiteral("Acelerador_lcdError"));
        sizePolicy3.setHeightForWidth(Acelerador_lcdError->sizePolicy().hasHeightForWidth());
        Acelerador_lcdError->setSizePolicy(sizePolicy3);
        Acelerador_lcdError->setMinimumSize(QSize(0, 30));

        frmLay_Acelerador->setWidget(2, QFormLayout::FieldRole, Acelerador_lcdError);


        verticalLayout_4->addLayout(frmLay_Acelerador);


        horizontalLayout->addWidget(grp_Acelerador);

        grp_Freno = new QGroupBox(valores_y_Conexion_Widget);
        grp_Freno->setObjectName(QStringLiteral("grp_Freno"));
        verticalLayout_2 = new QVBoxLayout(grp_Freno);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        frmLay_Freno = new QFormLayout();
        frmLay_Freno->setSpacing(6);
        frmLay_Freno->setObjectName(QStringLiteral("frmLay_Freno"));
        valorFreno_lbl = new QLabel(grp_Freno);
        valorFreno_lbl->setObjectName(QStringLiteral("valorFreno_lbl"));
        valorFreno_lbl->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(0, QFormLayout::LabelRole, valorFreno_lbl);

        frenoPos_lcd = new QLCDNumber(grp_Freno);
        frenoPos_lcd->setObjectName(QStringLiteral("frenoPos_lcd"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(frenoPos_lcd->sizePolicy().hasHeightForWidth());
        frenoPos_lcd->setSizePolicy(sizePolicy4);
        frenoPos_lcd->setMinimumSize(QSize(0, 30));
        frenoPos_lcd->setFont(font);

        frmLay_Freno->setWidget(0, QFormLayout::FieldRole, frenoPos_lcd);

        label = new QLabel(grp_Freno);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(1, QFormLayout::LabelRole, label);

        label_2 = new QLabel(grp_Freno);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(4, QFormLayout::LabelRole, label_2);

        frenoDes_lcd = new QLCDNumber(grp_Freno);
        frenoDes_lcd->setObjectName(QStringLiteral("frenoDes_lcd"));
        sizePolicy1.setHeightForWidth(frenoDes_lcd->sizePolicy().hasHeightForWidth());
        frenoDes_lcd->setSizePolicy(sizePolicy1);
        frenoDes_lcd->setMinimumSize(QSize(0, 30));
        frenoDes_lcd->setFont(font);

        frmLay_Freno->setWidget(1, QFormLayout::FieldRole, frenoDes_lcd);

        frenoControl_lcd = new QLCDNumber(grp_Freno);
        frenoControl_lcd->setObjectName(QStringLiteral("frenoControl_lcd"));
        frenoControl_lcd->setEnabled(true);
        sizePolicy1.setHeightForWidth(frenoControl_lcd->sizePolicy().hasHeightForWidth());
        frenoControl_lcd->setSizePolicy(sizePolicy1);
        frenoControl_lcd->setMinimumSize(QSize(30, 30));
        frenoControl_lcd->setFont(font);
        frenoControl_lcd->setSmallDecimalPoint(false);
        frenoControl_lcd->setDigitCount(5);

        frmLay_Freno->setWidget(4, QFormLayout::FieldRole, frenoControl_lcd);

        Freno_lblError = new QLabel(grp_Freno);
        Freno_lblError->setObjectName(QStringLiteral("Freno_lblError"));

        frmLay_Freno->setWidget(3, QFormLayout::LabelRole, Freno_lblError);

        Freno_lcdError = new QLCDNumber(grp_Freno);
        Freno_lcdError->setObjectName(QStringLiteral("Freno_lcdError"));
        Freno_lcdError->setMinimumSize(QSize(0, 30));

        frmLay_Freno->setWidget(3, QFormLayout::FieldRole, Freno_lcdError);


        verticalLayout_2->addLayout(frmLay_Freno);


        horizontalLayout->addWidget(grp_Freno);


        verticalLayout_7->addLayout(horizontalLayout);


        Valores_Widget->addLayout(verticalLayout_7);

        valoresYConexion_Spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Valores_Widget->addItem(valoresYConexion_Spacer);

        ConexionConfigForm_Widget = new QWidget(valores_y_Conexion_Widget);
        ConexionConfigForm_Widget->setObjectName(QStringLiteral("ConexionConfigForm_Widget"));
        sizePolicy4.setHeightForWidth(ConexionConfigForm_Widget->sizePolicy().hasHeightForWidth());
        ConexionConfigForm_Widget->setSizePolicy(sizePolicy4);
        verticalLayout_3 = new QVBoxLayout(ConexionConfigForm_Widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        Conectar_HLay = new QHBoxLayout();
        Conectar_HLay->setSpacing(6);
        Conectar_HLay->setObjectName(QStringLiteral("Conectar_HLay"));
        btnConectar = new QPushButton(ConexionConfigForm_Widget);
        btnConectar->setObjectName(QStringLiteral("btnConectar"));
        btnConectar->setEnabled(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnConectar->setIcon(icon);

        Conectar_HLay->addWidget(btnConectar);

        btnDesconectar = new QPushButton(ConexionConfigForm_Widget);
        btnDesconectar->setObjectName(QStringLiteral("btnDesconectar"));
        btnDesconectar->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDesconectar->setIcon(icon1);

        Conectar_HLay->addWidget(btnDesconectar);

        lblDescripcion = new QLabel(ConexionConfigForm_Widget);
        lblDescripcion->setObjectName(QStringLiteral("lblDescripcion"));

        Conectar_HLay->addWidget(lblDescripcion);

        cmbBaudRate = new QComboBox(ConexionConfigForm_Widget);
        cmbBaudRate->setObjectName(QStringLiteral("cmbBaudRate"));

        Conectar_HLay->addWidget(cmbBaudRate);

        cmbSerialPortSelector = new QComboBox(ConexionConfigForm_Widget);
        cmbSerialPortSelector->setObjectName(QStringLiteral("cmbSerialPortSelector"));

        Conectar_HLay->addWidget(cmbSerialPortSelector);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Conectar_HLay->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(Conectar_HLay);

        btnParoEmergencia = new QPushButton(ConexionConfigForm_Widget);
        btnParoEmergencia->setObjectName(QStringLiteral("btnParoEmergencia"));
        sizePolicy3.setHeightForWidth(btnParoEmergencia->sizePolicy().hasHeightForWidth());
        btnParoEmergencia->setSizePolicy(sizePolicy3);

        verticalLayout_3->addWidget(btnParoEmergencia);


        Valores_Widget->addWidget(ConexionConfigForm_Widget);


        verticalLayout->addWidget(valores_y_Conexion_Widget);

        SalidaConsola_Widget = new QWidget(centralWidget);
        SalidaConsola_Widget->setObjectName(QStringLiteral("SalidaConsola_Widget"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(SalidaConsola_Widget->sizePolicy().hasHeightForWidth());
        SalidaConsola_Widget->setSizePolicy(sizePolicy5);
        horizontalLayout_5 = new QHBoxLayout(SalidaConsola_Widget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        InfoSalida_txt = new QPlainTextEdit(SalidaConsola_Widget);
        InfoSalida_txt->setObjectName(QStringLiteral("InfoSalida_txt"));

        horizontalLayout_5->addWidget(InfoSalida_txt);

        erroresSalida_txt = new QPlainTextEdit(SalidaConsola_Widget);
        erroresSalida_txt->setObjectName(QStringLiteral("erroresSalida_txt"));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(erroresSalida_txt->sizePolicy().hasHeightForWidth());
        erroresSalida_txt->setSizePolicy(sizePolicy6);

        horizontalLayout_5->addWidget(erroresSalida_txt);


        verticalLayout->addWidget(SalidaConsola_Widget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1046, 22));
        menuConfiguraci_n = new QMenu(menuBar);
        menuConfiguraci_n->setObjectName(QStringLiteral("menuConfiguraci_n"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionConfigurar->setText(QApplication::translate("MainWindow", "Configurar", Q_NULLPTR));
        actionBuscar_puertos->setText(QApplication::translate("MainWindow", "Buscar puertos", Q_NULLPTR));
        grp_Joystick->setTitle(QApplication::translate("MainWindow", "Joystick", Q_NULLPTR));
        joystick_X_lbl->setText(QApplication::translate("MainWindow", "J_ X:", Q_NULLPTR));
        joystick_Y_lbl->setText(QApplication::translate("MainWindow", "J_Y:", Q_NULLPTR));
        grp_Volante->setTitle(QApplication::translate("MainWindow", "Volante", Q_NULLPTR));
        valorVolante_lbl->setText(QApplication::translate("MainWindow", "Valor:", Q_NULLPTR));
        grp_Acelerador->setTitle(QApplication::translate("MainWindow", "Acelerador", Q_NULLPTR));
        valorAcelerador_lbl->setText(QApplication::translate("MainWindow", "Pos:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Des:", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Ctrl:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Error", Q_NULLPTR));
        grp_Freno->setTitle(QApplication::translate("MainWindow", "Freno", Q_NULLPTR));
        valorFreno_lbl->setText(QApplication::translate("MainWindow", "Pos:", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Des:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Ctrl", Q_NULLPTR));
        Freno_lblError->setText(QApplication::translate("MainWindow", "Error", Q_NULLPTR));
        btnConectar->setText(QString());
        btnDesconectar->setText(QString());
        lblDescripcion->setText(QApplication::translate("MainWindow", "Descripci\303\263n:", Q_NULLPTR));
        cmbSerialPortSelector->clear();
        cmbSerialPortSelector->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "/dev/ttyUSB0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "/dev/ttyUSB1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "/dev/ttyUSB2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "/dev/ttyACM0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "/dev/ttyACM1", Q_NULLPTR)
        );
        btnParoEmergencia->setText(QApplication::translate("MainWindow", "Paro de emergencia", Q_NULLPTR));
        InfoSalida_txt->setPlainText(QString());
        erroresSalida_txt->setPlainText(QString());
        menuConfiguraci_n->setTitle(QApplication::translate("MainWindow", "Configuraci\303\263n", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

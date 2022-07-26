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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
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
    QWidget *SensorsInfo_Errors_and_Conn_Widget;
    QHBoxLayout *Valores_Widget;
    QFrame *Joystick_and_Actuators_ext_hotLayout;
    QVBoxLayout *SensorsInfo_verLayout;
    QFrame *Joystick_and_Actuators_hotLayout;
    QHBoxLayout *SensorsInfo_horLayout;
    QGroupBox *grp_Joystick;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *joystick_Activado_chk;
    QCheckBox *chk_LED_Joy_Y_Desc;
    QCheckBox *chk_LED_Joy_X_Desc;
    QCheckBox *chk_LED_Joy_Y_OutR;
    QCheckBox *chk_LED_Joy_X_OutR;
    QFormLayout *formLayout_2;
    QLabel *joystick_Y_lbl;
    QLCDNumber *joystick_Y_lcd;
    QLabel *joystick_X_lbl;
    QLCDNumber *joystick_X_lcd;
    QLabel *label_34;
    QLabel *label_36;
    QLabel *Jy_Min_lbl;
    QLabel *Jy_Max_lbl;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *Jx_Min_lbl;
    QLabel *Jx_Max_lbl;
    QFrame *gridLayout_3;
    QGridLayout *gridLayout_2;
    QSlider *joystickVertical_sld;
    QSlider *joystickHorizontal_Sld;
    QGroupBox *grp_Botones;
    QVBoxLayout *verticalLayout_9;
    QFrame *frame;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *FixFreno_chk;
    QCheckBox *PalUp_chk;
    QCheckBox *PalDown_chk;
    QCheckBox *RoadMode_chk;
    QGroupBox *grp_Freno;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_5;
    QFormLayout *frmLay_Freno;
    QLabel *valorFreno_lbl;
    QLCDNumber *frenoPos_lcd;
    QLabel *label;
    QLCDNumber *frenoDes_lcd;
    QLCDNumber *Freno_lcdError;
    QLabel *Freno_lblError;
    QLCDNumber *frenoControl_lcd;
    QLabel *label_2;
    QCheckBox *Freno_Inhibido_chk;
    QLabel *label_7;
    QCheckBox *Freno_Activado_chk;
    QLabel *FrenoActivado_lbl;
    QCheckBox *chk_LED_Freno_OutR;
    QCheckBox *chk_LED_Freno_Desc;
    QSlider *FrenoControl_Slider;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_26;
    QFormLayout *formLayout_3;
    QLabel *label_29;
    QLabel *label_28;
    QLabel *brake_PosLimits_Min_lbl;
    QLabel *brake_PosLimits_Max_lbl;
    QFrame *Brake_Driver_lay_2;
    QFormLayout *Brake_Driver_lay;
    QLabel *label_8;
    QLabel *Brake_VIN_lbl;
    QLabel *label_10;
    QLabel *Brake_Temp_lbl;
    QLabel *label_12;
    QLabel *Brake_Error_lbl;
    QRadioButton *brake_ShowInfo_rBtn;
    QGroupBox *grp_Acelerador;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame1;
    QFormLayout *frmLay_Acelerador;
    QLabel *Acel_Activado_lbl;
    QCheckBox *Acel_Activado_chk;
    QLabel *Acel_Inhibido_lbl;
    QCheckBox *Acel_Inhibido_chk;
    QCheckBox *chk_LED_Acel_OutR;
    QLabel *valorAcelerador_lbl;
    QLCDNumber *aceleradorPos_lcd;
    QLabel *label_3;
    QLCDNumber *aceleradorDes_lcd;
    QLabel *label_5;
    QLCDNumber *Acelerador_lcdError;
    QLabel *label_4;
    QLCDNumber *aceleradorControl_lcd;
    QCheckBox *chk_LED_Acel_Desc;
    QSlider *AceleradorControl_Slider;
    QFrame *frame2;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_30;
    QFormLayout *formLayout_4;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *Accel_PosLimits_Max_lbl;
    QLabel *Accel_PosLimits_Min_lbl;
    QFormLayout *Accel_Driver_lay;
    QLabel *label_9;
    QLabel *Accel_Vin_lbl;
    QLabel *Accel_Temp_lbl;
    QLabel *label_14;
    QLabel *label_11;
    QLabel *Accel_Error_lbl;
    QRadioButton *accel_ShowInfo_rBtn;
    QGroupBox *grp_Volante;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *volante_Activado_chk;
    QCheckBox *volante_Inhibido_chk;
    QComboBox *VolanteModo_cmb;
    QVBoxLayout *verticalLayout_11;
    QLabel *valorVolante_lbl;
    QLCDNumber *volante_lcd;
    QDial *VolanteControl_Dial;
    QSpacerItem *verticalSpacer_2;
    QFormLayout *formLayout_5;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *Steer_Vin_lbl;
    QLabel *Steer_Temp_lbl;
    QLabel *Steer_Error_lbl;
    QRadioButton *steer_ShowInfo_rBtn;
    QWidget *grp_ShiftGear_and_SystemInfo;
    QVBoxLayout *shiftGear_and_DefaultDefines;
    QGroupBox *palanca_grp;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_14;
    QCheckBox *palanca_Activada_chk;
    QCheckBox *palanca_Inhibida_chk;
    QSpacerItem *verticalSpacer;
    QFrame *time_frame;
    QVBoxLayout *verticalLayout_7;
    QFormLayout *formLayout_6;
    QLabel *label_27;
    QLabel *T_lbl;
    QLabel *T_max_lbl;
    QLabel *label_35;
    QLabel *label_33;
    QLabel *T_min_lbl;
    QCheckBox *normalDefines_chk;
    QWidget *Edo_ConexionConfig_and_Error_vertWidget;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout;
    QLabel *logoOlin_lbl;
    QFrame *Status_horLay;
    QHBoxLayout *EstadoIsiukak_horLayout;
    QLabel *lblEstadoSistema;
    QLabel *estadoSistema_lbl;
    QFrame *driverErrorsHeaders_gridLayout_2;
    QGridLayout *driverErrorsHeaders_gridLayout;
    QLabel *label_21;
    QLabel *label_25;
    QLabel *label_24;
    QLabel *label_20;
    QLabel *label_38;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_37;
    QLabel *label_41;
    QFrame *driverErrorsValues_gridLayout_2;
    QGridLayout *driverErrorsValues_gridLayout;
    QPlainTextEdit *driversValues_txt;
    QPlainTextEdit *erroresSalida_txt;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QLabel *lblDescripcion;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *cmbBaudRate;
    QComboBox *cmbSerialPortSelector;
    QFrame *Connection_horLay;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnParoEmergencia;
    QFrame *buttonsConnection_verLay;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnConectar;
    QPushButton *btnDesconectar;
    QWidget *SalidaConsola_Widget;
    QHBoxLayout *horizontalLayout_5;
    QPlainTextEdit *InfoSalida_txt;
    QMenuBar *menuBar;
    QMenu *menuConfiguraci_n;
    QButtonGroup *driversShowInfoSelect;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1195, 753);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1024, 600));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Isotipo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionConfigurar = new QAction(MainWindow);
        actionConfigurar->setObjectName(QStringLiteral("actionConfigurar"));
        actionBuscar_puertos = new QAction(MainWindow);
        actionBuscar_puertos->setObjectName(QStringLiteral("actionBuscar_puertos"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 1, 5, 1);
        SensorsInfo_Errors_and_Conn_Widget = new QWidget(centralWidget);
        SensorsInfo_Errors_and_Conn_Widget->setObjectName(QStringLiteral("SensorsInfo_Errors_and_Conn_Widget"));
        sizePolicy.setHeightForWidth(SensorsInfo_Errors_and_Conn_Widget->sizePolicy().hasHeightForWidth());
        SensorsInfo_Errors_and_Conn_Widget->setSizePolicy(sizePolicy);
        Valores_Widget = new QHBoxLayout(SensorsInfo_Errors_and_Conn_Widget);
        Valores_Widget->setSpacing(1);
        Valores_Widget->setContentsMargins(11, 11, 11, 11);
        Valores_Widget->setObjectName(QStringLiteral("Valores_Widget"));
        Valores_Widget->setContentsMargins(3, 1, 3, 1);
        Joystick_and_Actuators_ext_hotLayout = new QFrame(SensorsInfo_Errors_and_Conn_Widget);
        Joystick_and_Actuators_ext_hotLayout->setObjectName(QStringLiteral("Joystick_and_Actuators_ext_hotLayout"));
        SensorsInfo_verLayout = new QVBoxLayout(Joystick_and_Actuators_ext_hotLayout);
        SensorsInfo_verLayout->setSpacing(0);
        SensorsInfo_verLayout->setContentsMargins(11, 11, 11, 11);
        SensorsInfo_verLayout->setObjectName(QStringLiteral("SensorsInfo_verLayout"));
        Joystick_and_Actuators_hotLayout = new QFrame(Joystick_and_Actuators_ext_hotLayout);
        Joystick_and_Actuators_hotLayout->setObjectName(QStringLiteral("Joystick_and_Actuators_hotLayout"));
        SensorsInfo_horLayout = new QHBoxLayout(Joystick_and_Actuators_hotLayout);
        SensorsInfo_horLayout->setSpacing(1);
        SensorsInfo_horLayout->setContentsMargins(11, 11, 11, 11);
        SensorsInfo_horLayout->setObjectName(QStringLiteral("SensorsInfo_horLayout"));
        grp_Joystick = new QGroupBox(Joystick_and_Actuators_hotLayout);
        grp_Joystick->setObjectName(QStringLiteral("grp_Joystick"));
        sizePolicy.setHeightForWidth(grp_Joystick->sizePolicy().hasHeightForWidth());
        grp_Joystick->setSizePolicy(sizePolicy);
        grp_Joystick->setMinimumSize(QSize(140, 0));
        grp_Joystick->setMaximumSize(QSize(160, 525));
        grp_Joystick->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_6 = new QVBoxLayout(grp_Joystick);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, 1, -1, 1);
        joystick_Activado_chk = new QCheckBox(grp_Joystick);
        joystick_Activado_chk->setObjectName(QStringLiteral("joystick_Activado_chk"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(joystick_Activado_chk->sizePolicy().hasHeightForWidth());
        joystick_Activado_chk->setSizePolicy(sizePolicy1);
        joystick_Activado_chk->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_6->addWidget(joystick_Activado_chk);

        chk_LED_Joy_Y_Desc = new QCheckBox(grp_Joystick);
        chk_LED_Joy_Y_Desc->setObjectName(QStringLiteral("chk_LED_Joy_Y_Desc"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(chk_LED_Joy_Y_Desc->sizePolicy().hasHeightForWidth());
        chk_LED_Joy_Y_Desc->setSizePolicy(sizePolicy2);
        chk_LED_Joy_Y_Desc->setMinimumSize(QSize(40, 0));
        chk_LED_Joy_Y_Desc->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_6->addWidget(chk_LED_Joy_Y_Desc);

        chk_LED_Joy_X_Desc = new QCheckBox(grp_Joystick);
        chk_LED_Joy_X_Desc->setObjectName(QStringLiteral("chk_LED_Joy_X_Desc"));
        sizePolicy2.setHeightForWidth(chk_LED_Joy_X_Desc->sizePolicy().hasHeightForWidth());
        chk_LED_Joy_X_Desc->setSizePolicy(sizePolicy2);
        chk_LED_Joy_X_Desc->setMinimumSize(QSize(20, 0));
        chk_LED_Joy_X_Desc->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_6->addWidget(chk_LED_Joy_X_Desc);

        chk_LED_Joy_Y_OutR = new QCheckBox(grp_Joystick);
        chk_LED_Joy_Y_OutR->setObjectName(QStringLiteral("chk_LED_Joy_Y_OutR"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(chk_LED_Joy_Y_OutR->sizePolicy().hasHeightForWidth());
        chk_LED_Joy_Y_OutR->setSizePolicy(sizePolicy3);
        chk_LED_Joy_Y_OutR->setMinimumSize(QSize(40, 0));
        chk_LED_Joy_Y_OutR->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_6->addWidget(chk_LED_Joy_Y_OutR);

        chk_LED_Joy_X_OutR = new QCheckBox(grp_Joystick);
        chk_LED_Joy_X_OutR->setObjectName(QStringLiteral("chk_LED_Joy_X_OutR"));
        sizePolicy3.setHeightForWidth(chk_LED_Joy_X_OutR->sizePolicy().hasHeightForWidth());
        chk_LED_Joy_X_OutR->setSizePolicy(sizePolicy3);
        chk_LED_Joy_X_OutR->setMinimumSize(QSize(20, 0));
        chk_LED_Joy_X_OutR->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_6->addWidget(chk_LED_Joy_X_OutR);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(2, -1, 2, -1);
        joystick_Y_lbl = new QLabel(grp_Joystick);
        joystick_Y_lbl->setObjectName(QStringLiteral("joystick_Y_lbl"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(joystick_Y_lbl->sizePolicy().hasHeightForWidth());
        joystick_Y_lbl->setSizePolicy(sizePolicy4);
        joystick_Y_lbl->setMinimumSize(QSize(18, 50));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, joystick_Y_lbl);

        joystick_Y_lcd = new QLCDNumber(grp_Joystick);
        joystick_Y_lcd->setObjectName(QStringLiteral("joystick_Y_lcd"));
        sizePolicy.setHeightForWidth(joystick_Y_lcd->sizePolicy().hasHeightForWidth());
        joystick_Y_lcd->setSizePolicy(sizePolicy);
        joystick_Y_lcd->setMinimumSize(QSize(50, 40));
        joystick_Y_lcd->setMaximumSize(QSize(16777215, 60));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        joystick_Y_lcd->setFont(font);
        joystick_Y_lcd->setDigitCount(4);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, joystick_Y_lcd);

        joystick_X_lbl = new QLabel(grp_Joystick);
        joystick_X_lbl->setObjectName(QStringLiteral("joystick_X_lbl"));
        sizePolicy4.setHeightForWidth(joystick_X_lbl->sizePolicy().hasHeightForWidth());
        joystick_X_lbl->setSizePolicy(sizePolicy4);
        joystick_X_lbl->setMinimumSize(QSize(17, 50));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, joystick_X_lbl);

        joystick_X_lcd = new QLCDNumber(grp_Joystick);
        joystick_X_lcd->setObjectName(QStringLiteral("joystick_X_lcd"));
        joystick_X_lcd->setEnabled(true);
        sizePolicy.setHeightForWidth(joystick_X_lcd->sizePolicy().hasHeightForWidth());
        joystick_X_lcd->setSizePolicy(sizePolicy);
        joystick_X_lcd->setMinimumSize(QSize(50, 40));
        joystick_X_lcd->setMaximumSize(QSize(16777215, 60));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        joystick_X_lcd->setFont(font1);
        joystick_X_lcd->setDigitCount(4);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, joystick_X_lcd);

        label_34 = new QLabel(grp_Joystick);
        label_34->setObjectName(QStringLiteral("label_34"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_34);

        label_36 = new QLabel(grp_Joystick);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, label_36);

        Jy_Min_lbl = new QLabel(grp_Joystick);
        Jy_Min_lbl->setObjectName(QStringLiteral("Jy_Min_lbl"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, Jy_Min_lbl);

        Jy_Max_lbl = new QLabel(grp_Joystick);
        Jy_Max_lbl->setObjectName(QStringLiteral("Jy_Max_lbl"));
        Jy_Max_lbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, Jy_Max_lbl);

        label_39 = new QLabel(grp_Joystick);
        label_39->setObjectName(QStringLiteral("label_39"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_39);

        label_40 = new QLabel(grp_Joystick);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, label_40);

        Jx_Min_lbl = new QLabel(grp_Joystick);
        Jx_Min_lbl->setObjectName(QStringLiteral("Jx_Min_lbl"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, Jx_Min_lbl);

        Jx_Max_lbl = new QLabel(grp_Joystick);
        Jx_Max_lbl->setObjectName(QStringLiteral("Jx_Max_lbl"));
        Jx_Max_lbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(6, QFormLayout::FieldRole, Jx_Max_lbl);


        verticalLayout_6->addLayout(formLayout_2);

        gridLayout_3 = new QFrame(grp_Joystick);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout(gridLayout_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(6);
        gridLayout_2->setContentsMargins(1, -1, -1, -1);
        joystickVertical_sld = new QSlider(gridLayout_3);
        joystickVertical_sld->setObjectName(QStringLiteral("joystickVertical_sld"));
        joystickVertical_sld->setMinimumSize(QSize(0, 60));
        joystickVertical_sld->setMaximumSize(QSize(16777215, 100));
        joystickVertical_sld->setMinimum(370);
        joystickVertical_sld->setMaximum(640);
        joystickVertical_sld->setPageStep(36);
        joystickVertical_sld->setValue(512);
        joystickVertical_sld->setOrientation(Qt::Vertical);
        joystickVertical_sld->setTickPosition(QSlider::TicksBelow);

        gridLayout_2->addWidget(joystickVertical_sld, 2, 0, 1, 1);

        joystickHorizontal_Sld = new QSlider(gridLayout_3);
        joystickHorizontal_Sld->setObjectName(QStringLiteral("joystickHorizontal_Sld"));
        joystickHorizontal_Sld->setMinimum(374);
        joystickHorizontal_Sld->setMaximum(640);
        joystickHorizontal_Sld->setPageStep(33);
        joystickHorizontal_Sld->setValue(512);
        joystickHorizontal_Sld->setOrientation(Qt::Horizontal);
        joystickHorizontal_Sld->setTickPosition(QSlider::TicksAbove);

        gridLayout_2->addWidget(joystickHorizontal_Sld, 3, 0, 1, 1);


        verticalLayout_6->addWidget(gridLayout_3);


        SensorsInfo_horLayout->addWidget(grp_Joystick);

        grp_Botones = new QGroupBox(Joystick_and_Actuators_hotLayout);
        grp_Botones->setObjectName(QStringLiteral("grp_Botones"));
        sizePolicy.setHeightForWidth(grp_Botones->sizePolicy().hasHeightForWidth());
        grp_Botones->setSizePolicy(sizePolicy);
        grp_Botones->setMinimumSize(QSize(70, 0));
        grp_Botones->setMaximumSize(QSize(104, 256));
        grp_Botones->setAutoFillBackground(true);
        verticalLayout_9 = new QVBoxLayout(grp_Botones);
        verticalLayout_9->setSpacing(4);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(1, 1, 1, 2);
        frame = new QFrame(grp_Botones);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(35, 0));
        frame->setMaximumSize(QSize(115, 16777215));
        verticalLayout_8 = new QVBoxLayout(frame);
        verticalLayout_8->setSpacing(2);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        FixFreno_chk = new QCheckBox(frame);
        FixFreno_chk->setObjectName(QStringLiteral("FixFreno_chk"));
        sizePolicy.setHeightForWidth(FixFreno_chk->sizePolicy().hasHeightForWidth());
        FixFreno_chk->setSizePolicy(sizePolicy);
        FixFreno_chk->setMinimumSize(QSize(10, 0));

        verticalLayout_8->addWidget(FixFreno_chk);

        PalUp_chk = new QCheckBox(frame);
        PalUp_chk->setObjectName(QStringLiteral("PalUp_chk"));
        sizePolicy.setHeightForWidth(PalUp_chk->sizePolicy().hasHeightForWidth());
        PalUp_chk->setSizePolicy(sizePolicy);
        PalUp_chk->setMinimumSize(QSize(0, 0));

        verticalLayout_8->addWidget(PalUp_chk);

        PalDown_chk = new QCheckBox(frame);
        PalDown_chk->setObjectName(QStringLiteral("PalDown_chk"));
        sizePolicy.setHeightForWidth(PalDown_chk->sizePolicy().hasHeightForWidth());
        PalDown_chk->setSizePolicy(sizePolicy);
        PalDown_chk->setMinimumSize(QSize(0, 0));

        verticalLayout_8->addWidget(PalDown_chk);

        RoadMode_chk = new QCheckBox(frame);
        RoadMode_chk->setObjectName(QStringLiteral("RoadMode_chk"));
        sizePolicy.setHeightForWidth(RoadMode_chk->sizePolicy().hasHeightForWidth());
        RoadMode_chk->setSizePolicy(sizePolicy);
        RoadMode_chk->setMinimumSize(QSize(0, 0));

        verticalLayout_8->addWidget(RoadMode_chk);


        verticalLayout_9->addWidget(frame);


        SensorsInfo_horLayout->addWidget(grp_Botones);

        grp_Freno = new QGroupBox(Joystick_and_Actuators_hotLayout);
        grp_Freno->setObjectName(QStringLiteral("grp_Freno"));
        sizePolicy.setHeightForWidth(grp_Freno->sizePolicy().hasHeightForWidth());
        grp_Freno->setSizePolicy(sizePolicy);
        grp_Freno->setMinimumSize(QSize(170, 450));
        grp_Freno->setMaximumSize(QSize(180, 525));
        grp_Freno->setAutoFillBackground(true);
        verticalLayout_2 = new QVBoxLayout(grp_Freno);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(3, 1, 5, 1);
        frame_5 = new QFrame(grp_Freno);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setMinimumSize(QSize(136, 0));
        frmLay_Freno = new QFormLayout(frame_5);
        frmLay_Freno->setSpacing(6);
        frmLay_Freno->setContentsMargins(11, 11, 11, 11);
        frmLay_Freno->setObjectName(QStringLiteral("frmLay_Freno"));
        frmLay_Freno->setHorizontalSpacing(1);
        frmLay_Freno->setVerticalSpacing(3);
        valorFreno_lbl = new QLabel(frame_5);
        valorFreno_lbl->setObjectName(QStringLiteral("valorFreno_lbl"));
        valorFreno_lbl->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(6, QFormLayout::LabelRole, valorFreno_lbl);

        frenoPos_lcd = new QLCDNumber(frame_5);
        frenoPos_lcd->setObjectName(QStringLiteral("frenoPos_lcd"));
        sizePolicy.setHeightForWidth(frenoPos_lcd->sizePolicy().hasHeightForWidth());
        frenoPos_lcd->setSizePolicy(sizePolicy);
        frenoPos_lcd->setMinimumSize(QSize(75, 40));
        frenoPos_lcd->setFont(font);
        frenoPos_lcd->setDigitCount(4);

        frmLay_Freno->setWidget(6, QFormLayout::FieldRole, frenoPos_lcd);

        label = new QLabel(frame_5);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(7, QFormLayout::LabelRole, label);

        frenoDes_lcd = new QLCDNumber(frame_5);
        frenoDes_lcd->setObjectName(QStringLiteral("frenoDes_lcd"));
        sizePolicy.setHeightForWidth(frenoDes_lcd->sizePolicy().hasHeightForWidth());
        frenoDes_lcd->setSizePolicy(sizePolicy);
        frenoDes_lcd->setMinimumSize(QSize(0, 30));
        frenoDes_lcd->setFont(font);
        frenoDes_lcd->setDigitCount(4);

        frmLay_Freno->setWidget(7, QFormLayout::FieldRole, frenoDes_lcd);

        Freno_lcdError = new QLCDNumber(frame_5);
        Freno_lcdError->setObjectName(QStringLiteral("Freno_lcdError"));
        sizePolicy.setHeightForWidth(Freno_lcdError->sizePolicy().hasHeightForWidth());
        Freno_lcdError->setSizePolicy(sizePolicy);
        Freno_lcdError->setMinimumSize(QSize(0, 30));

        frmLay_Freno->setWidget(8, QFormLayout::FieldRole, Freno_lcdError);

        Freno_lblError = new QLabel(frame_5);
        Freno_lblError->setObjectName(QStringLiteral("Freno_lblError"));

        frmLay_Freno->setWidget(8, QFormLayout::LabelRole, Freno_lblError);

        frenoControl_lcd = new QLCDNumber(frame_5);
        frenoControl_lcd->setObjectName(QStringLiteral("frenoControl_lcd"));
        frenoControl_lcd->setEnabled(true);
        sizePolicy.setHeightForWidth(frenoControl_lcd->sizePolicy().hasHeightForWidth());
        frenoControl_lcd->setSizePolicy(sizePolicy);
        frenoControl_lcd->setMinimumSize(QSize(30, 30));
        frenoControl_lcd->setFont(font);
        frenoControl_lcd->setSmallDecimalPoint(false);
        frenoControl_lcd->setDigitCount(6);

        frmLay_Freno->setWidget(9, QFormLayout::FieldRole, frenoControl_lcd);

        label_2 = new QLabel(frame_5);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(9, QFormLayout::LabelRole, label_2);

        Freno_Inhibido_chk = new QCheckBox(frame_5);
        Freno_Inhibido_chk->setObjectName(QStringLiteral("Freno_Inhibido_chk"));
        Freno_Inhibido_chk->setLayoutDirection(Qt::RightToLeft);

        frmLay_Freno->setWidget(2, QFormLayout::FieldRole, Freno_Inhibido_chk);

        label_7 = new QLabel(frame_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(2, QFormLayout::LabelRole, label_7);

        Freno_Activado_chk = new QCheckBox(frame_5);
        Freno_Activado_chk->setObjectName(QStringLiteral("Freno_Activado_chk"));
        Freno_Activado_chk->setLayoutDirection(Qt::RightToLeft);

        frmLay_Freno->setWidget(1, QFormLayout::FieldRole, Freno_Activado_chk);

        FrenoActivado_lbl = new QLabel(frame_5);
        FrenoActivado_lbl->setObjectName(QStringLiteral("FrenoActivado_lbl"));
        FrenoActivado_lbl->setMinimumSize(QSize(20, 0));

        frmLay_Freno->setWidget(1, QFormLayout::LabelRole, FrenoActivado_lbl);

        chk_LED_Freno_OutR = new QCheckBox(frame_5);
        chk_LED_Freno_OutR->setObjectName(QStringLiteral("chk_LED_Freno_OutR"));
        sizePolicy2.setHeightForWidth(chk_LED_Freno_OutR->sizePolicy().hasHeightForWidth());
        chk_LED_Freno_OutR->setSizePolicy(sizePolicy2);
        chk_LED_Freno_OutR->setMinimumSize(QSize(50, 0));
        chk_LED_Freno_OutR->setLayoutDirection(Qt::RightToLeft);

        frmLay_Freno->setWidget(4, QFormLayout::FieldRole, chk_LED_Freno_OutR);

        chk_LED_Freno_Desc = new QCheckBox(frame_5);
        chk_LED_Freno_Desc->setObjectName(QStringLiteral("chk_LED_Freno_Desc"));
        sizePolicy2.setHeightForWidth(chk_LED_Freno_Desc->sizePolicy().hasHeightForWidth());
        chk_LED_Freno_Desc->setSizePolicy(sizePolicy2);
        chk_LED_Freno_Desc->setMinimumSize(QSize(20, 0));
        chk_LED_Freno_Desc->setLayoutDirection(Qt::RightToLeft);

        frmLay_Freno->setWidget(3, QFormLayout::FieldRole, chk_LED_Freno_Desc);


        verticalLayout_2->addWidget(frame_5);

        FrenoControl_Slider = new QSlider(grp_Freno);
        FrenoControl_Slider->setObjectName(QStringLiteral("FrenoControl_Slider"));
        FrenoControl_Slider->setMinimum(-3200);
        FrenoControl_Slider->setMaximum(3200);
        FrenoControl_Slider->setSingleStep(100);
        FrenoControl_Slider->setPageStep(800);
        FrenoControl_Slider->setOrientation(Qt::Horizontal);
        FrenoControl_Slider->setTickPosition(QSlider::TicksAbove);

        verticalLayout_2->addWidget(FrenoControl_Slider);

        frame_2 = new QFrame(grp_Freno);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setMaximumSize(QSize(16777215, 72));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_15 = new QVBoxLayout(frame_2);
        verticalLayout_15->setSpacing(3);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(3, 2, 3, 0);
        label_26 = new QLabel(frame_2);
        label_26->setObjectName(QStringLiteral("label_26"));

        verticalLayout_15->addWidget(label_26);

        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        label_29 = new QLabel(frame_2);
        label_29->setObjectName(QStringLiteral("label_29"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_29);

        label_28 = new QLabel(frame_2);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, label_28);

        brake_PosLimits_Min_lbl = new QLabel(frame_2);
        brake_PosLimits_Min_lbl->setObjectName(QStringLiteral("brake_PosLimits_Min_lbl"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, brake_PosLimits_Min_lbl);

        brake_PosLimits_Max_lbl = new QLabel(frame_2);
        brake_PosLimits_Max_lbl->setObjectName(QStringLiteral("brake_PosLimits_Max_lbl"));
        brake_PosLimits_Max_lbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, brake_PosLimits_Max_lbl);


        verticalLayout_15->addLayout(formLayout_3);


        verticalLayout_2->addWidget(frame_2);

        Brake_Driver_lay_2 = new QFrame(grp_Freno);
        Brake_Driver_lay_2->setObjectName(QStringLiteral("Brake_Driver_lay_2"));
        Brake_Driver_lay = new QFormLayout(Brake_Driver_lay_2);
        Brake_Driver_lay->setSpacing(6);
        Brake_Driver_lay->setContentsMargins(11, 11, 11, 11);
        Brake_Driver_lay->setObjectName(QStringLiteral("Brake_Driver_lay"));
        Brake_Driver_lay->setHorizontalSpacing(3);
        Brake_Driver_lay->setVerticalSpacing(6);
        Brake_Driver_lay->setContentsMargins(-1, 3, 1, 3);
        label_8 = new QLabel(Brake_Driver_lay_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        Brake_Driver_lay->setWidget(0, QFormLayout::LabelRole, label_8);

        Brake_VIN_lbl = new QLabel(Brake_Driver_lay_2);
        Brake_VIN_lbl->setObjectName(QStringLiteral("Brake_VIN_lbl"));
        QFont font2;
        font2.setPointSize(14);
        Brake_VIN_lbl->setFont(font2);

        Brake_Driver_lay->setWidget(0, QFormLayout::FieldRole, Brake_VIN_lbl);

        label_10 = new QLabel(Brake_Driver_lay_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        Brake_Driver_lay->setWidget(1, QFormLayout::LabelRole, label_10);

        Brake_Temp_lbl = new QLabel(Brake_Driver_lay_2);
        Brake_Temp_lbl->setObjectName(QStringLiteral("Brake_Temp_lbl"));
        Brake_Temp_lbl->setFont(font2);

        Brake_Driver_lay->setWidget(1, QFormLayout::FieldRole, Brake_Temp_lbl);

        label_12 = new QLabel(Brake_Driver_lay_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        Brake_Driver_lay->setWidget(2, QFormLayout::LabelRole, label_12);

        Brake_Error_lbl = new QLabel(Brake_Driver_lay_2);
        Brake_Error_lbl->setObjectName(QStringLiteral("Brake_Error_lbl"));

        Brake_Driver_lay->setWidget(2, QFormLayout::FieldRole, Brake_Error_lbl);

        brake_ShowInfo_rBtn = new QRadioButton(Brake_Driver_lay_2);
        driversShowInfoSelect = new QButtonGroup(MainWindow);
        driversShowInfoSelect->setObjectName(QStringLiteral("driversShowInfoSelect"));
        driversShowInfoSelect->addButton(brake_ShowInfo_rBtn);
        brake_ShowInfo_rBtn->setObjectName(QStringLiteral("brake_ShowInfo_rBtn"));
        brake_ShowInfo_rBtn->setChecked(true);
        brake_ShowInfo_rBtn->setAutoExclusive(false);

        Brake_Driver_lay->setWidget(3, QFormLayout::FieldRole, brake_ShowInfo_rBtn);


        verticalLayout_2->addWidget(Brake_Driver_lay_2);


        SensorsInfo_horLayout->addWidget(grp_Freno);

        grp_Acelerador = new QGroupBox(Joystick_and_Actuators_hotLayout);
        grp_Acelerador->setObjectName(QStringLiteral("grp_Acelerador"));
        sizePolicy.setHeightForWidth(grp_Acelerador->sizePolicy().hasHeightForWidth());
        grp_Acelerador->setSizePolicy(sizePolicy);
        grp_Acelerador->setMinimumSize(QSize(170, 450));
        grp_Acelerador->setMaximumSize(QSize(180, 525));
        grp_Acelerador->setAutoFillBackground(true);
        grp_Acelerador->setFlat(false);
        verticalLayout_4 = new QVBoxLayout(grp_Acelerador);
        verticalLayout_4->setSpacing(3);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(3, 1, 3, 1);
        frame1 = new QFrame(grp_Acelerador);
        frame1->setObjectName(QStringLiteral("frame1"));
        frame1->setMinimumSize(QSize(136, 0));
        frmLay_Acelerador = new QFormLayout(frame1);
        frmLay_Acelerador->setSpacing(6);
        frmLay_Acelerador->setContentsMargins(11, 11, 11, 11);
        frmLay_Acelerador->setObjectName(QStringLiteral("frmLay_Acelerador"));
        frmLay_Acelerador->setHorizontalSpacing(1);
        frmLay_Acelerador->setVerticalSpacing(3);
        frmLay_Acelerador->setContentsMargins(-1, 3, -1, 5);
        Acel_Activado_lbl = new QLabel(frame1);
        Acel_Activado_lbl->setObjectName(QStringLiteral("Acel_Activado_lbl"));

        frmLay_Acelerador->setWidget(0, QFormLayout::LabelRole, Acel_Activado_lbl);

        Acel_Activado_chk = new QCheckBox(frame1);
        Acel_Activado_chk->setObjectName(QStringLiteral("Acel_Activado_chk"));
        sizePolicy2.setHeightForWidth(Acel_Activado_chk->sizePolicy().hasHeightForWidth());
        Acel_Activado_chk->setSizePolicy(sizePolicy2);
        Acel_Activado_chk->setLayoutDirection(Qt::RightToLeft);

        frmLay_Acelerador->setWidget(0, QFormLayout::FieldRole, Acel_Activado_chk);

        Acel_Inhibido_lbl = new QLabel(frame1);
        Acel_Inhibido_lbl->setObjectName(QStringLiteral("Acel_Inhibido_lbl"));

        frmLay_Acelerador->setWidget(1, QFormLayout::LabelRole, Acel_Inhibido_lbl);

        Acel_Inhibido_chk = new QCheckBox(frame1);
        Acel_Inhibido_chk->setObjectName(QStringLiteral("Acel_Inhibido_chk"));
        sizePolicy2.setHeightForWidth(Acel_Inhibido_chk->sizePolicy().hasHeightForWidth());
        Acel_Inhibido_chk->setSizePolicy(sizePolicy2);
        Acel_Inhibido_chk->setLayoutDirection(Qt::RightToLeft);

        frmLay_Acelerador->setWidget(1, QFormLayout::FieldRole, Acel_Inhibido_chk);

        chk_LED_Acel_OutR = new QCheckBox(frame1);
        chk_LED_Acel_OutR->setObjectName(QStringLiteral("chk_LED_Acel_OutR"));
        sizePolicy2.setHeightForWidth(chk_LED_Acel_OutR->sizePolicy().hasHeightForWidth());
        chk_LED_Acel_OutR->setSizePolicy(sizePolicy2);
        chk_LED_Acel_OutR->setMinimumSize(QSize(43, 0));
        chk_LED_Acel_OutR->setLayoutDirection(Qt::RightToLeft);

        frmLay_Acelerador->setWidget(3, QFormLayout::FieldRole, chk_LED_Acel_OutR);

        valorAcelerador_lbl = new QLabel(frame1);
        valorAcelerador_lbl->setObjectName(QStringLiteral("valorAcelerador_lbl"));

        frmLay_Acelerador->setWidget(5, QFormLayout::LabelRole, valorAcelerador_lbl);

        aceleradorPos_lcd = new QLCDNumber(frame1);
        aceleradorPos_lcd->setObjectName(QStringLiteral("aceleradorPos_lcd"));
        sizePolicy.setHeightForWidth(aceleradorPos_lcd->sizePolicy().hasHeightForWidth());
        aceleradorPos_lcd->setSizePolicy(sizePolicy);
        aceleradorPos_lcd->setMinimumSize(QSize(75, 40));
        aceleradorPos_lcd->setFont(font);
        aceleradorPos_lcd->setDigitCount(4);

        frmLay_Acelerador->setWidget(5, QFormLayout::FieldRole, aceleradorPos_lcd);

        label_3 = new QLabel(frame1);
        label_3->setObjectName(QStringLiteral("label_3"));

        frmLay_Acelerador->setWidget(6, QFormLayout::LabelRole, label_3);

        aceleradorDes_lcd = new QLCDNumber(frame1);
        aceleradorDes_lcd->setObjectName(QStringLiteral("aceleradorDes_lcd"));
        sizePolicy.setHeightForWidth(aceleradorDes_lcd->sizePolicy().hasHeightForWidth());
        aceleradorDes_lcd->setSizePolicy(sizePolicy);
        aceleradorDes_lcd->setMinimumSize(QSize(0, 30));
        aceleradorDes_lcd->setFont(font2);
        aceleradorDes_lcd->setDigitCount(4);

        frmLay_Acelerador->setWidget(6, QFormLayout::FieldRole, aceleradorDes_lcd);

        label_5 = new QLabel(frame1);
        label_5->setObjectName(QStringLiteral("label_5"));

        frmLay_Acelerador->setWidget(7, QFormLayout::LabelRole, label_5);

        Acelerador_lcdError = new QLCDNumber(frame1);
        Acelerador_lcdError->setObjectName(QStringLiteral("Acelerador_lcdError"));
        sizePolicy.setHeightForWidth(Acelerador_lcdError->sizePolicy().hasHeightForWidth());
        Acelerador_lcdError->setSizePolicy(sizePolicy);
        Acelerador_lcdError->setMinimumSize(QSize(0, 30));

        frmLay_Acelerador->setWidget(7, QFormLayout::FieldRole, Acelerador_lcdError);

        label_4 = new QLabel(frame1);
        label_4->setObjectName(QStringLiteral("label_4"));

        frmLay_Acelerador->setWidget(8, QFormLayout::LabelRole, label_4);

        aceleradorControl_lcd = new QLCDNumber(frame1);
        aceleradorControl_lcd->setObjectName(QStringLiteral("aceleradorControl_lcd"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(aceleradorControl_lcd->sizePolicy().hasHeightForWidth());
        aceleradorControl_lcd->setSizePolicy(sizePolicy5);
        aceleradorControl_lcd->setMinimumSize(QSize(0, 30));
        aceleradorControl_lcd->setFont(font2);
        aceleradorControl_lcd->setDigitCount(6);

        frmLay_Acelerador->setWidget(8, QFormLayout::FieldRole, aceleradorControl_lcd);

        chk_LED_Acel_Desc = new QCheckBox(frame1);
        chk_LED_Acel_Desc->setObjectName(QStringLiteral("chk_LED_Acel_Desc"));
        sizePolicy2.setHeightForWidth(chk_LED_Acel_Desc->sizePolicy().hasHeightForWidth());
        chk_LED_Acel_Desc->setSizePolicy(sizePolicy2);
        chk_LED_Acel_Desc->setMinimumSize(QSize(50, 0));
        chk_LED_Acel_Desc->setLayoutDirection(Qt::RightToLeft);

        frmLay_Acelerador->setWidget(2, QFormLayout::FieldRole, chk_LED_Acel_Desc);


        verticalLayout_4->addWidget(frame1);

        AceleradorControl_Slider = new QSlider(grp_Acelerador);
        AceleradorControl_Slider->setObjectName(QStringLiteral("AceleradorControl_Slider"));
        AceleradorControl_Slider->setMinimum(-3200);
        AceleradorControl_Slider->setMaximum(3200);
        AceleradorControl_Slider->setSingleStep(100);
        AceleradorControl_Slider->setPageStep(800);
        AceleradorControl_Slider->setOrientation(Qt::Horizontal);
        AceleradorControl_Slider->setTickPosition(QSlider::TicksAbove);

        verticalLayout_4->addWidget(AceleradorControl_Slider);

        frame2 = new QFrame(grp_Acelerador);
        frame2->setObjectName(QStringLiteral("frame2"));
        frame2->setLayoutDirection(Qt::LeftToRight);
        frame2->setFrameShape(QFrame::StyledPanel);
        frame2->setFrameShadow(QFrame::Raised);
        verticalLayout_13 = new QVBoxLayout(frame2);
        verticalLayout_13->setSpacing(2);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(3, 2, 3, 1);
        label_30 = new QLabel(frame2);
        label_30->setObjectName(QStringLiteral("label_30"));

        verticalLayout_13->addWidget(label_30);

        formLayout_4 = new QFormLayout();
        formLayout_4->setSpacing(6);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        label_31 = new QLabel(frame2);
        label_31->setObjectName(QStringLiteral("label_31"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_31);

        label_32 = new QLabel(frame2);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setLayoutDirection(Qt::LeftToRight);
        label_32->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, label_32);

        Accel_PosLimits_Max_lbl = new QLabel(frame2);
        Accel_PosLimits_Max_lbl->setObjectName(QStringLiteral("Accel_PosLimits_Max_lbl"));
        Accel_PosLimits_Max_lbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, Accel_PosLimits_Max_lbl);

        Accel_PosLimits_Min_lbl = new QLabel(frame2);
        Accel_PosLimits_Min_lbl->setObjectName(QStringLiteral("Accel_PosLimits_Min_lbl"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, Accel_PosLimits_Min_lbl);


        verticalLayout_13->addLayout(formLayout_4);


        verticalLayout_4->addWidget(frame2);

        Accel_Driver_lay = new QFormLayout();
        Accel_Driver_lay->setSpacing(6);
        Accel_Driver_lay->setObjectName(QStringLiteral("Accel_Driver_lay"));
        Accel_Driver_lay->setVerticalSpacing(6);
        Accel_Driver_lay->setContentsMargins(-1, 3, -1, 3);
        label_9 = new QLabel(grp_Acelerador);
        label_9->setObjectName(QStringLiteral("label_9"));

        Accel_Driver_lay->setWidget(0, QFormLayout::LabelRole, label_9);

        Accel_Vin_lbl = new QLabel(grp_Acelerador);
        Accel_Vin_lbl->setObjectName(QStringLiteral("Accel_Vin_lbl"));
        Accel_Vin_lbl->setFont(font2);

        Accel_Driver_lay->setWidget(0, QFormLayout::FieldRole, Accel_Vin_lbl);

        Accel_Temp_lbl = new QLabel(grp_Acelerador);
        Accel_Temp_lbl->setObjectName(QStringLiteral("Accel_Temp_lbl"));
        Accel_Temp_lbl->setFont(font2);

        Accel_Driver_lay->setWidget(1, QFormLayout::FieldRole, Accel_Temp_lbl);

        label_14 = new QLabel(grp_Acelerador);
        label_14->setObjectName(QStringLiteral("label_14"));

        Accel_Driver_lay->setWidget(1, QFormLayout::LabelRole, label_14);

        label_11 = new QLabel(grp_Acelerador);
        label_11->setObjectName(QStringLiteral("label_11"));

        Accel_Driver_lay->setWidget(2, QFormLayout::LabelRole, label_11);

        Accel_Error_lbl = new QLabel(grp_Acelerador);
        Accel_Error_lbl->setObjectName(QStringLiteral("Accel_Error_lbl"));

        Accel_Driver_lay->setWidget(2, QFormLayout::FieldRole, Accel_Error_lbl);

        accel_ShowInfo_rBtn = new QRadioButton(grp_Acelerador);
        driversShowInfoSelect->addButton(accel_ShowInfo_rBtn);
        accel_ShowInfo_rBtn->setObjectName(QStringLiteral("accel_ShowInfo_rBtn"));
        accel_ShowInfo_rBtn->setAutoExclusive(false);

        Accel_Driver_lay->setWidget(3, QFormLayout::FieldRole, accel_ShowInfo_rBtn);


        verticalLayout_4->addLayout(Accel_Driver_lay);


        SensorsInfo_horLayout->addWidget(grp_Acelerador);

        grp_Volante = new QGroupBox(Joystick_and_Actuators_hotLayout);
        grp_Volante->setObjectName(QStringLiteral("grp_Volante"));
        sizePolicy.setHeightForWidth(grp_Volante->sizePolicy().hasHeightForWidth());
        grp_Volante->setSizePolicy(sizePolicy);
        grp_Volante->setMinimumSize(QSize(110, 450));
        grp_Volante->setMaximumSize(QSize(110, 525));
        grp_Volante->setAutoFillBackground(true);
        verticalLayout_5 = new QVBoxLayout(grp_Volante);
        verticalLayout_5->setSpacing(4);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(3, 3, 3, 3);
        volante_Activado_chk = new QCheckBox(grp_Volante);
        volante_Activado_chk->setObjectName(QStringLiteral("volante_Activado_chk"));
        sizePolicy.setHeightForWidth(volante_Activado_chk->sizePolicy().hasHeightForWidth());
        volante_Activado_chk->setSizePolicy(sizePolicy);
        volante_Activado_chk->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_5->addWidget(volante_Activado_chk);

        volante_Inhibido_chk = new QCheckBox(grp_Volante);
        volante_Inhibido_chk->setObjectName(QStringLiteral("volante_Inhibido_chk"));
        volante_Inhibido_chk->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_5->addWidget(volante_Inhibido_chk);

        VolanteModo_cmb = new QComboBox(grp_Volante);
        VolanteModo_cmb->setObjectName(QStringLiteral("VolanteModo_cmb"));

        verticalLayout_5->addWidget(VolanteModo_cmb);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(3);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        valorVolante_lbl = new QLabel(grp_Volante);
        valorVolante_lbl->setObjectName(QStringLiteral("valorVolante_lbl"));
        valorVolante_lbl->setMinimumSize(QSize(25, 0));
        valorVolante_lbl->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(valorVolante_lbl);

        volante_lcd = new QLCDNumber(grp_Volante);
        volante_lcd->setObjectName(QStringLiteral("volante_lcd"));
        sizePolicy.setHeightForWidth(volante_lcd->sizePolicy().hasHeightForWidth());
        volante_lcd->setSizePolicy(sizePolicy);
        volante_lcd->setMinimumSize(QSize(40, 30));
        volante_lcd->setFont(font2);

        verticalLayout_11->addWidget(volante_lcd);


        verticalLayout_5->addLayout(verticalLayout_11);

        VolanteControl_Dial = new QDial(grp_Volante);
        VolanteControl_Dial->setObjectName(QStringLiteral("VolanteControl_Dial"));
        VolanteControl_Dial->setMinimumSize(QSize(50, 50));
        VolanteControl_Dial->setMaximumSize(QSize(90, 90));
        VolanteControl_Dial->setAutoFillBackground(false);
        VolanteControl_Dial->setMinimum(-3200);
        VolanteControl_Dial->setMaximum(3200);
        VolanteControl_Dial->setSingleStep(100);
        VolanteControl_Dial->setPageStep(400);
        VolanteControl_Dial->setInvertedAppearance(false);

        verticalLayout_5->addWidget(VolanteControl_Dial);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        formLayout_5 = new QFormLayout();
        formLayout_5->setSpacing(6);
        formLayout_5->setObjectName(QStringLiteral("formLayout_5"));
        label_13 = new QLabel(grp_Volante);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_13);

        label_15 = new QLabel(grp_Volante);
        label_15->setObjectName(QStringLiteral("label_15"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, label_15);

        label_16 = new QLabel(grp_Volante);
        label_16->setObjectName(QStringLiteral("label_16"));

        formLayout_5->setWidget(2, QFormLayout::LabelRole, label_16);

        Steer_Vin_lbl = new QLabel(grp_Volante);
        Steer_Vin_lbl->setObjectName(QStringLiteral("Steer_Vin_lbl"));
        Steer_Vin_lbl->setFont(font2);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, Steer_Vin_lbl);

        Steer_Temp_lbl = new QLabel(grp_Volante);
        Steer_Temp_lbl->setObjectName(QStringLiteral("Steer_Temp_lbl"));
        Steer_Temp_lbl->setFont(font2);

        formLayout_5->setWidget(1, QFormLayout::FieldRole, Steer_Temp_lbl);

        Steer_Error_lbl = new QLabel(grp_Volante);
        Steer_Error_lbl->setObjectName(QStringLiteral("Steer_Error_lbl"));

        formLayout_5->setWidget(2, QFormLayout::FieldRole, Steer_Error_lbl);

        steer_ShowInfo_rBtn = new QRadioButton(grp_Volante);
        driversShowInfoSelect->addButton(steer_ShowInfo_rBtn);
        steer_ShowInfo_rBtn->setObjectName(QStringLiteral("steer_ShowInfo_rBtn"));
        steer_ShowInfo_rBtn->setAutoExclusive(false);

        formLayout_5->setWidget(3, QFormLayout::FieldRole, steer_ShowInfo_rBtn);


        verticalLayout_5->addLayout(formLayout_5);


        SensorsInfo_horLayout->addWidget(grp_Volante);

        grp_ShiftGear_and_SystemInfo = new QWidget(Joystick_and_Actuators_hotLayout);
        grp_ShiftGear_and_SystemInfo->setObjectName(QStringLiteral("grp_ShiftGear_and_SystemInfo"));
        grp_ShiftGear_and_SystemInfo->setMinimumSize(QSize(56, 450));
        grp_ShiftGear_and_SystemInfo->setMaximumSize(QSize(160, 525));
        shiftGear_and_DefaultDefines = new QVBoxLayout(grp_ShiftGear_and_SystemInfo);
        shiftGear_and_DefaultDefines->setSpacing(6);
        shiftGear_and_DefaultDefines->setContentsMargins(11, 11, 11, 11);
        shiftGear_and_DefaultDefines->setObjectName(QStringLiteral("shiftGear_and_DefaultDefines"));
        palanca_grp = new QGroupBox(grp_ShiftGear_and_SystemInfo);
        palanca_grp->setObjectName(QStringLiteral("palanca_grp"));
        sizePolicy2.setHeightForWidth(palanca_grp->sizePolicy().hasHeightForWidth());
        palanca_grp->setSizePolicy(sizePolicy2);
        palanca_grp->setMinimumSize(QSize(90, 200));
        palanca_grp->setLayoutDirection(Qt::LeftToRight);
        palanca_grp->setAutoFillBackground(true);
        palanca_grp->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        verticalLayout_10 = new QVBoxLayout(palanca_grp);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        palanca_Activada_chk = new QCheckBox(palanca_grp);
        palanca_Activada_chk->setObjectName(QStringLiteral("palanca_Activada_chk"));
        sizePolicy2.setHeightForWidth(palanca_Activada_chk->sizePolicy().hasHeightForWidth());
        palanca_Activada_chk->setSizePolicy(sizePolicy2);
        palanca_Activada_chk->setMinimumSize(QSize(50, 0));
        palanca_Activada_chk->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_14->addWidget(palanca_Activada_chk);

        palanca_Inhibida_chk = new QCheckBox(palanca_grp);
        palanca_Inhibida_chk->setObjectName(QStringLiteral("palanca_Inhibida_chk"));
        palanca_Inhibida_chk->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_14->addWidget(palanca_Inhibida_chk);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(verticalSpacer);


        verticalLayout_10->addLayout(verticalLayout_14);


        shiftGear_and_DefaultDefines->addWidget(palanca_grp);

        time_frame = new QFrame(grp_ShiftGear_and_SystemInfo);
        time_frame->setObjectName(QStringLiteral("time_frame"));
        time_frame->setFrameShape(QFrame::StyledPanel);
        time_frame->setFrameShadow(QFrame::Raised);
        verticalLayout_7 = new QVBoxLayout(time_frame);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(7, 7, 7, 7);
        formLayout_6 = new QFormLayout();
        formLayout_6->setSpacing(6);
        formLayout_6->setObjectName(QStringLiteral("formLayout_6"));
        label_27 = new QLabel(time_frame);
        label_27->setObjectName(QStringLiteral("label_27"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_27);

        T_lbl = new QLabel(time_frame);
        T_lbl->setObjectName(QStringLiteral("T_lbl"));

        formLayout_6->setWidget(0, QFormLayout::FieldRole, T_lbl);

        T_max_lbl = new QLabel(time_frame);
        T_max_lbl->setObjectName(QStringLiteral("T_max_lbl"));
        T_max_lbl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(2, QFormLayout::FieldRole, T_max_lbl);

        label_35 = new QLabel(time_frame);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(1, QFormLayout::FieldRole, label_35);

        label_33 = new QLabel(time_frame);
        label_33->setObjectName(QStringLiteral("label_33"));

        formLayout_6->setWidget(1, QFormLayout::LabelRole, label_33);

        T_min_lbl = new QLabel(time_frame);
        T_min_lbl->setObjectName(QStringLiteral("T_min_lbl"));

        formLayout_6->setWidget(2, QFormLayout::LabelRole, T_min_lbl);


        verticalLayout_7->addLayout(formLayout_6);

        normalDefines_chk = new QCheckBox(time_frame);
        normalDefines_chk->setObjectName(QStringLiteral("normalDefines_chk"));
        normalDefines_chk->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_7->addWidget(normalDefines_chk);


        shiftGear_and_DefaultDefines->addWidget(time_frame);


        SensorsInfo_horLayout->addWidget(grp_ShiftGear_and_SystemInfo);


        SensorsInfo_verLayout->addWidget(Joystick_and_Actuators_hotLayout);


        Valores_Widget->addWidget(Joystick_and_Actuators_ext_hotLayout);

        Edo_ConexionConfig_and_Error_vertWidget = new QWidget(SensorsInfo_Errors_and_Conn_Widget);
        Edo_ConexionConfig_and_Error_vertWidget->setObjectName(QStringLiteral("Edo_ConexionConfig_and_Error_vertWidget"));
        sizePolicy.setHeightForWidth(Edo_ConexionConfig_and_Error_vertWidget->sizePolicy().hasHeightForWidth());
        Edo_ConexionConfig_and_Error_vertWidget->setSizePolicy(sizePolicy);
        Edo_ConexionConfig_and_Error_vertWidget->setMinimumSize(QSize(50, 0));
        Edo_ConexionConfig_and_Error_vertWidget->setMaximumSize(QSize(300, 515));
        Edo_ConexionConfig_and_Error_vertWidget->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_12 = new QVBoxLayout(Edo_ConexionConfig_and_Error_vertWidget);
        verticalLayout_12->setSpacing(3);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(1, 1, 1, 1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        logoOlin_lbl = new QLabel(Edo_ConexionConfig_and_Error_vertWidget);
        logoOlin_lbl->setObjectName(QStringLiteral("logoOlin_lbl"));
        logoOlin_lbl->setMaximumSize(QSize(80, 80));
        logoOlin_lbl->setAutoFillBackground(false);
        logoOlin_lbl->setPixmap(QPixmap(QString::fromUtf8(":/images/Isotipo.png")));
        logoOlin_lbl->setScaledContents(true);
        logoOlin_lbl->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(logoOlin_lbl);


        verticalLayout_12->addLayout(horizontalLayout);

        Status_horLay = new QFrame(Edo_ConexionConfig_and_Error_vertWidget);
        Status_horLay->setObjectName(QStringLiteral("Status_horLay"));
        EstadoIsiukak_horLayout = new QHBoxLayout(Status_horLay);
        EstadoIsiukak_horLayout->setSpacing(4);
        EstadoIsiukak_horLayout->setContentsMargins(11, 11, 11, 11);
        EstadoIsiukak_horLayout->setObjectName(QStringLiteral("EstadoIsiukak_horLayout"));
        lblEstadoSistema = new QLabel(Status_horLay);
        lblEstadoSistema->setObjectName(QStringLiteral("lblEstadoSistema"));
        lblEstadoSistema->setMinimumSize(QSize(30, 0));
        QFont font3;
        font3.setPointSize(13);
        lblEstadoSistema->setFont(font3);

        EstadoIsiukak_horLayout->addWidget(lblEstadoSistema);

        estadoSistema_lbl = new QLabel(Status_horLay);
        estadoSistema_lbl->setObjectName(QStringLiteral("estadoSistema_lbl"));
        estadoSistema_lbl->setMinimumSize(QSize(217, 30));
        QFont font4;
        font4.setPointSize(16);
        estadoSistema_lbl->setFont(font4);

        EstadoIsiukak_horLayout->addWidget(estadoSistema_lbl);


        verticalLayout_12->addWidget(Status_horLay);

        driverErrorsHeaders_gridLayout_2 = new QFrame(Edo_ConexionConfig_and_Error_vertWidget);
        driverErrorsHeaders_gridLayout_2->setObjectName(QStringLiteral("driverErrorsHeaders_gridLayout_2"));
        driverErrorsHeaders_gridLayout = new QGridLayout(driverErrorsHeaders_gridLayout_2);
        driverErrorsHeaders_gridLayout->setSpacing(6);
        driverErrorsHeaders_gridLayout->setContentsMargins(11, 11, 11, 11);
        driverErrorsHeaders_gridLayout->setObjectName(QStringLiteral("driverErrorsHeaders_gridLayout"));
        label_21 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_21->setObjectName(QStringLiteral("label_21"));

        driverErrorsHeaders_gridLayout->addWidget(label_21, 0, 6, 1, 1);

        label_25 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_25->setObjectName(QStringLiteral("label_25"));

        driverErrorsHeaders_gridLayout->addWidget(label_25, 0, 10, 1, 1);

        label_24 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_24->setObjectName(QStringLiteral("label_24"));

        driverErrorsHeaders_gridLayout->addWidget(label_24, 0, 9, 1, 1);

        label_20 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_20->setObjectName(QStringLiteral("label_20"));

        driverErrorsHeaders_gridLayout->addWidget(label_20, 0, 5, 1, 1);

        label_38 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setMinimumSize(QSize(18, 0));

        driverErrorsHeaders_gridLayout->addWidget(label_38, 0, 0, 1, 1);

        label_22 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_22->setObjectName(QStringLiteral("label_22"));

        driverErrorsHeaders_gridLayout->addWidget(label_22, 0, 7, 1, 1);

        label_23 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_23->setObjectName(QStringLiteral("label_23"));

        driverErrorsHeaders_gridLayout->addWidget(label_23, 0, 8, 1, 1);

        label_17 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_17->setObjectName(QStringLiteral("label_17"));

        driverErrorsHeaders_gridLayout->addWidget(label_17, 0, 2, 1, 1);

        label_18 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_18->setObjectName(QStringLiteral("label_18"));

        driverErrorsHeaders_gridLayout->addWidget(label_18, 0, 3, 1, 1);

        label_19 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_19->setObjectName(QStringLiteral("label_19"));

        driverErrorsHeaders_gridLayout->addWidget(label_19, 0, 4, 1, 1);

        label_37 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setMinimumSize(QSize(18, 0));

        driverErrorsHeaders_gridLayout->addWidget(label_37, 0, 1, 1, 1);

        label_41 = new QLabel(driverErrorsHeaders_gridLayout_2);
        label_41->setObjectName(QStringLiteral("label_41"));

        driverErrorsHeaders_gridLayout->addWidget(label_41, 0, 11, 1, 1);


        verticalLayout_12->addWidget(driverErrorsHeaders_gridLayout_2);

        driverErrorsValues_gridLayout_2 = new QFrame(Edo_ConexionConfig_and_Error_vertWidget);
        driverErrorsValues_gridLayout_2->setObjectName(QStringLiteral("driverErrorsValues_gridLayout_2"));
        driverErrorsValues_gridLayout = new QGridLayout(driverErrorsValues_gridLayout_2);
        driverErrorsValues_gridLayout->setSpacing(1);
        driverErrorsValues_gridLayout->setContentsMargins(11, 11, 11, 11);
        driverErrorsValues_gridLayout->setObjectName(QStringLiteral("driverErrorsValues_gridLayout"));

        verticalLayout_12->addWidget(driverErrorsValues_gridLayout_2);

        driversValues_txt = new QPlainTextEdit(Edo_ConexionConfig_and_Error_vertWidget);
        driversValues_txt->setObjectName(QStringLiteral("driversValues_txt"));
        driversValues_txt->setEnabled(false);
        sizePolicy.setHeightForWidth(driversValues_txt->sizePolicy().hasHeightForWidth());
        driversValues_txt->setSizePolicy(sizePolicy);
        driversValues_txt->setMaximumSize(QSize(16777215, 220));

        verticalLayout_12->addWidget(driversValues_txt);

        erroresSalida_txt = new QPlainTextEdit(Edo_ConexionConfig_and_Error_vertWidget);
        erroresSalida_txt->setObjectName(QStringLiteral("erroresSalida_txt"));
        sizePolicy.setHeightForWidth(erroresSalida_txt->sizePolicy().hasHeightForWidth());
        erroresSalida_txt->setSizePolicy(sizePolicy);
        erroresSalida_txt->setMinimumSize(QSize(60, 0));
        erroresSalida_txt->setBaseSize(QSize(70, 0));

        verticalLayout_12->addWidget(erroresSalida_txt);

        frame_4 = new QFrame(Edo_ConexionConfig_and_Error_vertWidget);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        horizontalLayout_4 = new QHBoxLayout(frame_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        lblDescripcion = new QLabel(frame_4);
        lblDescripcion->setObjectName(QStringLiteral("lblDescripcion"));
        lblDescripcion->setLayoutDirection(Qt::RightToLeft);
        lblDescripcion->setAutoFillBackground(false);
        lblDescripcion->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(lblDescripcion);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        cmbBaudRate = new QComboBox(frame_4);
        cmbBaudRate->setObjectName(QStringLiteral("cmbBaudRate"));

        horizontalLayout_2->addWidget(cmbBaudRate);

        cmbSerialPortSelector = new QComboBox(frame_4);
        cmbSerialPortSelector->setObjectName(QStringLiteral("cmbSerialPortSelector"));
        cmbSerialPortSelector->setMinimumSize(QSize(0, 25));

        horizontalLayout_2->addWidget(cmbSerialPortSelector);


        horizontalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_12->addWidget(frame_4);

        Connection_horLay = new QFrame(Edo_ConexionConfig_and_Error_vertWidget);
        Connection_horLay->setObjectName(QStringLiteral("Connection_horLay"));
        horizontalLayout_3 = new QHBoxLayout(Connection_horLay);
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnParoEmergencia = new QPushButton(Connection_horLay);
        btnParoEmergencia->setObjectName(QStringLiteral("btnParoEmergencia"));
        sizePolicy.setHeightForWidth(btnParoEmergencia->sizePolicy().hasHeightForWidth());
        btnParoEmergencia->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(btnParoEmergencia);

        buttonsConnection_verLay = new QFrame(Connection_horLay);
        buttonsConnection_verLay->setObjectName(QStringLiteral("buttonsConnection_verLay"));
        buttonsConnection_verLay->setMinimumSize(QSize(0, 0));
        verticalLayout_3 = new QVBoxLayout(buttonsConnection_verLay);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(3, 3, 3, 3);
        btnConectar = new QPushButton(buttonsConnection_verLay);
        btnConectar->setObjectName(QStringLiteral("btnConectar"));
        btnConectar->setEnabled(true);
        sizePolicy.setHeightForWidth(btnConectar->sizePolicy().hasHeightForWidth());
        btnConectar->setSizePolicy(sizePolicy);
        btnConectar->setMinimumSize(QSize(0, 25));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnConectar->setIcon(icon1);

        verticalLayout_3->addWidget(btnConectar);

        btnDesconectar = new QPushButton(buttonsConnection_verLay);
        btnDesconectar->setObjectName(QStringLiteral("btnDesconectar"));
        btnDesconectar->setEnabled(false);
        sizePolicy.setHeightForWidth(btnDesconectar->sizePolicy().hasHeightForWidth());
        btnDesconectar->setSizePolicy(sizePolicy);
        btnDesconectar->setMinimumSize(QSize(0, 25));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDesconectar->setIcon(icon2);

        verticalLayout_3->addWidget(btnDesconectar);


        horizontalLayout_3->addWidget(buttonsConnection_verLay);


        verticalLayout_12->addWidget(Connection_horLay);


        Valores_Widget->addWidget(Edo_ConexionConfig_and_Error_vertWidget);


        verticalLayout->addWidget(SensorsInfo_Errors_and_Conn_Widget);

        SalidaConsola_Widget = new QWidget(centralWidget);
        SalidaConsola_Widget->setObjectName(QStringLiteral("SalidaConsola_Widget"));
        sizePolicy.setHeightForWidth(SalidaConsola_Widget->sizePolicy().hasHeightForWidth());
        SalidaConsola_Widget->setSizePolicy(sizePolicy);
        SalidaConsola_Widget->setMinimumSize(QSize(0, 20));
        horizontalLayout_5 = new QHBoxLayout(SalidaConsola_Widget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(3, 1, -1, 1);
        InfoSalida_txt = new QPlainTextEdit(SalidaConsola_Widget);
        InfoSalida_txt->setObjectName(QStringLiteral("InfoSalida_txt"));
        InfoSalida_txt->setEnabled(true);
        sizePolicy.setHeightForWidth(InfoSalida_txt->sizePolicy().hasHeightForWidth());
        InfoSalida_txt->setSizePolicy(sizePolicy);
        InfoSalida_txt->setMinimumSize(QSize(0, 40));
        InfoSalida_txt->setMaximumSize(QSize(16777215, 400));

        horizontalLayout_5->addWidget(InfoSalida_txt);


        verticalLayout->addWidget(SalidaConsola_Widget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(false);
        menuBar->setGeometry(QRect(0, 0, 1195, 22));
        sizePolicy.setHeightForWidth(menuBar->sizePolicy().hasHeightForWidth());
        menuBar->setSizePolicy(sizePolicy);
        menuBar->setMinimumSize(QSize(0, 10));
        menuConfiguraci_n = new QMenu(menuBar);
        menuConfiguraci_n->setObjectName(QStringLiteral("menuConfiguraci_n"));
        MainWindow->setMenuBar(menuBar);

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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Monitor Serial Isiukak", Q_NULLPTR));
        actionConfigurar->setText(QApplication::translate("MainWindow", "Configurar", Q_NULLPTR));
        actionBuscar_puertos->setText(QApplication::translate("MainWindow", "Buscar puertos", Q_NULLPTR));
        grp_Joystick->setTitle(QApplication::translate("MainWindow", "Joystick", Q_NULLPTR));
        joystick_Activado_chk->setText(QApplication::translate("MainWindow", "Activado ", Q_NULLPTR));
        chk_LED_Joy_Y_Desc->setText(QApplication::translate("MainWindow", "JY_Desc", Q_NULLPTR));
        chk_LED_Joy_X_Desc->setText(QApplication::translate("MainWindow", "JX_Desc", Q_NULLPTR));
        chk_LED_Joy_Y_OutR->setText(QApplication::translate("MainWindow", "JY_OutR", Q_NULLPTR));
        chk_LED_Joy_X_OutR->setText(QApplication::translate("MainWindow", "JX_OutR", Q_NULLPTR));
        joystick_Y_lbl->setText(QApplication::translate("MainWindow", "J_Y:", Q_NULLPTR));
        joystick_X_lbl->setText(QApplication::translate("MainWindow", "J_ X:", Q_NULLPTR));
        label_34->setText(QApplication::translate("MainWindow", "Min", Q_NULLPTR));
        label_36->setText(QApplication::translate("MainWindow", "Max", Q_NULLPTR));
        Jy_Min_lbl->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        Jy_Max_lbl->setText(QApplication::translate("MainWindow", "1024", Q_NULLPTR));
        label_39->setText(QApplication::translate("MainWindow", "Min", Q_NULLPTR));
        label_40->setText(QApplication::translate("MainWindow", "Max", Q_NULLPTR));
        Jx_Min_lbl->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        Jx_Max_lbl->setText(QApplication::translate("MainWindow", "1024", Q_NULLPTR));
        grp_Botones->setTitle(QApplication::translate("MainWindow", "Botones", Q_NULLPTR));
        FixFreno_chk->setText(QApplication::translate("MainWindow", "Fix Freno", Q_NULLPTR));
        PalUp_chk->setText(QApplication::translate("MainWindow", "Pal Up", Q_NULLPTR));
        PalDown_chk->setText(QApplication::translate("MainWindow", "Pal Down", Q_NULLPTR));
        RoadMode_chk->setText(QApplication::translate("MainWindow", "Modo Road", Q_NULLPTR));
        grp_Freno->setTitle(QApplication::translate("MainWindow", "Freno", Q_NULLPTR));
        valorFreno_lbl->setText(QApplication::translate("MainWindow", "Pos:", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Des:", Q_NULLPTR));
        Freno_lblError->setText(QApplication::translate("MainWindow", "Error", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Ctrl", Q_NULLPTR));
        Freno_Inhibido_chk->setText(QApplication::translate("MainWindow", "Inhibido", Q_NULLPTR));
        label_7->setText(QString());
        Freno_Activado_chk->setText(QApplication::translate("MainWindow", "Activado", Q_NULLPTR));
        FrenoActivado_lbl->setText(QString());
        chk_LED_Freno_OutR->setText(QApplication::translate("MainWindow", "OutRnge", Q_NULLPTR));
        chk_LED_Freno_Desc->setText(QApplication::translate("MainWindow", "Desc", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "Position Limits", Q_NULLPTR));
        label_29->setText(QApplication::translate("MainWindow", "Min", Q_NULLPTR));
        label_28->setText(QApplication::translate("MainWindow", "Max", Q_NULLPTR));
        brake_PosLimits_Min_lbl->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        brake_PosLimits_Max_lbl->setText(QApplication::translate("MainWindow", "1024", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "VIN:", Q_NULLPTR));
        Brake_VIN_lbl->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "TemP: ", Q_NULLPTR));
        Brake_Temp_lbl->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Err:", Q_NULLPTR));
        Brake_Error_lbl->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        brake_ShowInfo_rBtn->setText(QApplication::translate("MainWindow", "Show Info", Q_NULLPTR));
        grp_Acelerador->setTitle(QApplication::translate("MainWindow", "Acelerador", Q_NULLPTR));
        Acel_Activado_lbl->setText(QString());
        Acel_Activado_chk->setText(QApplication::translate("MainWindow", "Activado", Q_NULLPTR));
        Acel_Inhibido_lbl->setText(QString());
        Acel_Inhibido_chk->setText(QApplication::translate("MainWindow", "Inhibido", Q_NULLPTR));
        chk_LED_Acel_OutR->setText(QApplication::translate("MainWindow", "OutRnge", Q_NULLPTR));
        valorAcelerador_lbl->setText(QApplication::translate("MainWindow", "Pos:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Des:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Error", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Ctrl:", Q_NULLPTR));
        chk_LED_Acel_Desc->setText(QApplication::translate("MainWindow", "Desc", Q_NULLPTR));
        label_30->setText(QApplication::translate("MainWindow", "Position Limits", Q_NULLPTR));
        label_31->setText(QApplication::translate("MainWindow", "Min", Q_NULLPTR));
        label_32->setText(QApplication::translate("MainWindow", "Max", Q_NULLPTR));
        Accel_PosLimits_Max_lbl->setText(QApplication::translate("MainWindow", "1024", Q_NULLPTR));
        Accel_PosLimits_Min_lbl->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "VIN:", Q_NULLPTR));
        Accel_Vin_lbl->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        Accel_Temp_lbl->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "Temp:", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Err:", Q_NULLPTR));
        Accel_Error_lbl->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        accel_ShowInfo_rBtn->setText(QApplication::translate("MainWindow", "Show Info", Q_NULLPTR));
        grp_Volante->setTitle(QApplication::translate("MainWindow", "Volante", Q_NULLPTR));
        volante_Activado_chk->setText(QApplication::translate("MainWindow", "Activado   ", Q_NULLPTR));
        volante_Inhibido_chk->setText(QApplication::translate("MainWindow", "Inhibido", Q_NULLPTR));
        VolanteModo_cmb->clear();
        VolanteModo_cmb->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "INHIBIDO", Q_NULLPTR)
         << QApplication::translate("MainWindow", "OPENLOOP_LINEAL", Q_NULLPTR)
         << QApplication::translate("MainWindow", "OPENLOOP_PARTES", Q_NULLPTR)
         << QApplication::translate("MainWindow", "OPENLOOP_EXP", Q_NULLPTR)
         << QApplication::translate("MainWindow", "CLOSEDLOOP_POS_LINEAL", Q_NULLPTR)
         << QApplication::translate("MainWindow", "CLOSEDLOOP_POS_LOG", Q_NULLPTR)
         << QApplication::translate("MainWindow", "CLOSEDLOOP_VELOCIDAD", Q_NULLPTR)
        );
        valorVolante_lbl->setText(QApplication::translate("MainWindow", "Ctrl:", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "VIN:", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "Temp:", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "Err:", Q_NULLPTR));
        Steer_Vin_lbl->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        Steer_Temp_lbl->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        Steer_Error_lbl->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        steer_ShowInfo_rBtn->setText(QApplication::translate("MainWindow", "Show Info", Q_NULLPTR));
        palanca_grp->setTitle(QApplication::translate("MainWindow", "Palanca", Q_NULLPTR));
        palanca_Activada_chk->setText(QApplication::translate("MainWindow", "Activada", Q_NULLPTR));
        palanca_Inhibida_chk->setText(QApplication::translate("MainWindow", "Inhibida", Q_NULLPTR));
        label_27->setText(QApplication::translate("MainWindow", "T:", Q_NULLPTR));
        T_lbl->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        T_max_lbl->setText(QApplication::translate("MainWindow", "100", Q_NULLPTR));
        label_35->setText(QApplication::translate("MainWindow", "T_max", Q_NULLPTR));
        label_33->setText(QApplication::translate("MainWindow", "T_min", Q_NULLPTR));
        T_min_lbl->setText(QApplication::translate("MainWindow", "25", Q_NULLPTR));
        normalDefines_chk->setText(QApplication::translate("MainWindow", "Normal Defines", Q_NULLPTR));
        logoOlin_lbl->setText(QString());
        lblEstadoSistema->setText(QApplication::translate("MainWindow", "Estado: ", Q_NULLPTR));
        estadoSistema_lbl->setText(QApplication::translate("MainWindow", "E0: OK", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_21->setToolTip(QApplication::translate("MainWindow", "Limit/Kill Switch", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_21->setText(QApplication::translate("MainWindow", "LSw", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_25->setToolTip(QApplication::translate("MainWindow", "Motor Driver Error", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_25->setText(QApplication::translate("MainWindow", "DEr", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_24->setToolTip(QApplication::translate("MainWindow", "Over Temperature", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_24->setText(QApplication::translate("MainWindow", "OvT", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_20->setToolTip(QApplication::translate("MainWindow", "Comm TimeOut", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_20->setText(QApplication::translate("MainWindow", "CTO", Q_NULLPTR));
        label_38->setText(QApplication::translate("MainWindow", "Vin", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_22->setToolTip(QApplication::translate("MainWindow", "Low Vin", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_22->setText(QApplication::translate("MainWindow", "LwV", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_23->setToolTip(QApplication::translate("MainWindow", "High Vin", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_23->setText(QApplication::translate("MainWindow", "HgV", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_17->setToolTip(QApplication::translate("MainWindow", "Safe Start Violation", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_17->setText(QApplication::translate("MainWindow", "SSV", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_18->setToolTip(QApplication::translate("MainWindow", "Required Channel Invalid", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_18->setText(QApplication::translate("MainWindow", "RCI", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_19->setToolTip(QApplication::translate("MainWindow", "Serial Error", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_19->setText(QApplication::translate("MainWindow", "SEr", Q_NULLPTR));
        label_37->setText(QApplication::translate("MainWindow", "\302\260C", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_41->setToolTip(QApplication::translate("MainWindow", "ERR Line  High", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_41->setText(QApplication::translate("MainWindow", "LHg", Q_NULLPTR));
        driversValues_txt->setPlainText(QString());
        erroresSalida_txt->setPlainText(QString());
        lblDescripcion->setText(QApplication::translate("MainWindow", "Descripci\303\263n:", Q_NULLPTR));
        cmbSerialPortSelector->clear();
        cmbSerialPortSelector->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "/dev/ttyUSB0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "/dev/ttyUSB1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "/dev/ttyUSB2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "/dev/ttyACM0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "/dev/ttyACM1", Q_NULLPTR)
        );
        btnParoEmergencia->setText(QApplication::translate("MainWindow", "Prueba de funciones", Q_NULLPTR));
        btnConectar->setText(QString());
        btnDesconectar->setText(QString());
        InfoSalida_txt->setPlainText(QString());
        menuConfiguraci_n->setTitle(QApplication::translate("MainWindow", "Configuraci\303\263n", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Sistema Conducción Joystick/Programas/ProgramasQt/SistemaConduccionJoystick_b0.8/include"
INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Sistema Conducción Joystick/Programas/ProgramasQt/SistemaConduccionJoystick_b0.8/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/SPI/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/Wire/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/SoftwareSerial/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/EEPROM/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/cores/arduino"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/variants/standard"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/HID/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/avr/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/5.4.0/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/5.4.0/include-fixed"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/tool-unity"

DEFINES += "PLATFORMIO=40100"
DEFINES += "ARDUINO_AVR_UNO"
DEFINES += "F_CPU=16000000L"
DEFINES += "ARDUINO_ARCH_AVR"
DEFINES += "ARDUINO=10808"
DEFINES += "__AVR_ATmega328P__"

OTHER_FILES += platformio.ini

HEADERS += src/DriversMotores.hpp \
    src/Config.hpp \
    src/LecturaFeedback.hpp \
    src/ComunicacionSerial.hpp \
    src/ControlPalanca.hpp \
    src/Testing.hpp
HEADERS +=
HEADERS += src/ControlPedales.hpp
HEADERS += src/ExtensorPCF.hpp
HEADERS += src/ControlVolante.hpp
HEADERS += src/PCF8574.hpp
HEADERS += src/Seguridad.hpp
HEADERS += src/Debug.hpp
HEADERS += src/DigitalFilter.hpp
HEADERS += src/LecturaEncoder.hpp

SOURCES += src/ControlActuadoresJoystick_Retro.cpp

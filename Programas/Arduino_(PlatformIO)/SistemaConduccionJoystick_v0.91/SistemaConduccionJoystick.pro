win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Sistema Conducción Joystick/Programas/PlatformIO+QtCreator/SistemaConduccionJoystick_v0.9/include"
INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Sistema Conducción Joystick/Programas/PlatformIO+QtCreator/SistemaConduccionJoystick_v0.9/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/SPI/src"
#INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/Wire/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/SoftwareSerial/src"
#INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/EEPROM/src"
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


# El orden importa.
HEADERS +=  src/Config.hpp \
            src/Debug.hpp

HEADERS +=  src/ComunicacionSerial.hpp \
src/DigitalFilter.hpp \
src/LecturaFeedback.hpp

HEADERS += src/DriversMotores.hpp \
src/ControlPalanca.hpp \
src/ControlPedales.hpp \
src/ControlVolante.hpp

HEADERS +=  src/Seguridad.hpp \
            src/Testing.hpp

SOURCES += src/ControlActuadoresJoystick_Retro.cpp

SOURCES += test/test_main.cpp

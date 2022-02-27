
win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Sistema Conducción Joystick/Documentación/Programas/Isiukak_ST/Isiukak_STM32_PlatformIO/include"
INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Sistema Conducción Joystick/Documentación/Programas/Isiukak_ST/Isiukak_STM32_PlatformIO/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/cores/arduino/avr"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/cores/arduino/stm32"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/cores/arduino/stm32/LL"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/cores/arduino/stm32/usb"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/cores/arduino/stm32/OpenAMP"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/cores/arduino/stm32/usb/hid"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/cores/arduino/stm32/usb/cdc"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/system/Drivers/STM32F4xx_HAL_Driver/Inc"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/system/Drivers/STM32F4xx_HAL_Driver/Src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/system/STM32F4xx"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/system/Middlewares/ST/STM32_USB_Device_Library/Core/Inc"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/system/Middlewares/ST/STM32_USB_Device_Library/Core/Src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/system/Middlewares/OpenAMP"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/system/Middlewares/OpenAMP/open-amp/lib/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/system/Middlewares/OpenAMP/libmetal/lib/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/system/Middlewares/OpenAMP/virtual_driver"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-cmsis/CMSIS/Core/Include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/system/Drivers/CMSIS/Device/ST/STM32F4xx/Include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/system/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-cmsis/CMSIS/DSP/Include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-cmsis/CMSIS/DSP/PrivateInclude"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/cores/arduino"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/variants/STM32F4xx/F401R(B-C-D-E)T"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/libraries/CMSIS_DSP/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/libraries/EEPROM/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/libraries/IWatchdog/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/libraries/Keyboard/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/libraries/Mouse/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/libraries/RGB_LED_TLC59731/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/libraries/SPI/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/libraries/Servo/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/libraries/SoftwareSerial/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/libraries/SrcWrapper/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoststm32/libraries/Wire/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/include/c++/9.2.1"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/include/c++/9.2.1/arm-none-eabi"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-gccarmnoneeabi/lib/gcc/arm-none-eabi/9.2.1/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-gccarmnoneeabi/lib/gcc/arm-none-eabi/9.2.1/include-fixed"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/tool-unity"

DEFINES += "PLATFORMIO=50200"
DEFINES += "STM32F4"
DEFINES += "STM32F401xE"
DEFINES += "STM32F40_41xxx"
DEFINES += "STM32F4xx"
DEFINES += "ARDUINO=10808"
DEFINES += "ARDUINO_ARCH_STM32"
DEFINES += "ARDUINO_NUCLEO_F401RE"
DEFINES += "BOARD_NAME=&quot;NUCLEO_F401RE&quot;"
DEFINES += "HAL_UART_MODULE_ENABLED"
DEFINES += "USE_FULL_LL_DRIVER"
DEFINES += "VARIANT_H=&quot;variant_NUCLEO_F401RE.h&quot;"

OTHER_FILES += platformio.ini

CONFIG += c++14

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

SOURCES += src/ControlActuadoresJoystick_Retro.cpp \
test/test_embedded.cpp

SOURCES +=

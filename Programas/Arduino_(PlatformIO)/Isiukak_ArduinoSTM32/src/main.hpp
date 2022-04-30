#ifndef MAIN_HPP
#define MAIN_HPP

#include "Seguridad.hpp"
#include "Testing.hpp"

//Variables para la medición del periodo del sistema.
long tiempoAnterior = 0, tiempoActual = 0;

uint8_t actualizacionExitosa = false;
//******************************************************************************//

bool validateDefinesNormalUse()
{
    definesNormalUse = true;
    //assert(JOYSTICK_ACTIVADO);

    // Checking defines that must be activated
    uint8_t mustBeActivated[13] = {
        JOYSTICK_ACTIVADO,
        FRENO_ACTIVADO,
        ACELERADOR_ACTIVADO,
        VOLANTE_ACTIVADO,
        PALANCA_ACTIVADA,

        INFO_JOYSTICK,
        INFO_BOTONES,
        INFO_ACTUADORES_POS,
        INFO_ACTUADORES_CONTROL,
        INFO_VOLANTE,
        INFO_PALANCA,

        INFO_MOTOR_DRIVERS,
        INFO_TIME
    };

    uint8_t mustBeDeactivated[8] = {
        JOYSTICK_VIRTUAL, EMBEDDED_TESTING, TESTING_MODE,
        ENTRADAS_VIRTUALES, VERIFICACION_ADC,
        DEBUG_BOOT, DEBUG_POTS_VALUES, DEBUG_POTS_ERROR_VALUES
    };

    uint activatedsArrayLenght  = sizeof(mustBeActivated);
    for(uint cont = 0; cont < activatedsArrayLenght; cont++)
    {
        if(!mustBeActivated[cont])
        {
            definesNormalUse = false;
            Serial.print("**Element ");
            Serial.print(cont);
            Serial.println(" of MustBeActivated Array is deactivated**");
        }
    }

    /*if(!JOYSTICK_ACTIVADO) {
        definesNormalUse = false;
        Serial.println("**Joystick Desactivado"); Serial.println("**");
    }

    if(!FRENO_ACTIVADO )
    {

    }*/

    uint deactivatedsArrayLenght  = sizeof(mustBeDeactivated);
    for(uint cont = 0; cont < deactivatedsArrayLenght; cont++)
    {
        if(mustBeDeactivated[cont])
        {
            definesNormalUse = false;
            Serial.print("**Element ");
            Serial.print(cont);
            Serial.println(" of MustBeDeactivated Array is Activated**");
        }
    }

    /*
    if(JOYSTICK_VIRTUAL) // 0 in normal use.
    {
        definesNormalUse = false;
        Serial.println("**JOYSTICK_VIRTUAL ACTIVATED**");
    }

    if(EMBEDDED_TESTING) // 0 in normal use.
    {
        definesNormalUse = false;
        Serial.println("**EMBEDDED_TESTING ACTIVATED**");
    }

    bool testingModeDisabled = !TESTING_MODE;
    //assert(testingModeDisabled);
    if(!testingModeDisabled)
    {
        definesNormalUse = false;
        Serial.println("**TESTING_MODE ACTIVATED!!!**");
    }

    bool entradasVirtualesDesactivadas = !ENTRADAS_VIRTUALES;
    //assert(entradasVirtualesDesactivadas);
    if(!entradasVirtualesDesactivadas)
    {
        definesNormalUse = false;
        Serial.println("**ENTRADAS_VIRTUALES ACTIVATED!!!**");
    }

    bool debugBootDisabled = !DEBUG_BOOT;
    if(!debugBootDisabled)
    {
        definesNormalUse = false;
        Serial.println("**DEBUG_BOOT_ACTIVATED!!!**");
    }*/


    if(timeOutSetted > timeOut) {
        definesNormalUse = false;
        Serial.println("**TimeOut Setted > TimeOut Target on smcSerial.**");
    }

    return definesNormalUse;
}



void Control(int Joystick_X, int Joystick_Y,
                uint8_t ActuadorFreno_EstaInhibido,
                uint8_t ActuadorAcelerador_EstaInhibido,
                TiposControlVolante tipoControlVolante)
{
    /*!
     *****************************************************************************************/

    // *************  *************** //

    ControlarPedales(Joystick_Y, FijarPosicionFreno, Joystick_comportamientoDirecto,
                     ActuadorFreno_EstaInhibido, ActuadorAcelerador_EstaInhibido);


    ControlarVolante(Joystick_X, tipoControlVolante);


    ControlPalanca(ActuadorFreno_Posicion);
}

void setUnusedPins_input_pullDown()
{
    /*STM32 datasheet recommends to set all unused pins
     * to reduce consumption
    As input with pull-up or pull-down resistor or
    As output if EM noise is an issue for the application.*/

    pinMode(D6, INPUT_PULLDOWN); //PB_10
    /*
    pinMode(PB_13, INPUT_PULLDOWN); //MORPHO_CN10_30
    pinMode(PB_14, INPUT_PULLDOWN); //MORPHO_CN10_28
    pinMode(PB_15, INPUT_PULLDOWN); //MORPHO_CN10_26
    pinMode(PB_1, INPUT_PULLDOWN); //MORPHO_CN10_24
    pinMode(PB_2, INPUT_PULLDOWN); //MORPHO_CN10_22
    pinMode(PB_12, INPUT_PULLDOWN); //MORPHO_CN10_16
    pinMode(PA_11, INPUT_PULLDOWN); //MORPHO_CN10_14
    pinMode(PA_12, INPUT_PULLDOWN); //MORPHO_CN10_12
    pinMode(PC_5, INPUT_PULLDOWN); //MORPHO_CN10_6
    pinMode(PC_6, INPUT_PULLDOWN); //MORPHO_CN10_4
    pinMode(PC_8, INPUT_PULLDOWN); //MORPHO_CN10_2

    MORPHO_CN7
    PA13(3) Checar cuál es la nota
    PA (3) ídem
    pinMode(PC10, INPUT_PULLDOWN);
    pinMode(PD12, INPUT_PULLDOWN);
    pinMode(PA15, INPUT_PULLDOWN);
    pinMode(PB7, INPUT_PULLDOWN);
    pinMode(PC13, INPUT_PULLDOWN);
    pinMode(PC14, INPUT_PULLDOWN);
    pinMode(PC15, INPUT_PULLDOWN);
    pinMode(PH0, INPUT_PULLDOWN);
    pinMode(PH1, INPUT_PULLDOWN);
    pinMode(PC2, INPUT_PULLDOWN);
    pinMode(PC3, INPUT_PULLDOWN);
    */
}

void configurarPines()
{
    // Com Serial USB
    // RX: D0, PA_3
    // TX: D1, PA_2

    // Com serial Drivers
    // RX: D2, PA_10
    // TX: D8, PA_9

    pinMode(pinJoystickY, INPUT_ANALOG);    //A0; //PA0
    pinMode(pinJoystickX, INPUT_ANALOG);    //A1; //PA1
    pinMode(pinActFreno, INPUT_ANALOG);     //A2; //PA4
    pinMode(pinActAcel, INPUT_ANALOG);      //A3; //PB0


    pinMode(pinVDDVirtual, OUTPUT);         //D3; //PB3;
    pinMode(pinGNDVirtual, OUTPUT);         //D7; //PA8;

    pinMode(pinOutput_PalancaBajar, OUTPUT);    //D4; //PB5
    pinMode(pinOutput_PalancaSubir, OUTPUT);    //D5; //PB4
    digitalWrite(pinOutput_PalancaBajar, LOW);
    digitalWrite(pinOutput_PalancaSubir, LOW);

    pinMode(pinAGND, OUTPUT);            //D12; //PA6
    pinMode(pinAVDD, OUTPUT);            //D13; //PA5
    digitalWrite(pinAGND, LOW);
    digitalWrite(pinAVDD, HIGH);

    pinMode(pinBotonParoEmergencia, INPUT_PULLUP);  //D9; //PC7

    // The buttons have external pullup resistors
    pinMode(pinFijarPosicionFreno, INPUT);  //D10; //PB6
    pinMode(pinBajarPalanca,  INPUT);       //D11; //PA7
    pinMode(pinSubirPalanca,  INPUT);       //       PC2 (Morpho only);
    pinMode(pinModoCarretera, INPUT);       //       PC3 (Morpho only);
    // FIXME: A. Validar si activar PullUps internas modifica la lectura del ADC.

    //TODO: C. //setUnusedPins_input_pullDown();

    //pinMode(pin_encendido, INPUT_PULLUP); //Por defecto en alto

    //analogReference(EXTERNAL);
    //EXTERNAL: the voltage applied to AVDD and AGND (0 to 3.3V only).
    //En el STM32 F401RE sólo puede haber referencia externa para el ADC.

    /*GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    //GPIO_InitStruct.Pin = pinBotonParoEmergencia;
    //GPIO_InitStruct.Mode =
    //GPIO_InitStruct.Pull = GPIO_PULLUP;
    //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    //GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
    //HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); */
}

void displayInfo()
{
    desplegarInfoJoystick();
    desplegarInfoBotones();

    desplegarInfoPedales();
    desplegarInfoMotorDrivers();

    desplegarInfoVolante();
    desplegarInfoPalanca(ActuadorFreno_Posicion);


    desplegarInfoEstadoSistema();
}

void desplegarInfoArranque()
{

#if JOYSTICK_ACTIVADO
    Serial.print("**Modo Operación Joystick: ");
    if(Joystick_comportamientoDirecto)
    {
        Serial.println("Directo. **");
    }
    else
    {
        Serial.println("Inverso. **");
    }
#else
    Serial.println("**EL JOYSTICK NO ESTÁ ACTIVADO");
#endif

#if FRENO_ACTIVADO //Usar ! para negar la constante no funciona como con una variable normal.
    Serial.println("**El Freno está Activado.**");
#else
    Serial.println("**¡EL FRENO NO ESTÁ ACTIVADO!**");
#endif

#if ACELERADOR_ACTIVADO
    Serial.println("**El Acelerador está Activado.**");
#else
    Serial.println("**¡EL ACELERADOR NO ESTÁ ACTIVADO!**");
#endif

#if EMBEDDED_TESTING
    Serial.println("**EMBEDDED TESTING**");

#endif

#if TESTING_MODE
    calculate_IterationsPerActuator(periodoDeseado);
    Serial.println("**TESTING MODE**");
#endif

#if JOYSTICK_VIRTUAL
    Serial.println("**JOYSTICK VIRTUAL**");
#endif

#if ENTRADAS_VIRTUALES
    Serial.println("**ENTRADAS VIRTUALES**");
#endif

#if VALIDAR_LIMITES_JOYSTICK
    Serial.println("**Validando_Limites_Joystick**");
#else
    Serial.println("**NO_VALINDANDO_LIMITES_JOYSTICK**");
#endif

#if VALIDAR_LIMITES_ACTUADORES
    Serial.println("**Validando_Limites_Actuadores**");
#else
    Serial.println("**NO_VALINDANDO_LIMITES_ACTUADORES**");
#endif

#if DEBUG_CONTROL_VOLANTE_UMBRALES
    Serial.println("Corroborando valores de control por segmentos para Joystick y Actuación del volante");
    Serial.print("porcentControlPuente_Seg1:  ");
    Serial.println(porcentControlPuente_Seg1);//Segmento1
    Serial.print("ControlVolante_IzqSeg1: ");
    Serial.println(ControlVolante_IzqSeg1);
    Serial.print("ControlVolante_DerSeg1");
    Serial.println(ControlVolante_DerSeg1);

    Serial.print("joy_percentSegmento1: ");
    Serial.println(joy_percentSegmento1);
    Serial.print("joyIzq_Segmento1: ");
    Serial.println(joyIzq_Segmento1);
    Serial.print("joyDer_Segmento1: ");
    Serial.println(joyDer_Segmento1);
    delay(2000);
#endif

    Serial.print("**Periodo verificación: ");   Serial.print(periodoVerificacion);    Serial.println("**");
    Serial.print("**Periodo Deseado: ");        Serial.print(periodoDeseado);       Serial.println("**");
    Serial.print("**Cantidad de iteraciones para verificación: "); Serial.print(cantidadIteracionesParaVerificacion); Serial.println("**");
    Serial.print("**TimeOut setted for smcSerial: "); Serial.print(timeOutSetted); Serial.println("**");
}



void displayInfoTime()
{
    #if INFO_TIME
    long diferencia = tiempoActual - tiempoAnterior;
    Serial.print(",\tT:"); Serial.print(diferencia);
    #endif
    Serial.println(" ");
    tiempoAnterior = tiempoActual;
}

#endif // MAIN_HPP

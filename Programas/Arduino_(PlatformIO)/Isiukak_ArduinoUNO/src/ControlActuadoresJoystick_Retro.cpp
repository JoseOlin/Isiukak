/*****************************************************************************

La configuración general del sistema puede consultarse en README.md

******************************************************************************/

#include "Seguridad.hpp"
#include "Testing.hpp"

//****************************** Variables de programa *************************//
/*int pinJoystickY = A0;
int pinJoystickX = A1;
int pinActFreno  = A2;
int pinActAcel   = A3;

int pinFijarPosicionFreno = 10; //10
int pinSubirPalanca = A5; //A5
int pinBajarPalanca = 11; //11
int pinModoCarretera = A4; //A4

int pinBotonParoEmergencia = 9;

*/

//Variables para la medición del periodo del sistema.
long tiempoAnterior = 0, tiempoActual = 0;

boolean actualizacionExitosa = false;
//******************************************************************************//


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

void configurarPines()
{
    analogReference(EXTERNAL);
    //DEFAULT: the default analog reference of 5 volts (on 5V Arduino boards) or 3.3 volts (on 3.3V Arduino boards)
    //EXTERNAL: the voltage applied to the AREF pin (0 to 5V only).

    pinMode(pinBotonParoEmergencia, INPUT_PULLUP); //Configurar el pin por defecto en alto.

    pinMode(pin5VVirtual, OUTPUT);
    pinMode(pinGNDVirtual, OUTPUT);

    pinMode(pinFijarPosicionFreno, INPUT);
    pinMode(pinSubirPalanca, INPUT);
    pinMode(pinBajarPalanca, INPUT);
    pinMode(pinModoCarretera, INPUT);

    pinMode(pinOutput_PalancaBajar, OUTPUT);
    pinMode(pinOutput_PalancaSubir, OUTPUT);
    digitalWrite(pinOutput_PalancaBajar, LOW);
    digitalWrite(pinOutput_PalancaSubir, LOW);

    //pinMode(pin_encendido, INPUT_PULLUP); //Por defecto en alto
}

void desplegarInfoArranque()
{
    Serial.print("**Modo Operación Joystick: ");

    if(Joystick_comportamientoDirecto)
    {
        Serial.println("Directo. **");
    }
    else
    {
        Serial.println("Inverso. **");
    }

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


#if DEBUG_CONTROL_VOLANTE_UMBRALES
    //Serial.print("JoyIzq_Medio: "); Serial.println(joyIzquierdaMedio);
    //Serial.print("JoyDer_Medio: "); Serial.println(joyDerechaMedio);

    //Serial.print("JoyIzq_2/3: "); Serial.println(joyIzqDosTer);
    //Serial.print("JoyDer_2/3: "); Serial.println(joyDerDosTer);


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

    Serial.print("**Periodo verificación: "); Serial.println(periodoVerificacion);
    Serial.print("**Periodo Deseado: "); Serial.println(periodoDeseado);
    Serial.print("**Cantidad de iteraciones para verificación: "); Serial.println(cantIteracionesParaVerificacion);
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

void displayInfo()
{
    desplegarInfoJoystick();
    desplegarInfoBotones();

    desplegarInfoPedales();

    desplegarInfoVolante();
    desplegarInfoPalanca(ActuadorFreno_Posicion);

    desplegarInfoEstadoSistema();
}


void setup()
{
    /// TODO: Portar a Infineon.

    //Serial.begin(38400);
    Serial.begin(115200);
    Serial.println("Comunicación Serial Iniciada.");
    //smcSerial.begin(19200);
    smcSerial.begin(9600); // Se probó con 19200 y funciona.
    /// TODO: Investigar si menor velocidad Serial es menos exigente para el micro.

    configurarPines();

    Pots_verificacion_activarVoltajeVirtual();

    Feedback_fillBuffer();

    // Verificación de seguridad al arranque.
    /*
    erroresArranque = verificacionSeguridad_Boot();
    if(erroresArranque)
    {
        Serial.println("**Se detectaron errores durante el arranque.**");
    }
    while(erroresArranque)
    {
        erroresArranque = verificacionSeguridad_Boot();
        aplicarRutinasSeguridad_boot(Joystick_Centrado, EstadoDelSistema);
        feedbackOnly();
    }
    */

#if VOLANTE_ACTIVADO
    volante_Desinhibir();
#endif

    tiempoAnterior = millis();

    desplegarInfoArranque();
}

void loop()
{

    tiempoActual = millis();
    if ( (tiempoActual - tiempoAnterior) >= periodoDeseado )
    {

        BotonParoEmergenciaPulsado = leerBotonParoEmergencia();

        if(!BotonParoEmergenciaPulsado)
        {
        #if JOYSTICK_VIRTUAL
            // Asignación virtual sólo de valores para los pots y botones del joystick.
        #elif EMBEDDED_TESTING
            EmbeddedTest_SetInputs();
            //Testing_VerificacionSeguridad_SetValues(); //Se hace dedntro de EmbeddedTest_SetInputs()

            leerFeedback_Virtual(LOW, LOW, LOW, LOW);
            Actuadores_Feedback_Leer();
        #else
            leerFeedback();
            aplicarModoCarretera(ModoCarreteraActivado);

            verificacionSeguridad_Constante(Potenciometros_EnRangoValido); // Invoca Potenciometros_EstanEnRango
            verificacionSeguridad_Periodica(Potenciometros_Conectados);    // VerificarConexionPotenciometros
        #endif

            /*aplicarRutinasSeguridad(
                        Joystick_X_Conectado, Joystick_Y_Conectado,
                        ActuadorAcelerador_Conectado, ActuadorFreno_Conectado,

                        Joystick_X_EnRango,   Joystick_Y_EnRango,
                        ActuadorAcelerador_EnRango, ActuadorFreno_EnRango,

                        EstadoDelSistema,
                        ActuadorAcelerador_EstaInhibido, ActuadorFreno_EstaInhibido);
            */
            // FIXME: Desactivadas para pruebas con los drivers

            Control(Joystick_X, Joystick_Y,
                    ActuadorFreno_EstaInhibido, ActuadorAcelerador_EstaInhibido, TipoControlVolante);

            displayInfo();
        }
        else
        {
            ParoBotonEmergencia();
        }

        displayInfoTime();
    }
}









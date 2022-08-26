/*****************************************************************************

La configuración general del sistema puede consultarse en README.md

******************************************************************************/
#include "main.hpp"

//****************************** Variables de programa *************************//


void setup()
{
    commInit();

    Drivers_setIterationsToRead(periodoDeseado);

    configurarPines();

    Pots_verificacion_activarVoltajeVirtual();

    Feedback_fillBuffer();

    // Verificación de seguridad al arranque.
#if DEBUG_BOOT
    delay(2000); // Tiempo para permitir que arranque el monitor serial y leer errores al arranque.
    // En la Dell Vostro este parece y con el ST Nucleo este fue el menor valor posible (con 500 ya no detecta).
    Serial.print("***DEBUG_BOOT ACTIVADO***");
#endif

#if VERIFICACION_ADC
    delay(2000);
    #if JOYSTICK_ACTIVADO
        Joystick_Leer();
        desplegarInfoJoystick_Raw();
    #endif
    #if FRENO_ACTIVADO
        Actuadores_Feedback_Leer();
        desplegarInfoPedales_Raw();
    #endif

    int delayLecturaLenta = 7000;
    verificacionManualADC(Potenciometros_Conectados, delayLecturaLenta);

    #if JOYSTICK_ACTIVADO
        Joystick_Leer();
        desplegarInfoJoystick_Raw();
    #endif
    #if FRENO_ACTIVADO
        Actuadores_Feedback_Leer();
        desplegarInfoPedales_Raw();
    #endif

    Serial.println("\nFin de la verifición de pots");
    delay(delayLecturaLenta);
#endif

#if VOLANTE_ACTIVADO
    volante_Desinhibir();
#endif

    desplegarInfoArranque();

    //TO-DO: Add function to check that the right defines are activated for normal use.
    if(!validateDefinesNormalUse() )
    {
        Serial.println("**NOT ALL DEFINES FOR NORMAL USE ARE SETTED!!!**");
    }

    #if TESTING_EMBEDDED
    calculate_IterationsPerActuator(periodoDeseado);
    #endif

    tiempoAnterior = millis();
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
            // Asignación de valores sólo para los pots y botones del joystick.
        #elif TESTING_EMBEDDED
            EmbeddedTest_SetInputs_and_Status();
            //Testing_VerificacionSeguridad_SetValues(); //Se hace dedntro de EmbeddedTest_SetInputs()

            leerFeedback_Virtual(LOW, LOW, LOW, LOW);
            Actuators_Feedback_Read(); // Esto es necesario en Testing embedded para verificar posiciones de los actuadores.
            Actuators_Drivers_Read();

        #else
            leerFeedback();
            aplicarModoCarretera(ModoCarreteraActivado);

            verificacionSeguridad_Constante(Potenciometros_EnRangoValido); // Invoca Potenciometros_EstanEnRango
            verificacionSeguridad_Periodica(Potenciometros_Conectados);    // VerificarConexionPotenciometros

        #endif
            readTemperatures();
            aplicarRutinasSeguridad(
                Joystick_X_Conectado, Joystick_Y_Conectado,
                ActuadorAcelerador_Conectado, ActuadorFreno_Conectado,

                Joystick_X_EnRango,   Joystick_Y_EnRango,
                ActuadorAcelerador_EnRango, ActuadorFreno_EnRango,

                EstadoDelSistema,
                ActuadorAcelerador_EstaInhibido, ActuadorFreno_EstaInhibido);

            Control(Joystick_X, Joystick_Y,
                ActuadorFreno_EstaInhibido,
                ActuadorAcelerador_EstaInhibido,
                TipoControlVolante);

            displayInfo();
        }
        else
        {
            ParoBotonEmergencia();
        }

        displayInfoTime();
    }
}









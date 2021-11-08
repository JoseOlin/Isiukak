#ifndef TESTING_HPP
#define TESTING_HPP

#include "Seguridad.hpp"

// Definir una secuencia de control.

/****************************************************************************************
 *   En caso de que la constante TESTING_MODE esté activada en Config.hpp
 * La función void Leer_Joystick_Virtual() asigna valores específicos del joystick para
 * validar el comportamiento del sistema.
 *
 * *************************************************************************************/

uint16_t contTesting = 0;
uint8_t Testing_ReiniciarPrueba = false;


///* Variables para testing del Comportamiento normal del sistema. *///
uint16_t Testing_tiempo_AceleradorActivado = 3000; //ms
uint16_t Testing_tiempo_FrenoActivado = 3000; //
uint16_t Testing_tiempo_VolanteIzqActivado = 3600;
uint16_t Testing_tiempo_VolanteInhibido = 2000;
uint16_t Testing_tiempo_VolanteDerActivado = 3600;
uint16_t Testing_tiempo_PalancaEnExtension = 3000;
uint16_t Testing_tiempo_PalancaEnRetraccion = 3500;


///* Variables para testing del Comportamiento en error del sistema. *///
uint16_t Testing_tiempoJoystickY_Desconectado = 5000;
uint16_t Testing_tiempoJoystickX_Desconectado = 5000;
uint16_t Testing_tiempoJoystick_Desconectado = 5000;
uint16_t Testing_tiempoActuadorFreno_Desconectado = 5000;
uint16_t Testing_tiempoActuadorAcelerador_Desconectado = 5000;
uint16_t Testing_tiempoActuadores_Desconectados = 5000;

uint16_t Testing_tiempoJoystickY_FueraRango = 5000;
uint16_t Testing_tiempoJoystickX_FueraRango = 5000;
uint16_t Testing_tiempoJoystick_FueraRango = 5000;
uint16_t Testing_tiempoActuadorFreno_FueraRango = 5000;
uint16_t Testing_tiempoActuadorAcelerador_FueraRango = 5000;
uint16_t Testing_tiempoActuadores_FueraRango = 5000;

uint16_t Testing_tiempoReiniciarPrueba = 3000;

uint16_t Testing_nIteraciones_aceleradorActivado;
uint16_t Testing_nIteraciones_frenoActivado;
uint16_t Testing_nIteraciones_volanteIzquierda;
uint16_t Testing_nIteraciones_volanteInhibido;
uint16_t Testing_nIteraciones_volanteDerecha;

uint16_t Testing_nIteraciones_JoystickY_Desconectado;
uint16_t Testing_nIteraciones_JoystickX_Desconectado;
uint16_t Testing_nIteraciones_Joystick_Desconectado;
uint16_t Testing_nIteraciones_ActuadorFreno_Desconectado;
uint16_t Testing_nIteraciones_ActuadorAcelerador_Desconectado;
uint16_t Testing_nIteraciones_Actuadores_Desconectados;

uint16_t Testing_nIteraciones_JoystickY_FueraRango;
uint16_t Testing_nIteraciones_JoystickX_FueraRango;
uint16_t Testing_nIteraciones_Joystick_FueraRango;
uint16_t Testing_nIteraciones_ActuadorFreno_FueraRango;
uint16_t Testing_nIteraciones_ActuadorAcelerador_FueraRango;
uint16_t Testing_nIteraciones_Actuadores_FueraRango;

uint16_t Testing_nIteraciones_ReiniciandoPrueba;

///* Variables para registrar los casos que ya se probaron

/* Actuadores en condiciones normales, usando Joystick virtual. */
uint8_t Testing_Acelerador_Probado = false;
uint8_t Testing_Freno_Probado = false;
uint8_t Testing_VolanteIzquierda_Probado = false;
uint8_t Testing_VolanteInhibido_Probado = false;
uint8_t Testing_VolanteDerecha_Probado = false;
uint8_t Testing_Palanca_Probada = false;

/* Potenciómetros desconectados */
uint8_t Testing_JoystickX_Desconectado_Probado = false;
uint8_t Testing_JoystickY_Desconectado_Probado = false;
uint8_t Testing_Joystick_Desconectado_Probado = false; // Ambos Ejes
uint8_t Testing_ActuadorFreno_Desconectado_Probado = false;
uint8_t Testing_ActuadorAcelerador_Desconectado_Probado = false;
uint8_t Testing_Actuadores_Desconectados_Probado = false;

/* Joystick Fuera de Rango */
uint8_t Testing_JoystickY_FueraRango_Probado = false;
uint8_t Testing_JoystickX_FueraRango_Probado = false;
uint8_t Testing_Joystick_FueraRango_Probado = false; // Ambos Ejes

/* Actuadores Fuera de Rango */
uint8_t Testing_ActuadorFreno_FueraRango_Probado = false;
uint8_t Testing_ActuadorAcelerador_FueraRango_Probado = false;
uint8_t Testing_Actuadores_FueraRango_Probado = false; // Ambos

uint8_t Testing_ReiniciarPrueba_Probado = false;

void calculate_IterationsPerActuator(uint8_t periodoDeseado)
{
    Testing_nIteraciones_aceleradorActivado = Testing_tiempo_AceleradorActivado / periodoDeseado;
    Testing_nIteraciones_frenoActivado      = Testing_tiempo_FrenoActivado / periodoDeseado;
    Testing_nIteraciones_volanteIzquierda   = Testing_tiempo_VolanteIzqActivado / periodoDeseado;
    Testing_nIteraciones_volanteInhibido    = Testing_tiempo_VolanteInhibido / periodoDeseado;
    Testing_nIteraciones_volanteDerecha     = Testing_tiempo_VolanteDerActivado / periodoDeseado;


    Testing_nIteraciones_JoystickY_Desconectado             = Testing_tiempoJoystickY_Desconectado / periodoDeseado;
    Testing_nIteraciones_JoystickX_Desconectado             = Testing_tiempoJoystickX_Desconectado / periodoDeseado;
    Testing_nIteraciones_Joystick_Desconectado              = Testing_tiempoJoystick_Desconectado / periodoDeseado;
    Testing_nIteraciones_ActuadorFreno_Desconectado         = Testing_tiempoActuadorFreno_Desconectado / periodoDeseado;
    Testing_nIteraciones_ActuadorAcelerador_Desconectado    = Testing_tiempoActuadorAcelerador_Desconectado / periodoDeseado;
    Testing_nIteraciones_Actuadores_Desconectados           = Testing_tiempoActuadores_Desconectados / periodoDeseado;

    Testing_nIteraciones_JoystickY_FueraRango           = Testing_tiempoJoystickY_FueraRango / periodoDeseado;
    Testing_nIteraciones_JoystickX_FueraRango           = Testing_tiempoJoystickX_FueraRango / periodoDeseado;
    Testing_nIteraciones_Joystick_FueraRango            = Testing_tiempoJoystick_FueraRango / periodoDeseado;
    Testing_nIteraciones_ActuadorFreno_FueraRango       = Testing_tiempoActuadorFreno_FueraRango / periodoDeseado;
    Testing_nIteraciones_ActuadorAcelerador_FueraRango  = Testing_tiempoActuadorAcelerador_FueraRango / periodoDeseado;
    Testing_nIteraciones_Actuadores_FueraRango          = Testing_tiempoActuadores_FueraRango / periodoDeseado;

    Testing_nIteraciones_ReiniciandoPrueba  = Testing_tiempoReiniciarPrueba / periodoDeseado;
}


void Testing_Joystick_Pots_Virtual(int Joystick_Y, int Joystick_X)
{
    PotenciometrosVirtuales[0] = Joystick_Y;
    PotenciometrosVirtuales[1] = Joystick_X;
    //PotenciometrosVirtuales[2] = ActuadorFreno_valorRetraido;
    //PotenciometrosVirtuales[3] = ActuadorAcelerador_valorExtendido;
}

void Testing_AsignarEntradasVirtuales_Desconexion(uint16_t pot0_low, uint16_t pot1_low, uint16_t pot2_low, uint16_t pot3_low,
                                                  uint16_t pot0_high, uint16_t pot1_high, uint16_t pot2_high, uint16_t pot3_high)
{

    PotenciometrosVirtuales_ValidacionConexion[0][0] = pot0_low;
    PotenciometrosVirtuales_ValidacionConexion[0][1] = pot1_low;
    PotenciometrosVirtuales_ValidacionConexion[0][2] = pot2_low;
    PotenciometrosVirtuales_ValidacionConexion[0][3] = pot3_low;

    PotenciometrosVirtuales_ValidacionConexion[1][0] = pot0_high;
    PotenciometrosVirtuales_ValidacionConexion[1][1] = pot1_high;
    PotenciometrosVirtuales_ValidacionConexion[1][2] = pot2_high;
    PotenciometrosVirtuales_ValidacionConexion[1][3] = pot3_high;
}
void Testing_Joystick_Buttons_Virtual(
        uint8_t subirPalanca, uint8_t bajarPalanca, uint8_t fijarPosicionFreno, uint8_t modoCarretera)
        //uint8_t &SubirPalanca, uint8_t &BajarPalanca, uint8_t &FijarPosicionFreno, uint8_t &ModoCarreteraActivado)
{

    SubirPalanca = subirPalanca;
    BajarPalanca = bajarPalanca;
    FijarPosicionFreno = fijarPosicionFreno;
    ModoCarreteraActivado = modoCarretera;
}

void Testing_ActualizarContador(uint16_t &contadorIteraciones,
                                uint16_t nIteraciones,
                                uint8_t &elementoProbado)
{
    if(contadorIteraciones >= nIteraciones)
    {
        elementoProbado = true;
        contadorIteraciones = 0;
    }
}


void Testing_VerificacionSeguridad_SetValues(
        uint8_t joyst_X_Conectado, uint8_t joyst_Y_Conectado,
        uint8_t acelerador_Conectado, uint8_t freno_Conectado,

        uint8_t joyst_X_EnRango, uint8_t joys_Y_EnRango,
        uint8_t acelerador_EnRango, uint8_t freno_EnRango
        )
{
    Joystick_X_Conectado = joyst_X_Conectado;
    Joystick_Y_Conectado = joyst_Y_Conectado;
    Joystick_Conectado = joyst_X_Conectado && joyst_Y_Conectado;

    ActuadorFreno_Conectado = freno_Conectado;
    ActuadorAcelerador_Conectado = acelerador_Conectado;
    Actuadores_Conectados = freno_Conectado && acelerador_Conectado;

    Potenciometros_Conectados = Joystick_Conectado && Actuadores_Conectados;


    Joystick_X_EnRango = joyst_X_EnRango;
    Joystick_Y_EnRango = joys_Y_EnRango;
    Joystick_EnRango = joyst_X_EnRango && joys_Y_EnRango;

    ActuadorAcelerador_EnRango = acelerador_EnRango;
    ActuadorFreno_EnRango = freno_EnRango;
    Actuadores_EnRango = acelerador_EnRango && freno_EnRango;

    Potenciometros_EnRangoValido = Joystick_EnRango && Actuadores_EnRango;

    //uint8_t Potenciometros_EnRangoValido = false;
}

/*void EmbeddedTest_SetInputs()
{
    if(contTesting == 0)
    {
        Serial.println("Starting embedded testing with virtual values for safety routines..");
        Serial.println("THIS TEST SHALL ONLY MADE WITH ISIUKAK UNINSTALLED FROM THE CAR.");
    }


}*/
void Joystick_Leer_Virtual()
{
    int joystick1_Y = PotenciometrosVirtuales[0];
    int joystick1_X = PotenciometrosVirtuales[1];

    /// Aplicar filtrado
    smoothJS_Y = digitalSmooth(joystick1_Y, joy_Y_SmoothArray);
    Joystick_Y = smoothJS_Y;

    smoothJS_X = digitalSmooth(joystick1_X, joy_X_SmoothArray);
    Joystick_X = smoothJS_X;
}


void EmbeddedTest_SetInputs()
{
/*! The embedded test assigns virtual values for the joystick (pots and buttons)
  * virtual Safety checking function to define which pots are connected and which aren't
  *
  *
  *
  **************************************************************************************/
    uint8_t joyst_X_Conectado = true,  joyst_Y_Conectado = true;
    uint8_t acelerador_Conectado = true,  freno_Conectado = true;
    uint8_t joyst_X_EnRango = true,  joys_Y_EnRango = true;
    uint8_t acelerador_EnRango = true, freno_EnRango = true;

    uint8_t palancaDown = LOW, palancaUp = LOW, brakePositionFixed = LOW, fullGasMode = LOW;

    if(contTesting == 0)
    {
        Serial.println("Iniciando la prueba con valores virtuales del Joystick.");
        Serial.println("ESTA PRUEBA DEBE HACERSE CON EL SISTEMA DESINSTALADO DEL CARRO.");
    }

    // Activar el ACELERADOR A FULL durante n_a iteraciones
    if(contTesting <= Testing_nIteraciones_aceleradorActivado && !Testing_Acelerador_Probado)
    {
        if(contTesting == 1) {
            Serial.println("**Testing Acelerador a full...**");
        }
        Testing_Joystick_Pots_Virtual(joyY_MinVal, joyX_Center);


        Testing_Joystick_Buttons_Virtual(
            palancaUp = LOW, palancaDown = LOW, brakePositionFixed = LOW, fullGasMode = LOW);

        Testing_VerificacionSeguridad_SetValues(
                joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                acelerador_Conectado = true,  freno_Conectado = true,

                joyst_X_EnRango = true,  joys_Y_EnRango = true,
                acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_nIteraciones_aceleradorActivado, Testing_Acelerador_Probado);
    }

    // Activar el FRENO A FULL durante n_f iteraciones
    else if(contTesting <= Testing_nIteraciones_frenoActivado && !Testing_Freno_Probado)
    {
        if(contTesting == 1) {
            Serial.println("**Testing Freno a full...**");
        }
        Testing_Joystick_Pots_Virtual(joyY_MaxVal, joyX_Center);
        //Testing_VerificacionSeguridad_SetValues() // No modificar las variables de conexión

        Testing_ActualizarContador(contTesting, Testing_nIteraciones_frenoActivado, Testing_Freno_Probado);
    }

    // Activar el VOLANTE HACIA LA IZQUIERDA durante n_i iteraciones
    else if(contTesting <= Testing_nIteraciones_volanteIzquierda && !Testing_VolanteIzquierda_Probado)
    {
        if(contTesting == 1) {
            Serial.println("**Testing Volante a la izquierda a full...**");
        }
        Testing_Joystick_Pots_Virtual(joyY_Center, joyX_MinVal);
        // Testing_VerificacionSeguridad_SetValues //No modificar las variables de conexión

        Testing_ActualizarContador(contTesting, Testing_nIteraciones_volanteIzquierda, Testing_VolanteIzquierda_Probado);
    }

    // No actuar el volante durante nIteraciones
    else if(contTesting <= Testing_nIteraciones_volanteInhibido && !Testing_VolanteInhibido_Probado)
    {
        if(contTesting == 1)
        {
            Serial.println("**Testing Volante sin actuar...**");
        }
        Testing_Joystick_Pots_Virtual(joyY_Center, joyX_Center);
        // Testing_VerificacionSeguridad_SetValues //No modificar las variables de conexión

        Testing_ActualizarContador(contTesting, Testing_nIteraciones_volanteInhibido, Testing_VolanteInhibido_Probado);
    }

    // Activar el volante a la derecha a full durante n_d iteraciones
    else if(contTesting <= Testing_nIteraciones_volanteDerecha && !Testing_VolanteDerecha_Probado)
    {
        if(contTesting == 1)
        {
            Serial.println("**Testing Volante a la derecha...**");
        }
        Testing_Joystick_Pots_Virtual(joyY_Center, joyX_MaxVal);
        // Testing_VerificacionSeguridad_SetValues //No modificar las variables de conexión.

        Testing_ActualizarContador(contTesting, Testing_nIteraciones_volanteDerecha, Testing_VolanteDerecha_Probado);
    }

    // Testing Joystick Y disconnected.
    else if(contTesting <= Testing_nIteraciones_JoystickY_Desconectado && !Testing_JoystickY_Desconectado_Probado)
    {
        if(contTesting == 1) {
            Serial.println("**Testing Joystick Y Desconectado...**");
        }
        Testing_Joystick_Pots_Virtual(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                joyst_X_Conectado = true,
                joyst_Y_Conectado = false, //  <----------
                acelerador_Conectado = true,  freno_Conectado = true,

                joyst_X_EnRango = true,  joys_Y_EnRango = true,
                acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_nIteraciones_JoystickY_Desconectado, Testing_JoystickY_Desconectado_Probado);
    }

    // Testing Joystick X disconnected.
    else if(contTesting <= Testing_nIteraciones_JoystickX_Desconectado && !Testing_JoystickX_Desconectado_Probado)
    {
        if(contTesting == 1)  {
            Serial.println("**Testing Joystick X Desconectado...**");
        }
        Testing_Joystick_Pots_Virtual(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                joyst_X_Conectado = false, // <----------
                joyst_Y_Conectado = true,
                acelerador_Conectado = true,  freno_Conectado = true,

                joyst_X_EnRango = true,  joys_Y_EnRango = true,
                acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting,
                                   Testing_nIteraciones_JoystickX_Desconectado,
                                   Testing_JoystickX_Desconectado_Probado);

    }

    // Testing Joystick disconnected.
    else if(contTesting <= Testing_nIteraciones_Joystick_Desconectado && !Testing_Joystick_Desconectado_Probado)
    {
        if(contTesting == 1) {
            Serial.println("**Testing Joystick Desconectado (Ambos ejes)...**");
        }
        Testing_Joystick_Pots_Virtual(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                joyst_X_Conectado = false,  // <----------
                joyst_Y_Conectado = false, // <----------
                acelerador_Conectado = true,  freno_Conectado = true,

                joyst_X_EnRango = true,  joys_Y_EnRango = true,
                acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_nIteraciones_Joystick_Desconectado, Testing_Joystick_Desconectado_Probado);

    }

    // Testing Freno Desconectado.
    else if(contTesting <= Testing_nIteraciones_ActuadorFreno_Desconectado && !Testing_ActuadorFreno_Desconectado_Probado)
    {
        if(contTesting == 1) {
            Serial.println("**Testing Freno Desconectado...**");
        }
        Testing_Joystick_Pots_Virtual(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = true,
                    freno_Conectado = false, // <----------

                    joyst_X_EnRango = true,  joys_Y_EnRango = true,
                    acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_nIteraciones_ActuadorFreno_Desconectado, Testing_ActuadorFreno_Desconectado_Probado);

    }

    // Testing Acelerador Desconectado
    else if(contTesting <= Testing_nIteraciones_ActuadorAcelerador_Desconectado && !Testing_ActuadorAcelerador_Desconectado_Probado)
    {
        if(contTesting == 1)
        {
            Serial.println("**Testing Acelerador Desconectado...**");
        }
        Testing_Joystick_Pots_Virtual(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = false,  // <---------------
                    freno_Conectado = true,

                    joyst_X_EnRango = true,  joys_Y_EnRango = true,
                    acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_nIteraciones_ActuadorAcelerador_Desconectado, Testing_ActuadorAcelerador_Desconectado_Probado);

    }

    // Testing Ambos Actuadores Desconectados
    else if(contTesting <= Testing_nIteraciones_Actuadores_Desconectados && !Testing_Actuadores_Desconectados_Probado)
    {
        if(contTesting == 1) {
            Serial.println("**Testing Ambos Actuadores Desconectados...**");
        }
        Testing_Joystick_Pots_Virtual(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = false,  freno_Conectado = false, // <--------------------

                    joyst_X_EnRango = true,  joys_Y_EnRango = true,
                    acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_nIteraciones_Actuadores_Desconectados, Testing_Actuadores_Desconectados_Probado);

        //Testing_ReiniciarPrueba = true;
    }

    // Testing Reiniciando prueba
    else if(contTesting <= Testing_nIteraciones_ReiniciandoPrueba && !Testing_ReiniciarPrueba_Probado)
    {
        if(contTesting == 1)
        {
            Serial.println("**Testing Reiniciando prueba**");
        }


        if(contTesting == Testing_nIteraciones_ReiniciandoPrueba)
        {
            Testing_Acelerador_Probado          = false;
            Testing_Freno_Probado               = false;
            Testing_VolanteIzquierda_Probado    = false;
            Testing_VolanteInhibido_Probado     = false;
            Testing_VolanteDerecha_Probado      = false;

            Testing_JoystickY_Desconectado_Probado          = false;
            Testing_JoystickX_Desconectado_Probado          = false;
            Testing_Joystick_Desconectado_Probado           = false;

            Testing_ActuadorFreno_Desconectado_Probado      = false;
            Testing_ActuadorAcelerador_Desconectado_Probado = false;
            Testing_Actuadores_Desconectados_Probado        = false;

            Testing_ReiniciarPrueba_Probado     = false;
            contTesting = 0;
         }
        //Testing_ActualizarContador(contTesting, Testing_nIteraciones_ReiniciandoPrueba, Testing_ReiniciarPrueba_Probado);
    }

    contTesting++;
}

void leerFeedback_Virtual(
    uint8_t palancaUp, uint8_t palancaDown, uint8_t brakePositionFixed, uint8_t fullGasMode)
{
    Joystick_Leer_Virtual();

    Testing_Joystick_Buttons_Virtual(palancaUp, palancaDown, brakePositionFixed, fullGasMode);
}

/*void Actuadores_Feedback_Leer_Virtual(int actuadorFreno_Posicion_virtual, int actuadorAcelerador_Posicion_virtual)
{
    ActuadorFreno_Posicion = actuadorFreno_Posicion_virtual;
    ActuadorAcelerador_Posicion = actuadorAcelerador_Posicion_virtual;
}*/

#endif // TESTING_HPP

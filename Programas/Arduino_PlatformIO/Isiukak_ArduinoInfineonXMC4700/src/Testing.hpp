#ifndef TESTING_HPP
#define TESTING_HPP


#include "Seguridad.hpp"

// Definir una secuencia de control.

/****************************************************************************************
 * Para las Pruebas debe activar la constante TESTING_MODE en Config.hpp
 * Cuando esta se activa:
 * La función void Leer_Joystick_Virtual() asigna valores específicos del joystick para
 * validar el comportamiento del sistema.
 *
 * *************************************************************************************/
#if EMBEDDED_TESTING

uint16_t contTesting = 0;
uint8_t Testing_ReiniciarPrueba = false;


///* Variables para testing del Comportamiento normal del sistema. *///
//*** Variables for period of checking definition  ***//
uint16_t Testing_tiempo_AceleradorActivado = 3000; //ms
uint16_t Testing_tiempo_FrenoActivado = 3000; //
uint16_t Testing_tiempo_VolanteIzqActivado = 3600;
uint16_t Testing_tiempo_VolanteInhibido = 2000;
uint16_t Testing_tiempo_VolanteDerActivado = 3600;
uint16_t Testing_tiempo_PalancaExtension = 3000;
uint16_t Testing_tiempo_PalancaRetraction = 3500;
//*** Variables para conteo de iteraciones ***//
uint16_t Testing_aceleradorActivado_nIteraciones;
uint16_t Testing_frenoActivado_nIteraciones;
uint16_t Testing_volanteIzquierda_nIteraciones;
uint16_t Testing_volanteInhibido_nIteraciones;
uint16_t Testing_volanteDerecha_nIteraciones;
uint16_t Testing_PalancaEnExtension_nIteraciones;
uint16_t Testing_PalancaRetraction_nIteraciones;
//*** Variables para registrar los casos que ya se probaron ***//
uint8_t Testing_Acelerador_Probado = false;
uint8_t Testing_Freno_Probado = false;
uint8_t Testing_VolanteIzquierda_Probado = false;
uint8_t Testing_VolanteInhibido_Probado = false;
uint8_t Testing_VolanteDerecha_Probado = false;
uint8_t Testing_PalancaExtension_Probada = false;
uint8_t Testing_PalancaRetraction_Probada = false;
//*** Messages ***//
                                             // "1       10        20        30"
char Testing_AceleradorActivado_msg[40] =       "Gas pedal full activated\0";
char Testing_FrenoActivado_msg[40] =            "Brake pedal full activated\0";
char Testing_VolanteIzqActivado_msg[40] =       "Steering whel full left\0";



///* Variables para testing del Comportamiento en error del sistema. *///
//** Components disconnected **//
uint16_t Testing_tiempo_JoystickY_Desconectado = 5000;
uint16_t Testing_tiempo_JoystickX_Desconectado = 5000;
uint16_t Testing_tiempo_Joystick_Desconectado = 5000;
uint16_t Testing_tiempo_ActuadorFreno_Desconectado = 5000;
uint16_t Testing_tiempo_ActuadorAcelerador_Desconectado = 5000;
uint16_t Testing_tiempo_Actuadores_Desconectados = 5000;
//*** ***//
uint16_t Testing_JoystickY_Desconectado_nIteraciones;
uint16_t Testing_JoystickX_Desconectado_nIteraciones;
uint16_t Testing_Joystick_Desconectado_nIteraciones;
uint16_t Testing_ActuadorFreno_Desconectado_nIteraciones;
uint16_t Testing_ActuadorAcelerador_Desconectado_nIteraciones;
uint16_t Testing_Actuadores_Desconectados_nIteraciones;
//*** Variables para registrar los casos que ya se probaron ***//
uint8_t Testing_JoystickX_Desconectado_Probado = false;
uint8_t Testing_JoystickY_Desconectado_Probado = false;
uint8_t Testing_Joystick_Desconectado_Probado = false; // Ambos Ejes
uint8_t Testing_ActuadorFreno_Desconectado_Probado = false;
uint8_t Testing_ActuadorAcelerador_Desconectado_Probado = false;
uint8_t Testing_Actuadores_Desconectados_Probado = false;

//** Components out of range **//
uint16_t Testing_tiempo_JoystickY_FueraRango = 5000;
uint16_t Testing_tiempo_JoystickX_FueraRango = 5000;
uint16_t Testing_tiempo_Joystick_FueraRango = 5000;
uint16_t Testing_tiempo_ActuadorFreno_FueraRango = 5000;
uint16_t Testing_tiempo_ActuadorAcelerador_FueraRango = 5000;
uint16_t Testing_tiempo_Actuadores_FueraRango = 5000;
//*** ***//
uint16_t Testing_JoystickY_FueraRango_nIteraciones;
uint16_t Testing_JoystickX_FueraRango_nIteraciones;
uint16_t Testing_Joystick_FueraRango_nIteraciones;
uint16_t Testing_ActuadorFreno_FueraRango_nIteraciones;
uint16_t Testing_ActuadorAcelerador_FueraRango_nIteraciones;
uint16_t Testing_Actuadores_FueraRango_nIteraciones;
//*** Variables para registrar los casos que ya se probaron ***//
uint8_t Testing_JoystickY_FueraRango_Probado = false;
uint8_t Testing_JoystickX_FueraRango_Probado = false;
uint8_t Testing_Joystick_FueraRango_Probado = false; // Ambos Ejes
uint8_t Testing_ActuadorFreno_FueraRango_Probado = false;
uint8_t Testing_ActuadorAcelerador_FueraRango_Probado = false;
uint8_t Testing_Actuadores_FueraRango_Probado = false; // Ambos
//*** Variables para registrar los casos que ya se probaron ***//
char Testing_JoystickX_FueraRango_msg[40] = "Joystick X Out of Range\0";
char Testing_JoystickY_FueraRango_msg[40] = "Joystick Y Out of Range\0";
char Testing_Joystick_FueraRango_msg[40] = "Joystick Out of Range\0";
char Testing_ActuadorFreno_FueraRango_msg[40] = "Brake pot Out of Range\0";
char Testing_ActuadorAcelerador_FueraRango_msg[40] = "Gas pot Out of Range\0";
char Testing_Actuadores_FueraRango_msg[40] = "Actuators pots Out of Range\0";


///* *///
uint16_t Testing_tiempoReiniciarPrueba = 3000;
uint16_t Testing_ReiniciandoPrueba_nIteraciones;
uint8_t Testing_ReiniciarPrueba_Probado = false;


void calculate_IterationsPerActuator(uint8_t periodoDeseado)
{
    Testing_aceleradorActivado_nIteraciones = Testing_tiempo_AceleradorActivado / periodoDeseado;
    Testing_frenoActivado_nIteraciones      = Testing_tiempo_FrenoActivado / periodoDeseado;
    Testing_volanteIzquierda_nIteraciones   = Testing_tiempo_VolanteIzqActivado / periodoDeseado;
    Testing_volanteInhibido_nIteraciones    = Testing_tiempo_VolanteInhibido / periodoDeseado;
    Testing_volanteDerecha_nIteraciones     = Testing_tiempo_VolanteDerActivado / periodoDeseado;


    Testing_JoystickY_Desconectado_nIteraciones             = Testing_tiempo_JoystickY_Desconectado / periodoDeseado;
    Testing_JoystickX_Desconectado_nIteraciones             = Testing_tiempo_JoystickX_Desconectado / periodoDeseado;
    Testing_Joystick_Desconectado_nIteraciones              = Testing_tiempo_Joystick_Desconectado / periodoDeseado;
    Testing_ActuadorFreno_Desconectado_nIteraciones         = Testing_tiempo_ActuadorFreno_Desconectado / periodoDeseado;
    Testing_ActuadorAcelerador_Desconectado_nIteraciones    = Testing_tiempo_ActuadorAcelerador_Desconectado / periodoDeseado;
    Testing_Actuadores_Desconectados_nIteraciones           = Testing_tiempo_Actuadores_Desconectados / periodoDeseado;

    Testing_JoystickY_FueraRango_nIteraciones           = Testing_tiempo_JoystickY_FueraRango / periodoDeseado;
    Testing_JoystickX_FueraRango_nIteraciones           = Testing_tiempo_JoystickX_FueraRango / periodoDeseado;
    Testing_Joystick_FueraRango_nIteraciones            = Testing_tiempo_Joystick_FueraRango / periodoDeseado;
    Testing_ActuadorFreno_FueraRango_nIteraciones       = Testing_tiempo_ActuadorFreno_FueraRango / periodoDeseado;
    Testing_ActuadorAcelerador_FueraRango_nIteraciones  = Testing_tiempo_ActuadorAcelerador_FueraRango / periodoDeseado;
    Testing_Actuadores_FueraRango_nIteraciones          = Testing_tiempo_Actuadores_FueraRango / periodoDeseado;

    Testing_ReiniciandoPrueba_nIteraciones  = Testing_tiempoReiniciarPrueba / periodoDeseado;
}


void Testing_set_Virtual_Joystick_Pots(int Joystick_Y, int Joystick_X)
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

void Testing_set_Virtual_Joystick_Buttons(
        uint8_t subirPalanca, uint8_t bajarPalanca, uint8_t fijarPosicionFreno, uint8_t modoCarretera)
        //uint8_t &SubirPalanca, uint8_t &BajarPalanca, uint8_t &FijarPosicionFreno, uint8_t &ModoCarreteraActivado)
{

    SubirPalanca = subirPalanca;
    BajarPalanca = bajarPalanca;
    FijarPosicionFreno = fijarPosicionFreno;
    ModoCarreteraActivado = modoCarretera;
}

void Testing_ActualizarContador(uint16_t &contadorIteraciones, uint16_t nIteraciones, uint8_t &elementoProbado )
{
    if(contadorIteraciones >= nIteraciones)
    {
        elementoProbado = true;
        contadorIteraciones = 0;
    }
}

void Testing_ActualizarContadorMsg(uint16_t &contadorIteraciones, uint16_t nIteraciones, uint8_t &elementoProbado,
                                   char* msg)
{
    if(contadorIteraciones == 1) {
        //Serial.println("**Testing the system at normal behaviour (everything connected and in range)**");
        Serial.print("**Testing ");  Serial.print(msg); Serial.println("**");
    }

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
    uint8_t acelerador_EnRango, uint8_t freno_EnRango )
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
    /*! The Embedded Test assigns virtual values for the joystick (pots and buttons)
    * to chek the correct response of actuators as well as setting values of
    *disconnected pots to check the correct response of safety routines.
    *
    **************************************************************************************/

    uint8_t joyst_X_Conectado = true,  joyst_Y_Conectado = true;
    uint8_t acelerador_Conectado = true,  freno_Conectado = true;
    uint8_t joyst_X_EnRango = true,  joys_Y_EnRango = true;
    uint8_t acelerador_EnRango = true, freno_EnRango = true;

    uint8_t palancaDown = LOW, palancaUp = LOW, brakePositionFixed = LOW, fullGasMode = LOW;

    if(contTesting == 0)
    {
        Serial.println("Iniciando la prueba en el micro con valores virtuales del Joystick.");
        Serial.println("**ESTA PRUEBA DEBE HACERSE CON EL SISTEMA DESINSTALADO DEL CARRO.**");
        Serial.println("Starting embedded testing with Joystick virtual values to check safety routines..");
        Serial.println("**THIS TEST SHALL ONLY MADE WITH ISIUKAK UNINSTALLED FROM THE CAR.**");
    }

    /// Normal behaviour checking
    // 1 Activar el ACELERADOR A FULL durante n_a iteraciones
    if(contTesting <= Testing_aceleradorActivado_nIteraciones
                  && !Testing_Acelerador_Probado)
    {
        if(contTesting == 1) {
            Serial.println("**Testing the system at normal behaviour (everything connected and in range)**");
            //Serial.println("** Testing Acelerador a full...**");
        }
        Testing_set_Virtual_Joystick_Pots(joyY_MinVal, joyX_Center);

        Testing_set_Virtual_Joystick_Buttons(
            palancaUp = LOW, palancaDown = LOW, brakePositionFixed = LOW, fullGasMode = LOW);

        Testing_VerificacionSeguridad_SetValues(
                joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                acelerador_Conectado = true,  freno_Conectado = true,

                joyst_X_EnRango = true,  joys_Y_EnRango = true,
                acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContadorMsg(contTesting,
                                      Testing_aceleradorActivado_nIteraciones,
                                      Testing_Acelerador_Probado,
                                      Testing_AceleradorActivado_msg);
    }

    // 2 Activar el FRENO A FULL durante n_f iteraciones
    else if(contTesting <= Testing_frenoActivado_nIteraciones
                       && !Testing_Freno_Probado)
    {
        /*if(contTesting == 1) {
            Serial.println("**Testing Freno a full...**");
        }*/
        Testing_set_Virtual_Joystick_Pots(joyY_MaxVal, joyX_Center);
        //Testing_VerificacionSeguridad_SetValues() // No modificar las variables de conexión

        Testing_ActualizarContadorMsg(contTesting,
                                      Testing_frenoActivado_nIteraciones,
                                      Testing_Freno_Probado,
                                      Testing_FrenoActivado_msg);
    }

    // 3 Activar el VOLANTE HACIA LA IZQUIERDA durante n_i iteraciones
    else if(contTesting <= Testing_volanteIzquierda_nIteraciones
                       && !Testing_VolanteIzquierda_Probado)
    {
        /*if(contTesting == 1) {
            Serial.println("**Testing Volante a la izquierda a full...**");
        }*/
        Testing_set_Virtual_Joystick_Pots(joyY_Center, joyX_MinVal);
        // Testing_VerificacionSeguridad_SetValues //No modificar las variables de conexión

        Testing_ActualizarContadorMsg(contTesting,
                                      Testing_volanteIzquierda_nIteraciones,
                                      Testing_VolanteIzquierda_Probado,
                                      Testing_VolanteIzqActivado_msg);
    }

    // 4 No actuar el volante durante nIteraciones
    else if(contTesting <= Testing_volanteInhibido_nIteraciones
                       && !Testing_VolanteInhibido_Probado)
    {
        if(contTesting == 1)
        {
            Serial.println("**Testing Volante sin actuar...**");
        }
        Testing_set_Virtual_Joystick_Pots(joyY_Center, joyX_Center);
        // Testing_VerificacionSeguridad_SetValues //No modificar las variables de conexión

        Testing_ActualizarContador(contTesting, Testing_volanteInhibido_nIteraciones, Testing_VolanteInhibido_Probado);
    }

    // 5 Activar el volante a la derecha a full durante n_d iteraciones
    else if(contTesting <= Testing_volanteDerecha_nIteraciones
                       && !Testing_VolanteDerecha_Probado)
    {
        if(contTesting == 1)
        {
            Serial.println("**Testing Volante a la derecha...**");
        }
        Testing_set_Virtual_Joystick_Pots(joyY_Center, joyX_MaxVal);
        // Testing_VerificacionSeguridad_SetValues //No modificar las variables de conexión.

        Testing_ActualizarContador(contTesting, Testing_volanteDerecha_nIteraciones, Testing_VolanteDerecha_Probado);
    }

    /// Disconnection detection checking
    // 6 Testing Joystick Y disconnected.
    else if(contTesting <= Testing_JoystickY_Desconectado_nIteraciones
                       && !Testing_JoystickY_Desconectado_Probado)
    {
        if(contTesting == 1) {
            //Serial.print("**Testing**");
            Serial.println("**System at error: Disconnected componentes**");
            Serial.println("**Joystick Y Disconnected...**");
        }
        Testing_set_Virtual_Joystick_Pots(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                joyst_X_Conectado = true,
                joyst_Y_Conectado = false, //  <----------
                acelerador_Conectado = true,  freno_Conectado = true,

                joyst_X_EnRango = true,  joys_Y_EnRango = true,
                acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_JoystickY_Desconectado_nIteraciones,
                                                Testing_JoystickY_Desconectado_Probado);
    }

    // 7 Testing Joystick X disconnected.
    else if(contTesting <= Testing_JoystickX_Desconectado_nIteraciones
                       && !Testing_JoystickX_Desconectado_Probado)
    {
        if(contTesting == 1)  {
            Serial.print("**Testing**");
            Serial.println("**Joystick X Disconnected...**");
        }
        Testing_set_Virtual_Joystick_Pots(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                joyst_X_Conectado = false, // <----------
                joyst_Y_Conectado = true,
                acelerador_Conectado = true,  freno_Conectado = true,

                joyst_X_EnRango = true,  joys_Y_EnRango = true,
                acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting,
                                   Testing_JoystickX_Desconectado_nIteraciones,
                                   Testing_JoystickX_Desconectado_Probado);
    }

    // 8 Testing Joystick disconnected.
    else if(contTesting <= Testing_Joystick_Desconectado_nIteraciones
                       && !Testing_Joystick_Desconectado_Probado)
    {
        if(contTesting == 1) {
            //Serial.print("**Testing**");
            Serial.println("**Joystick both axis Disconnected...**");
        }
        Testing_set_Virtual_Joystick_Pots(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                joyst_X_Conectado = false, // <----------
                joyst_Y_Conectado = false, // <----------
                acelerador_Conectado = true,  freno_Conectado = true,

                joyst_X_EnRango = true,  joys_Y_EnRango = true,
                acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_Joystick_Desconectado_nIteraciones,
                                                Testing_Joystick_Desconectado_Probado);
    }

    // 9  Testing Freno Desconectado.
    else if(contTesting <= Testing_ActuadorFreno_Desconectado_nIteraciones
                       && !Testing_ActuadorFreno_Desconectado_Probado)
    {
        if(contTesting == 1) {
            Serial.print("**Testing**");
            Serial.println("**Freno Desconectado...**");
        }
        Testing_set_Virtual_Joystick_Pots(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = true,
                    freno_Conectado = false, // <----------

                    joyst_X_EnRango = true,  joys_Y_EnRango = true,
                    acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_ActuadorFreno_Desconectado_nIteraciones,
                                                Testing_ActuadorFreno_Desconectado_Probado);
    }

    // 10 Testing Acelerador Desconectado
    else if(contTesting <= Testing_ActuadorAcelerador_Desconectado_nIteraciones
                       && !Testing_ActuadorAcelerador_Desconectado_Probado)
    {
        if(contTesting == 1)
        {
            Serial.print("**Testing**");
            Serial.println("**Acelerador Desconectado...**");
        }
        Testing_set_Virtual_Joystick_Pots(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = false,  // <---------------
                    freno_Conectado = true,

                    joyst_X_EnRango = true,  joys_Y_EnRango = true,
                    acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_ActuadorAcelerador_Desconectado_nIteraciones,
                                                Testing_ActuadorAcelerador_Desconectado_Probado);

    }

    // 11  Testing Ambos Actuadores Desconectados
    else if(contTesting <= Testing_Actuadores_Desconectados_nIteraciones
                       && !Testing_Actuadores_Desconectados_Probado)
    {
        if(contTesting == 1) {
            //Serial.print("**Testing**");
            Serial.println("**Ambos Actuadores Desconectados...**");
        }
        Testing_set_Virtual_Joystick_Pots(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = false,   // <------
                    freno_Conectado = false,        // <------

                    joyst_X_EnRango = true,  joys_Y_EnRango = true,
                    acelerador_EnRango = true, freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_Actuadores_Desconectados_nIteraciones,
                                                Testing_Actuadores_Desconectados_Probado);

        //Testing_ReiniciarPrueba = true;
    }

    /// Out of Range detection checking.
    //12 Testing Joystick Y Out of Range.
    else if(contTesting <= Testing_JoystickY_FueraRango_nIteraciones
                       && !Testing_JoystickY_FueraRango_Probado)
    {
        if(contTesting == 1) {
            Serial.print("**Testing**");
            Serial.println("**Out of Range detection checking.**");
            Serial.println("**Joystick Y Out of Range...**");
        }
        Testing_set_Virtual_Joystick_Pots(joyY_MaxVal, joyX_Center);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = true,  freno_Conectado = true,

                    joyst_X_EnRango = true,
                    joys_Y_EnRango = false,  // <------
                    acelerador_EnRango = true,
                    freno_EnRango = true );

        Testing_ActualizarContador(contTesting, Testing_JoystickY_FueraRango_nIteraciones,
                                                Testing_JoystickY_FueraRango_Probado);
    }

    // TODO: 13  Testing Joystick X Out of Range.
    else if(contTesting <= Testing_JoystickX_FueraRango_nIteraciones
                        && !Testing_JoystickX_FueraRango_Probado)
    {
        Testing_set_Virtual_Joystick_Pots(joyY_MinVal, joyX_MinVal);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = true,  freno_Conectado = true,

                    joyst_X_EnRango = false,    // <------
                    joys_Y_EnRango = true,
                    acelerador_EnRango = true,
                    freno_EnRango = true );

        Testing_ActualizarContadorMsg(contTesting,
                                      Testing_JoystickX_FueraRango_nIteraciones,
                                      Testing_JoystickX_FueraRango_Probado,
                                      Testing_JoystickX_FueraRango_msg);
    }

    // TODO: 14  Testing Joystick both axis Out of Range.
    else if(contTesting <= Testing_Joystick_FueraRango_nIteraciones
                       && !Testing_Joystick_FueraRango_Probado)
    {
        Testing_set_Virtual_Joystick_Pots(joyY_MinVal, joyX_MinVal);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = true,  freno_Conectado = true,

                    joyst_X_EnRango = false,    // <------
                    joys_Y_EnRango = false,     // <------
                    acelerador_EnRango = true,
                    freno_EnRango = true );

        Testing_ActualizarContadorMsg(contTesting,
                                      Testing_Joystick_FueraRango_nIteraciones,
                                      Testing_Joystick_FueraRango_Probado,
                                      Testing_Joystick_FueraRango_msg);
    }

    // TODO: 15  Testing Accel Pedal Out of Range.
    else if(contTesting <= Testing_ActuadorAcelerador_FueraRango_nIteraciones
                        & !Testing_ActuadorAcelerador_FueraRango_Probado)
    {
        Testing_set_Virtual_Joystick_Pots(joyY_MinVal, joyX_MinVal);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = true,  freno_Conectado = true,

                    joyst_X_EnRango = true,
                    joys_Y_EnRango = true,
                    acelerador_EnRango = false,// <------
                    freno_EnRango = true );

        Testing_ActualizarContadorMsg(contTesting,
                                      Testing_ActuadorAcelerador_FueraRango_nIteraciones,
                                      Testing_ActuadorAcelerador_FueraRango_Probado,
                                      Testing_ActuadorAcelerador_FueraRango_msg);
    }

    // TODO: 16  Testing Brake pedal Out of Range.
    else if(contTesting <= Testing_ActuadorFreno_FueraRango_nIteraciones
                        && !Testing_ActuadorFreno_FueraRango_Probado)
    {
        Testing_set_Virtual_Joystick_Pots(joyY_MinVal, joyX_MinVal);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = true,  freno_Conectado = true,

                    joyst_X_EnRango = true,
                    joys_Y_EnRango = true,
                    acelerador_EnRango = true,
                    freno_EnRango = false );    // <------

        Testing_ActualizarContadorMsg(contTesting,
                                      Testing_ActuadorFreno_FueraRango_nIteraciones,
                                      Testing_ActuadorFreno_FueraRango_Probado,
                                      Testing_ActuadorFreno_FueraRango_msg);
    }

    // TODO: 17  Testing Both Actuators Out of Range.
    else if(contTesting <= Testing_Actuadores_FueraRango_nIteraciones
                       && !Testing_Actuadores_FueraRango_Probado)
    {
        Testing_set_Virtual_Joystick_Pots(joyY_MinVal, joyX_MinVal);

        Testing_VerificacionSeguridad_SetValues(
                    joyst_X_Conectado = true,  joyst_Y_Conectado = true,
                    acelerador_Conectado = true,  freno_Conectado = true,

                    joyst_X_EnRango = true,
                    joys_Y_EnRango = true,
                    acelerador_EnRango = false, // <------
                    freno_EnRango = false );    // <------

        Testing_ActualizarContadorMsg(contTesting,
                                      Testing_Actuadores_FueraRango_nIteraciones,
                                      Testing_Actuadores_FueraRango_Probado,
                                      Testing_Actuadores_FueraRango_msg);
    }

    /// Testing Reiniciando prueba
    else if(contTesting <= Testing_ReiniciandoPrueba_nIteraciones
                       && !Testing_ReiniciarPrueba_Probado)
    {
        if(contTesting == 1)
        {
            Serial.println("**Testing**");
            Serial.println("**Reiniciando prueba**");
        }

        if(contTesting == Testing_ReiniciandoPrueba_nIteraciones)
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


            Testing_JoystickX_FueraRango_Probado    = false;
            Testing_JoystickY_FueraRango_Probado    = false;
            Testing_Joystick_FueraRango_Probado     = false;

            Testing_ActuadorFreno_FueraRango_Probado        = false;
            Testing_ActuadorAcelerador_FueraRango_Probado   = false;
            Testing_Actuadores_FueraRango_Probado           = false;

            Testing_ReiniciarPrueba_Probado     = false;

            contTesting = 0;
         }
        //Testing_ActualizarContador(contTesting, Testing_ReiniciandoPrueba_nIteraciones,
        //                                        Testing_ReiniciarPrueba_Probado);
    }


    contTesting++;
}

void leerFeedback_Virtual(
    uint8_t palancaUp, uint8_t palancaDown, uint8_t brakePositionFixed, uint8_t fullGasMode)
{
    Joystick_Leer_Virtual();

    Testing_set_Virtual_Joystick_Buttons(palancaUp, palancaDown, brakePositionFixed, fullGasMode);
}
#endif

/*void Actuadores_Feedback_Leer_Virtual(int actuadorFreno_Posicion_virtual, int actuadorAcelerador_Posicion_virtual)
{
    ActuadorFreno_Posicion = actuadorFreno_Posicion_virtual;
    ActuadorAcelerador_Posicion = actuadorAcelerador_Posicion_virtual;
}*/

#endif // TESTING_HPP

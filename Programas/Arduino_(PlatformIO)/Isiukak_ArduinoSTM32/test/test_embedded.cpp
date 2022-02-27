//#include <Arduino.h>
#include <unity.h>
// pio platform install "native"

//#include "../src/Config.hpp"
#include "../src/Seguridad.hpp"

/*
# Test project
> platformio test

# Test specific environment
> platformio test -e nucleo_f401re

# Process test on native desktop machine
> platformio test -e native
*/


/*Funciones disponibles:
 *  TEST_ASSERT_EQUAL
 *  TEST_ASSERT_TRUE
 *  TEST_ASSERT_FALSE
 *
*/

void test_mode_enabled()
{
    TEST_ASSERT_EQUAL(TESTING_MODE, 1);
}

void test_pots_connected()
{
    /*Si los pots están conectados:
     *  - Al poner los extremos en bajo el wiper debe medir por debajo de un umbral
        - Al poner los extremos en alto el wiper debe medir por arriba de un umbral
    Por lo que al asignarle el valor 20 y 1023 debería pasar la prueba. */
    uint8_t Joystick_Y_Conectado;
    uint8_t Joystick_X_Conectado;
    uint8_t Joystick_Conectado;
    uint8_t ActuadorFreno_Conectado;
    uint8_t ActuadorAcelerador_Conectado;
    uint8_t Actuadores_Conectados;


    unsigned int value_lowValid = 20;
    unsigned int value_highValid = 1003;

    for(int cont=0; cont < 4; cont++)
    {
        PotenciometrosVirtuales_ValidacionConexion[0][cont] = value_lowValid; //Valor virtual en bajo.
    }
    for(int cont=0; cont < 4; cont++)
    {
        PotenciometrosVirtuales_ValidacionConexion[1][cont] = value_highValid; //Valor virtual en alto.
    }

    Potenciometros_VerificarConexion(Joystick_Y_Conectado, Joystick_X_Conectado, Joystick_Conectado,
                                     ActuadorFreno_Conectado, ActuadorAcelerador_Conectado, Actuadores_Conectados);


    TEST_ASSERT_EQUAL(Joystick_Y_Conectado, true);
    TEST_ASSERT_EQUAL(Joystick_X_Conectado, true);
    TEST_ASSERT_EQUAL(Joystick_Conectado, true);
    TEST_ASSERT_EQUAL(ActuadorFreno_Conectado, true);
    TEST_ASSERT_EQUAL(ActuadorAcelerador_Conectado, true);
    TEST_ASSERT_EQUAL(Actuadores_Conectados, true);

}

void test_pots_disconnected()
{
    /*Si los pots están desconectados:
     *  - Al poner los extremos en bajo el wiper sigue con valores aleatorios alrededor de 512
        - Al poner los extremos en alto el wiper debe medir por arriba de un umbral*/
    uint8_t Joystick_Y_Conectado;
    uint8_t Joystick_X_Conectado;
    uint8_t Joystick_Conectado;
    uint8_t ActuadorFreno_Conectado;
    uint8_t ActuadorAcelerador_Conectado;
    uint8_t Actuadores_Conectados;

    unsigned int value_lowInvalid = 400;
    unsigned int value_highInvalid = 403;

    for(int cont=0; cont < 4; cont++)
    {
        PotenciometrosVirtuales_ValidacionConexion[0][cont] = value_lowInvalid; //Valor virtual en bajo.
    }
    for(int cont=0; cont < 4; cont++)
    {
        PotenciometrosVirtuales_ValidacionConexion[1][cont] = value_highInvalid; //Valor virtual en alto.
    }

    Potenciometros_VerificarConexion(Joystick_Y_Conectado, Joystick_X_Conectado, Joystick_Conectado,
                                     ActuadorFreno_Conectado, ActuadorAcelerador_Conectado, Actuadores_Conectados);


    TEST_ASSERT_EQUAL(Joystick_Y_Conectado, false);
    TEST_ASSERT_EQUAL(Joystick_X_Conectado, false);
    TEST_ASSERT_EQUAL(Joystick_Conectado, false);
    TEST_ASSERT_EQUAL(ActuadorFreno_Conectado, false);
    TEST_ASSERT_EQUAL(ActuadorAcelerador_Conectado, false);
    TEST_ASSERT_EQUAL(Actuadores_Conectados, false);

}

void test_pots_inRange()
{
    uint8_t Potenciometros_EnRangoValido = false;

    int Joystick_X = 512;
    int Joystick_Y = 512;
    int ActuadorFreno_Posicion = ActuadorFreno_valorExtendido;
    int ActuadorAcelerador_Posicion = ActuadorAcelerador_valorRetraido;

    uint8_t Joystick_X_EnRango = false;
    uint8_t Joystick_Y_EnRango = false;
    uint8_t Joystick_EnRango = false;

    uint8_t ActuadorAcelerador_EnRango = false;
    uint8_t ActuadorFreno_EnRango = false;
    uint8_t Actuadores_EnRango = false;

    Potenciometros_EnRangoValido = Potenciometros_EstanEnRango(
                Joystick_X, Joystick_Y,
                ActuadorAcelerador_Posicion, ActuadorFreno_Posicion,

                Joystick_X_EnRango, Joystick_Y_EnRango, Joystick_EnRango,
                ActuadorAcelerador_EnRango, ActuadorFreno_EnRango, Actuadores_EnRango);


    TEST_ASSERT_EQUAL(Joystick_X_EnRango, true);
    TEST_ASSERT_EQUAL(Joystick_Y_EnRango, true);
    TEST_ASSERT_EQUAL(ActuadorAcelerador_EnRango, true);
    TEST_ASSERT_EQUAL(ActuadorFreno_EnRango, true);
    TEST_ASSERT_EQUAL(Potenciometros_EnRangoValido, true);
}

void test_pots_NotInRange()
{
    uint8_t Potenciometros_EnRangoValido = false;

    int Joystick_X = joyY_MaxVal + joystick_UmbralFueraRango + 20;
    int Joystick_Y = joyY_MaxVal + joystick_UmbralFueraRango + 20;

    int ActuadorFreno_Posicion = ActuadorFreno_valorExtendido;
    int ActuadorAcelerador_Posicion = ActuadorAcelerador_valorRetraido;

    uint8_t Joystick_X_EnRango = false;
    uint8_t Joystick_Y_EnRango = false;
    uint8_t Joystick_EnRango = false;

    uint8_t ActuadorAcelerador_EnRango = false;
    uint8_t ActuadorFreno_EnRango = false;
    uint8_t Actuadores_EnRango = false;

    Potenciometros_EnRangoValido = Potenciometros_EstanEnRango(Joystick_X, Joystick_Y,
                                                               ActuadorAcelerador_Posicion, ActuadorFreno_Posicion,
                                                               Joystick_X_EnRango, Joystick_Y_EnRango, Joystick_EnRango,
                                                               ActuadorAcelerador_EnRango, ActuadorFreno_EnRango, Actuadores_EnRango);


    TEST_ASSERT_EQUAL(Joystick_X_EnRango, false);
    TEST_ASSERT_EQUAL(Joystick_Y_EnRango, false);
    TEST_ASSERT_EQUAL(ActuadorAcelerador_EnRango, true);
    TEST_ASSERT_EQUAL(ActuadorFreno_EnRango, true);
    TEST_ASSERT_EQUAL(Potenciometros_EnRangoValido, false);
}

void test_aplicarRutinasSeguridad_JoystickX_Desconectado()
{
    uint8_t Joystick_X_Conectado = false; //
    uint8_t Joystick_Y_Conectado = true;
    uint8_t ActuadorAcelerador_Conectado = true;
    uint8_t ActuadorFreno_Conectado = true;
    uint8_t Joystick_X_EnRango = true;
    uint8_t Joystick_Y_EnRango = true;
    uint8_t ActuadorAcelerador_EnRango = true;
    uint8_t ActuadorFreno_EnRango = true;

    ErrorCodes EstadoDelSistema = ErrorCodes::OK;
    uint8_t ActuadorFreno_EstaInhibido = false;
    uint8_t ActuadorAcelerador_EstaInhibido = false;
    volante_Desinhibir();

    aplicarRutinasSeguridad(
                Joystick_X_Conectado, Joystick_Y_Conectado,
                ActuadorAcelerador_Conectado, ActuadorFreno_Conectado,
                Joystick_X_EnRango,   Joystick_Y_EnRango,
                ActuadorAcelerador_EnRango, ActuadorFreno_EnRango,

                EstadoDelSistema,
                ActuadorFreno_EstaInhibido, ActuadorAcelerador_EstaInhibido);


    TEST_ASSERT_EQUAL(TipoControlVolante, TiposControlVolante::MODO_INHIBIDO);
    TEST_ASSERT_EQUAL(mensajeError_Joystick_X_Desconectado_Registrado, true);
    TEST_ASSERT_EQUAL(LED_Joystick_X_Desconectado, true);

    TEST_ASSERT_EQUAL(EstadoDelSistema, ErrorCodes::EmergencyStop);
    TEST_ASSERT_EQUAL(ActuadorAcelerador_EstaInhibido, false);
    TEST_ASSERT_EQUAL(ActuadorFreno_EstaInhibido, false);
}

void test_aplicarRutinasSeguridad_JoystickY_Desconectado()
{
    uint8_t Joystick_X_Conectado = true;
    uint8_t Joystick_Y_Conectado = false; //
    uint8_t ActuadorAcelerador_Conectado = true;
    uint8_t ActuadorFreno_Conectado = true;
    uint8_t Joystick_X_EnRango = true;
    uint8_t Joystick_Y_EnRango = true;
    uint8_t ActuadorAcelerador_EnRango = true;
    uint8_t ActuadorFreno_EnRango = true;

    ErrorCodes EstadoDelSistema = ErrorCodes::OK;
    uint8_t ActuadorFreno_EstaInhibido = false;
    uint8_t ActuadorAcelerador_EstaInhibido = false;
    volante_Desinhibir();

    aplicarRutinasSeguridad(
                Joystick_X_Conectado, Joystick_Y_Conectado,
                ActuadorAcelerador_Conectado, ActuadorFreno_Conectado,

                Joystick_X_EnRango,   Joystick_Y_EnRango,
                ActuadorAcelerador_EnRango, ActuadorFreno_EnRango,

                EstadoDelSistema,
                ActuadorAcelerador_EstaInhibido, ActuadorFreno_EstaInhibido);

    TEST_ASSERT_EQUAL(TipoControlVolante, TiposControlVolante::MODO_OPENLOOP_PORPARTES);
    TEST_ASSERT_EQUAL(mensajeError_Joystick_Y_Desconectado_Registrado, true);
    TEST_ASSERT_EQUAL(LED_Joystick_Y_Desconectado, true);

    TEST_ASSERT_EQUAL(EstadoDelSistema, ErrorCodes::EmergencyBraking);
    TEST_ASSERT_EQUAL(ActuadorAcelerador_EstaInhibido, true);
    TEST_ASSERT_EQUAL(ActuadorFreno_EstaInhibido, true);


}

void test_aplicarRutinasSeguridad_Acelerador_Desconectado()
{
    uint8_t Joystick_X_Conectado = true;
    uint8_t Joystick_Y_Conectado = true;
    uint8_t ActuadorAcelerador_Conectado = false; // Variable a verificar.
    uint8_t ActuadorFreno_Conectado = true;
    uint8_t Joystick_X_EnRango = true;
    uint8_t Joystick_Y_EnRango = true;
    uint8_t ActuadorAcelerador_EnRango = true;
    uint8_t ActuadorFreno_EnRango = true;

    ErrorCodes EstadoDelSistema = ErrorCodes::OK;
    uint8_t ActuadorFreno_EstaInhibido = false;
    uint8_t ActuadorAcelerador_EstaInhibido = false;
    volante_Desinhibir();

    aplicarRutinasSeguridad(
                Joystick_X_Conectado, Joystick_Y_Conectado,
                ActuadorAcelerador_Conectado, ActuadorFreno_Conectado,

                Joystick_X_EnRango,   Joystick_Y_EnRango,
                ActuadorAcelerador_EnRango, ActuadorFreno_EnRango,

                EstadoDelSistema,
                ActuadorAcelerador_EstaInhibido, ActuadorFreno_EstaInhibido);

    TEST_ASSERT_EQUAL(EstadoDelSistema, ErrorCodes::ImmediateStop);
    TEST_ASSERT_EQUAL(ActuadorAcelerador_EstaInhibido, true);
    TEST_ASSERT_EQUAL(ActuadorFreno_EstaInhibido, false);

    TEST_ASSERT_EQUAL(TipoControlVolante, TiposControlVolante::MODO_OPENLOOP_PORPARTES);
    TEST_ASSERT_EQUAL(mensajeError_Acelerador_Desconectado_Registrado, true);
    TEST_ASSERT_EQUAL(LED_ActuadorAcelerador_Desconectado, true);

}

void test_aplicarRutinasSeguridad_Freno_Desconectado()
{
    uint8_t Joystick_X_Conectado = true;
    uint8_t Joystick_Y_Conectado = true;
    uint8_t ActuadorAcelerador_Conectado = true;
    uint8_t ActuadorFreno_Conectado = false;
    uint8_t Joystick_X_EnRango = true;
    uint8_t Joystick_Y_EnRango = true;
    uint8_t ActuadorAcelerador_EnRango = true;
    uint8_t ActuadorFreno_EnRango = true;

    ErrorCodes EstadoDelSistema = ErrorCodes::OK;
    uint8_t ActuadorFreno_EstaInhibido = false;
    uint8_t ActuadorAcelerador_EstaInhibido = false;
    volante_Desinhibir();

    aplicarRutinasSeguridad(
                Joystick_X_Conectado, Joystick_Y_Conectado,
                ActuadorAcelerador_Conectado, ActuadorFreno_Conectado,
                Joystick_X_EnRango,   Joystick_Y_EnRango,
                ActuadorAcelerador_EnRango, ActuadorFreno_EnRango,

                EstadoDelSistema,
                ActuadorAcelerador_EstaInhibido, ActuadorFreno_EstaInhibido);

    TEST_ASSERT_EQUAL(EstadoDelSistema, ErrorCodes::EmergencyStop);
    TEST_ASSERT_EQUAL(ActuadorFreno_EstaInhibido, true);
    TEST_ASSERT_EQUAL(ActuadorAcelerador_EstaInhibido, false);

    TEST_ASSERT_EQUAL(TipoControlVolante, TiposControlVolante::MODO_OPENLOOP_PORPARTES);
    TEST_ASSERT_EQUAL(mensajeError_Freno_Desconectado_Registrado, true);
    TEST_ASSERT_EQUAL(LED_ActuadorFreno_Desconectado, true);
}

void test_aplicarRutinasSeguridad_JoystickX_OutOfRange()
{
    uint8_t Joystick_X_Conectado = true;
    uint8_t Joystick_Y_Conectado = true;
    uint8_t ActuadorAcelerador_Conectado = true;
    uint8_t ActuadorFreno_Conectado = true;
    uint8_t Joystick_X_EnRango = false;
    uint8_t Joystick_Y_EnRango = true;
    uint8_t ActuadorAcelerador_EnRango = true;
    uint8_t ActuadorFreno_EnRango = true;

    ErrorCodes EstadoDelSistema = ErrorCodes::OK;
    uint8_t ActuadorFreno_EstaInhibido = false;
    uint8_t ActuadorAcelerador_EstaInhibido = false;
    volante_Desinhibir();

    aplicarRutinasSeguridad(
                Joystick_X_Conectado, Joystick_Y_Conectado,
                ActuadorAcelerador_Conectado, ActuadorFreno_Conectado,

                Joystick_X_EnRango,   Joystick_Y_EnRango,
                ActuadorAcelerador_EnRango, ActuadorFreno_EnRango,

                EstadoDelSistema,
                ActuadorAcelerador_EstaInhibido, ActuadorFreno_EstaInhibido);

    TEST_ASSERT_EQUAL(EstadoDelSistema, ErrorCodes::EmergencyStop);
    TEST_ASSERT_EQUAL(ActuadorFreno_EstaInhibido, false);
    TEST_ASSERT_EQUAL(ActuadorAcelerador_EstaInhibido, false);

    TEST_ASSERT_EQUAL(TipoControlVolante, TiposControlVolante::MODO_INHIBIDO);
    TEST_ASSERT_EQUAL(mensajeError_Joystick_X_FueraRango_Registrado, true);
    TEST_ASSERT_EQUAL(LED_JoystickX_FueraRango, true);
}

void test_aplicarRutinasSeguridad_JoystickY_OutOfRange()
{
    uint8_t Joystick_X_Conectado = true;
    uint8_t Joystick_Y_Conectado = true;
    uint8_t ActuadorAcelerador_Conectado = true;
    uint8_t ActuadorFreno_Conectado = true;
    uint8_t Joystick_X_EnRango = true;
    uint8_t Joystick_Y_EnRango = false;
    uint8_t ActuadorAcelerador_EnRango = true;
    uint8_t ActuadorFreno_EnRango = true;

    ErrorCodes EstadoDelSistema = ErrorCodes::OK;
    uint8_t ActuadorFreno_EstaInhibido = false;
    uint8_t ActuadorAcelerador_EstaInhibido = false;
    volante_Desinhibir();

    aplicarRutinasSeguridad(
                Joystick_X_Conectado, Joystick_Y_Conectado,
                ActuadorAcelerador_Conectado, ActuadorFreno_Conectado,
                Joystick_X_EnRango,   Joystick_Y_EnRango,
                ActuadorAcelerador_EnRango, ActuadorFreno_EnRango,

                EstadoDelSistema,
                ActuadorAcelerador_EstaInhibido, ActuadorFreno_EstaInhibido);

    TEST_ASSERT_EQUAL(EstadoDelSistema, ErrorCodes::EmergencyBraking);
    TEST_ASSERT_EQUAL(ActuadorFreno_EstaInhibido, true);
    TEST_ASSERT_EQUAL(ActuadorAcelerador_EstaInhibido, true);

    TEST_ASSERT_EQUAL(TipoControlVolante, TiposControlVolante::MODO_OPENLOOP_PORPARTES);
    TEST_ASSERT_EQUAL(mensajeError_JoystickY_FueraRango_Registrado, true);
    TEST_ASSERT_EQUAL(LED_Joystick_Y_FueraRango, true);
}


void test_aplicarRutinasSeguridad_Joystick_Desconectado()
{
    uint8_t Joystick_X_Conectado = false;
    uint8_t Joystick_Y_Conectado = false; //
    uint8_t ActuadorAcelerador_Conectado = true;
    uint8_t ActuadorFreno_Conectado = true;
    uint8_t Joystick_Y_EnRango = true;
    uint8_t Joystick_X_EnRango = true;
    uint8_t ActuadorAcelerador_EnRango = true;
    uint8_t ActuadorFreno_EnRango = true;

    ErrorCodes EstadoDelSistema = ErrorCodes::OK;
    uint8_t ActuadorFreno_EstaInhibido = false;
    uint8_t ActuadorAcelerador_EstaInhibido = false;
    volante_Desinhibir();

    aplicarRutinasSeguridad(
                Joystick_X_Conectado, Joystick_Y_Conectado,
                ActuadorAcelerador_Conectado, ActuadorFreno_Conectado,

                Joystick_X_EnRango,   Joystick_Y_EnRango,
                ActuadorAcelerador_EnRango, ActuadorFreno_EnRango,

                EstadoDelSistema,
                ActuadorAcelerador_EstaInhibido, ActuadorFreno_EstaInhibido);

    TEST_ASSERT_EQUAL(TipoControlVolante, TiposControlVolante::MODO_INHIBIDO);
    TEST_ASSERT_EQUAL(mensajeError_Joystick_X_Desconectado_Registrado, true);
    TEST_ASSERT_EQUAL(mensajeError_Joystick_Y_Desconectado_Registrado, true);

    TEST_ASSERT_EQUAL(LED_Joystick_X_Desconectado, true);
    TEST_ASSERT_EQUAL(LED_Joystick_Y_Desconectado, true);

    TEST_ASSERT_EQUAL(EstadoDelSistema, ErrorCodes::EmergencyBraking);

    TEST_ASSERT_EQUAL(ActuadorAcelerador_EstaInhibido, true);
    TEST_ASSERT_EQUAL(ActuadorFreno_EstaInhibido, true);
}

void test_aplicarRutinasSeguridad_Actuadores_Desconectados()
{
    uint8_t Joystick_X_Conectado = true;
    uint8_t Joystick_Y_Conectado = true;
    uint8_t ActuadorAcelerador_Conectado = false;
    uint8_t ActuadorFreno_Conectado = false;
    uint8_t Joystick_X_EnRango = true;
    uint8_t Joystick_Y_EnRango = true;
    uint8_t ActuadorAcelerador_EnRango = true;
    uint8_t ActuadorFreno_EnRango = true;

    ErrorCodes EstadoDelSistema = ErrorCodes::OK;
    uint8_t ActuadorFreno_EstaInhibido = false;
    uint8_t ActuadorAcelerador_EstaInhibido = false;
    volante_Desinhibir();

    aplicarRutinasSeguridad(
                Joystick_X_Conectado, Joystick_Y_Conectado,
                ActuadorAcelerador_Conectado, ActuadorFreno_Conectado,
                Joystick_X_EnRango,   Joystick_Y_EnRango,
                ActuadorAcelerador_EnRango, ActuadorFreno_EnRango,

                EstadoDelSistema,
                ActuadorAcelerador_EstaInhibido, ActuadorFreno_EstaInhibido);


    TEST_ASSERT_EQUAL(EstadoDelSistema, ErrorCodes::EmergencyStop);
    TEST_ASSERT_EQUAL(ActuadorFreno_EstaInhibido, true);
    TEST_ASSERT_EQUAL(ActuadorAcelerador_EstaInhibido, true);

    TEST_ASSERT_EQUAL(TipoControlVolante, TiposControlVolante::MODO_OPENLOOP_PORPARTES);

    TEST_ASSERT_EQUAL(mensajeError_Freno_Desconectado_Registrado, true);
    TEST_ASSERT_EQUAL(mensajeError_Acelerador_Desconectado_Registrado, true);

    TEST_ASSERT_EQUAL(LED_ActuadorFreno_Desconectado, true);
    TEST_ASSERT_EQUAL(LED_ActuadorAcelerador_Desconectado, true);
}

void test_aplicarRutinasSeguridad_JoystickDesconectado_ActuadoresFueraRango()
{
    uint8_t Joystick_X_Conectado = false;
    uint8_t Joystick_Y_Conectado = false; //
    uint8_t ActuadorAcelerador_Conectado = true;
    uint8_t ActuadorFreno_Conectado = true;

    uint8_t Joystick_Y_EnRango = true;
    uint8_t Joystick_X_EnRango = true;
    uint8_t ActuadorAcelerador_EnRango = false;
    uint8_t ActuadorFreno_EnRango = false;

    ErrorCodes EstadoDelSistema = ErrorCodes::OK;
    uint8_t ActuadorFreno_EstaInhibido = false;
    uint8_t ActuadorAcelerador_EstaInhibido = false;
    volante_Desinhibir();

    aplicarRutinasSeguridad(
                Joystick_X_Conectado, Joystick_Y_Conectado,
                ActuadorAcelerador_Conectado, ActuadorFreno_Conectado,

                Joystick_X_EnRango,   Joystick_Y_EnRango,
                ActuadorAcelerador_EnRango, ActuadorFreno_EnRango,

                EstadoDelSistema,
                ActuadorAcelerador_EstaInhibido, ActuadorFreno_EstaInhibido);



    TEST_ASSERT_EQUAL(LED_Joystick_X_Desconectado, true);
    TEST_ASSERT_EQUAL(LED_Joystick_Y_Desconectado, true);

    TEST_ASSERT_EQUAL(LED_ActuadorAcelerador_FueraRango, true);
    TEST_ASSERT_EQUAL(LED_ActuadorFreno_FueraRango, true);

    TEST_ASSERT_EQUAL(EstadoDelSistema, ErrorCodes::EmergencyBraking);

    TEST_ASSERT_EQUAL(ActuadorAcelerador_EstaInhibido, true);
    TEST_ASSERT_EQUAL(ActuadorFreno_EstaInhibido, true);


    TEST_ASSERT_EQUAL(TipoControlVolante, TiposControlVolante::MODO_INHIBIDO);
    TEST_ASSERT_EQUAL(mensajeError_Joystick_X_Desconectado_Registrado, true);
    TEST_ASSERT_EQUAL(mensajeError_Joystick_Y_Desconectado_Registrado, true);
    TEST_ASSERT_EQUAL(mensajeError_Acelerador_FueraRango_Registrado, true);
    TEST_ASSERT_EQUAL(mensajeError_Freno_FueraRango_Registrado, true);
}


void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_mode_enabled);
    RUN_TEST(test_pots_connected);
    RUN_TEST(test_pots_disconnected);
    RUN_TEST(test_pots_inRange);
    RUN_TEST(test_pots_NotInRange);

    RUN_TEST(test_aplicarRutinasSeguridad_JoystickX_Desconectado);
    RUN_TEST(test_aplicarRutinasSeguridad_JoystickY_Desconectado);
    RUN_TEST(test_aplicarRutinasSeguridad_Acelerador_Desconectado);
    RUN_TEST(test_aplicarRutinasSeguridad_Freno_Desconectado);

    RUN_TEST(test_aplicarRutinasSeguridad_JoystickX_OutOfRange);
    RUN_TEST(test_aplicarRutinasSeguridad_JoystickY_OutOfRange);

    /// Probar comportamiento con varios elementos desconectados.
    RUN_TEST(test_aplicarRutinasSeguridad_Joystick_Desconectado);
    RUN_TEST(test_aplicarRutinasSeguridad_Actuadores_Desconectados);

    /// Comportamiento con algunos elementos desconectados y otros fuera de rango.
    RUN_TEST(test_aplicarRutinasSeguridad_JoystickDesconectado_ActuadoresFueraRango);

    UNITY_END();
}

void loop() {
    /*digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);*/
}

/*int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_potenciometros_conectados);

    UNITY_END();
    return 0;
}*/

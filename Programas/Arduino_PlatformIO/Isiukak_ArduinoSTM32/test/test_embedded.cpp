
// pio platform install "native"

#include "test.hpp"


/* *********************************************************************************** */
/* To run tests activate     Projects -> Build Settings -> Test Nucleo
  This are tested on the board, so the STM32 must be connected.

In case the setting is not defined, should have one of the next behaviours.
# Test project
> platformio test

# Test specific environment
> platformio test -e nucleo_f401re

# Process test on native desktop machine
> platformio test -e native
************************************************************************************** */


/*Funciones disponibles:
 *  TEST_ASSERT_EQUAL
 *  TEST_ASSERT_TRUE
 *  TEST_ASSERT_FALSE
 *
*/



//int main(int argc, char **argv)
void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    //delay(2000);
    delay(2000);
    // The general structure of a test is RUN_TEST(test_function_name);

    UNITY_BEGIN();
    // Verify that the required defines for conditional compilation are active
    RUN_TEST(test_check_mode_defines_enabled);

    // Simulated test (not readed values) that the function to read the pots is
    // correctly detecting when they are connected, disconnected, in range and out of range.
    RUN_TEST(test_pots_connected);
    RUN_TEST(test_pots_disconnected);

    RUN_TEST(test_pots_inRange);
    RUN_TEST(test_pots_NotInRange);

    // Simulated test to check the right reaction of safety routines when:
    // * Horizontal or vertical joystick, accelerator or brake pedals are disconnected.
    RUN_TEST(test_aplicarRutinasSeguridad_JoystickX_Desconectado);
    RUN_TEST(test_aplicarRutinasSeguridad_JoystickY_Desconectado);
    RUN_TEST(test_aplicarRutinasSeguridad_Acelerador_Desconectado);
    RUN_TEST(test_aplicarRutinasSeguridad_Freno_Desconectado);

    RUN_TEST(test_aplicarRutinasSeguridad_JoystickX_OutOfRange);
    RUN_TEST(test_aplicarRutinasSeguridad_JoystickY_OutOfRange);

    // * Several elements disconnected.
    RUN_TEST(test_aplicarRutinasSeguridad_Joystick_Desconectado); // Both axis of joystick
    RUN_TEST(test_aplicarRutinasSeguridad_Actuadores_Desconectados); // Both pedals

    // * Joystick disconnected and pedals out of range.
    RUN_TEST(test_aplicarRutinasSeguridad_JoystickDesconectado_ActuadoresFueraRango);

    UNITY_END();
    //return 0;
}

void loop()
{

}


#ifndef TESTING_HPP
#define TESTING_HPP

#include "Seguridad.hpp"
#include "LecturaFeedback.hpp"

// Definir una secuencia de control.

#define TESTING_ACTIVADO 0

uint16_t tiempoAceleradorActivado = 2000; //ms
uint16_t tiempoFrenoActivado = 2000;
uint16_t tiempoVolanteIzActivado = 2600;
uint16_t tiempoFrenadoVolante = 800;
uint16_t tiempoVolanteDerActivado = 2600;


uint16_t nIteraciones_a = tiempoAceleradorActivado / periodoDeseado;
uint16_t nIteraciones_f = tiempoFrenoActivado / periodoDeseado;
uint16_t nIteraciones_vi = tiempoVolanteIzActivado  / periodoDeseado;
uint16_t nIteraciones_vFrenado = tiempoFrenadoVolante / periodoDeseado;
uint16_t nIteraciones_vd = tiempoVolanteDerActivado / periodoDeseado;

uint16_t total = nIteraciones_a + nIteraciones_f + nIteraciones_vi + nIteraciones_vFrenado + nIteraciones_vd;
uint16_t contTesting = 0;

void Leer_Joystick_Virtual()
{
    if(contTesting <= nIteraciones_a) // Activar el acelerador a full durante n_a iteraciones
    {
        Joystick_Y = joyY_MaxVal;
        Joystick_X = joyX_Center;
    }
    else if(contTesting <= (nIteraciones_a + nIteraciones_f)) // Activar el freno a full durante n_f iteraciones
    {
        Joystick_Y = joyY_MinVal;
        Joystick_X = joyX_Center;
    }
    else if(contTesting <= (nIteraciones_a + nIteraciones_f + nIteraciones_vi)) // Activar el volante a la izquierda a full durante n_i iteraciones
    {
        Joystick_Y = joyY_Center;
        Joystick_X = joyX_MinVal;
    }
    else if(contTesting <= (nIteraciones_a + nIteraciones_f + nIteraciones_vi + nIteraciones_vFrenado))
    {
        Joystick_Y = joyY_Center;
        Joystick_X = joyX_Center;
    }
    else if(contTesting <= total) // Activar el volante a la derecha a full durante n_d iteraciones
    {
        Joystick_Y = joyY_Center;
        Joystick_X = joyX_MaxVal;
    }
    else if(contTesting > total)
    {
        contTesting = 0;
    }

    contTesting++;
}



#endif // TESTING_HPP

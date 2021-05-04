#ifndef LECTURAFEEDBACK
#define LECTURAFEEDBACK

#include <Arduino.h>
#include "DigitalFilter.hpp"
//#include "Config.hpp"
//#include "Debug.hpp"
#include "ComunicacionSerial.hpp"

#include "Seguridad.hpp"
#include "Testing.hpp"
//

///************************Variables configuración********************///
/// Rango del joystick (Valores experimentales)
/* // * +Joystick Adafruit (10k)

// ** Eje-Y (Acelerador y freno).


int joyForward_minVal = 507;
int joyForward_maxVal = 1023;

int joyBackward_minVal = 0;
int joyBackward_maxVal = 506;

// ** Eje-X (Volante)
int joyDirectionCenter = 520;  //Centro del joystick.
int joyMaximoIzquierda = 4;
int joyMaximoDerecha = 1014;
int joyIzquierdaMedio = (joyDirectionCenter - joyMaximoIzquierda)/2;
int joyDerechaMedio = (joyMaximoDerecha - joyDirectionCenter)/2 + joyDirectionCenter;
*/

// * +Joytick Parallax (5k)
// ** Eje Y (Acelerador y freno).
int joyY_MaxVal = 647;
int joyY_Center = 514;
int joyY_MinVal = 384;
int joyY_FrenoCambios = 450;

// ** Eje X (Volante)
int joyX_MinVal = 387;  // Izquierda
int joyX_Center = 512;  // Centro del joystick.
int joyX_MaxVal = 643;  // Derecha

// Definir relación por segmentos
int totalSegmentoIzq = joyX_Center - joyX_MinVal;
int totalSegmentoDer = joyX_MaxVal - joyX_Center;

float joy_percentSegmento1 = 0.6;
int joyIzq_Segmento1 = joyX_Center - (float)totalSegmentoIzq * joy_percentSegmento1;
int joyDer_Segmento1 = joyX_Center + (float)totalSegmentoDer * joy_percentSegmento1;

//int joyIzquierda_Segmento1 =   joyMaximoIzquierda  +  (joyDirectionCenter - joyMaximoIzquierda)*1/3;
//int joyDerecha_Segmento1 =     joyDirectionCenter  +  (joyMaximoDerecha - joyDirectionCenter)*2/3;

int umbral_lectura_joystick = 1; //Valor para evitar mover los actuadores con valores muy pequeños en el potenciometro del joystick
int umbral_Lectura_JoyX = 2;

/*
Joystick Parallax

    + Joystick X
   387                              512                              643
  Mínimo                 Izq1      Centro     Der1                  Máximo
    |------------.-------------------|--------------------.----------|

Mínimo: joyMaximoIzquierda    Centro: joyDirectionCenter    Máximo: joyMaximoDerecha


    + Joystick Y
 - Máximo: joyY_MaxVal
 |
 |
 -
 |
 |
 -
 |
 |
 - Centro:
 |
 |
 -
 |
 |
 -
 |
 |
 - Mínimo

*/
///************************Fin Variables configuración********************///

///**********************Variables de programa****************************///
int Joystick_X;
int Joystick_Y;
int ActuadorFreno_Posicion;
int ActuadorAcelerador_Posicion;
///**********************Fin Variables de programa************************///


void Leer_Joystick()
{
#if TESTING_ACTIVADO
    Leer_Joystick_Virtual();
#else
    ////Leer potenciómetros del joystick y aplicar filtrado
    int joystick1_Y = analogRead(A0); //A0 Eje Y del Joystick (Aceleracion y Freno)
    smoothJS_Y = digitalSmooth(joystick1_Y, joy_Y_SmoothArray);
    Joystick_Y = smoothJS_Y;

    int joystick1_X = analogRead(A1); //A1 Eje X del Joystick (Direccion).
    smoothJS_X = digitalSmooth(joystick1_X, joy_X_SmoothArray);
    Joystick_X = smoothJS_X;
#endif
}

void Leer_Feedback()
{
    #if FRENO_ACTIVADO
    if(ActuadorFreno_TipoFeedback == TipoFeedback::ResistenciaVariable)
    {
        int act1_PosRaw = analogRead(A2); //Freno
        smoothAct1 = digitalSmooth(act1_PosRaw, act1SmoothArray);
        ActuadorFreno_Posicion = smoothAct1;
    }
    else if(ActuadorFreno_TipoFeedback == TipoFeedback::EncoderIncremental)
    {
        recvWithEndMarker();
        //recvCharsWithStartEndMarkers();
        recuperarValorNumerico(&ActuadorFreno_Posicion);
    }
    else
    {
        Serial.println("WARNING: No se ha definido el tipo de Feedback del actuador del freno.");
        Serial.println("Se definirá Resistencia varible por defecto.");
        ActuadorFreno_TipoFeedback = TipoFeedback::ResistenciaVariable;
    }
    #endif

    //#if ACELERADOR_ACTIVADO
    int act2_PosRaw = analogRead(A3); //Acelerador
    smoothAct2 = digitalSmooth(act2_PosRaw, act2SmoothArray);
    ActuadorAcelerador_Posicion = smoothAct2;
    //#endif

}


#endif

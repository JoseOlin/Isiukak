#ifndef LECTURAJOYSTICK
#define LECTURAJOYSTICK

#include <Arduino.h>
#include "DigitalFilter.hpp"
#include "ComunicacionSerial.hpp"


///************************Variables configuración********************///
///Rango del joystick (Valores experimentales)
//***** Joystick Adafruit (10k)
//** Eje-Y (Acelerador y freno).
/*

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

//***** Joytick Parallax (5k)
//** Eje Y (Acelerador).
int joyY_MaxVal = 647;
int joyY_Center = 514;
int joyY_MinVal = 384;

//** Eje X (Freno)
int joyX_MinVal = 387;  // Left.
int joyX_Center = 512;  // Centro del joystick.
int joyX_MaxVal = 643;  // Right.

//Definir relación por segmentos
//int totalSegmentoIzq = joyDirectionCenter - joyMaximoIzquierda;
//int totalSegmentoDer = joyMaximoDerecha - joyDirectionCenter;

//float joy_percentSegmento1 = 0.375;
//int joyIzq_Segmento1 = joyDirectionCenter - (float)totalSegmentoIzq*joy_percentSegmento1;
//int joyDer_Segmento1 = joyDirectionCenter + (float)totalSegmentoDer*joy_percentSegmento1;

//int joyIzquierda_Segmento1 =   joyMaximoIzquierda  +  (joyDirectionCenter - joyMaximoIzquierda)*1/3;
//int joyDerecha_Segmento1 =     joyDirectionCenter  +  (joyMaximoDerecha - joyDirectionCenter)*2/3;

int umbral_lectura_joystick = 1; //Valor para evitar mover los actuadores con valores muy pequeños en el potenciometro del joystick

/// Rango de los actuadores.
// Actuador del freno (GoBilda, encoder incremental)
// Partiendo de estar totalmente retraído a estar totalmente extendido
// 833 pulsos.

enum TipoFeedback{ResistenciaVariable, EncoderIncremental};
//TipoFeedback ActuadorFreno_TipoFeedback = TipoFeedback::EncoderIncremental;
TipoFeedback ActuadorFreno_TipoFeedback = TipoFeedback::ResistenciaVariable;
////////////////////////////////////////////////////////////////////////

int Joystick_X;
int Joystick_Y;
int ActuadorFreno_Posicion;
int ActuadorAcelerador_Posicion;

/*
Joystick Parallax
    + Joystick X
   387                              512                              643
  Mínimo                 Izq1      Centro     Der1                  Máximo
    |----------.----------.----------|----------.----------.----------|

  Mínimo: joyMaximoIzquierda    Centro: joyDirectionCenter    Máximo: joyMaximoDerecha

    + Joystick Y
 - Máximo: joyForward_maxVal
 |
 |
 -
 |
 |
 -
 |
 |
 - Centro
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

//int

///************************Fin Variables configuración********************///



//Leer potenciómetros del joystick y los actuadores, así como el encoder del freno.
void Leer_Feedback()
{
    /// Lectura de potenciómetros de feedback del joystick y los actuadores.

    ////Leer potenciómetros del joystick y aplicar filtrado
    int joystick1_Y = analogRead(A0); //A0 para el Pot de Aceleracion y Freno
    // Small pause is needed between reading analog pins, otherwise we get the same value twice
    // Buscar el delay mínimo.
    smoothJS_Y = digitalSmooth(joystick1_Y, joy_Y_SmoothArray);
    Joystick_Y = smoothJS_Y;
    // this small pause is needed between reading analog pins, otherwise we get the same value twice

    int joystick1_X = analogRead(A1); //A1 para el Pot de la direccion.
    smoothJS_X = digitalSmooth(joystick1_X, joy_X_SmoothArray);
    Joystick_X = smoothJS_X;
    // small pause is needed between reading analog pins, otherwise we get the same value twice

    //#if FRENO_ACTIVADO
    if(ActuadorFreno_TipoFeedback == TipoFeedback::ResistenciaVariable)
    {
        ////Leer resitencias variables de los actuadores
        int act1_PosRaw = analogRead(A2); //Freno
        smoothAct1 = digitalSmooth(act1_PosRaw, act1SmoothArray);
        ActuadorFreno_Posicion = smoothAct1;
    }
    else if(ActuadorFreno_TipoFeedback == TipoFeedback::EncoderIncremental)
    {
        /*if(Serial.available())
        {
            //ActuadorFreno_Posicion = Serial.parseInt();
            // TODO : Revisar cómo funciona la función parseInt
            // La función parseInt bloquea el arduino hasta que es satisfecha, así que no nos sirve para esta aplicación.
            ActuadorFreno_Posicion = Serial.read();
            Serial.read(); //Para eliminar el salto de línea.
        }*/
        recvWithEndMarker();
        recuperarValorNumerico(&ActuadorFreno_Posicion);
    }
    else
    {
        Serial.print("ERROR: No se ha definido el tipo de Feedback del actuador del freno.");
    }
      //#endif

    //#if ACELERADOR_ACTIVADO
    int act2_PosRaw = analogRead(A3); //Acelerador
    smoothAct2 = digitalSmooth(act2_PosRaw, act2SmoothArray);
    ActuadorAcelerador_Posicion = smoothAct2;
    //#endif
}


#endif

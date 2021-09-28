#ifndef LECTURAFEEDBACK
#define LECTURAFEEDBACK

#include <Arduino.h>
#include "DigitalFilter.hpp"
#include "Config.hpp"
//#include "Debug.hpp"
#include "ComunicacionSerial.hpp"

#include "Seguridad.hpp"
//#include "Testing.hpp"


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
// Valores con 5V virtual directo en las salidas digitales
int joyY_MaxVal = 639;
int joyY_Center = 509;
int joyY_MinVal = 374;
int joyY_FrenoCambios = 450;


/* // Valores con transistores conectados a las salidas
int joyY_MaxVal = 567;
int joyY_Center = 451;
int joyY_MinVal = 331;
int joyY_FrenoCambios = 525; */

// ** Eje X (Volante)
// Valores con 5V virtual directo en las salidas digitales
int joyX_MinVal = 377;  //
int joyX_Center = 510;  //
int joyX_MaxVal = 636;  //

/* // Valores con transistores conectados a las salidas
int joyX_MinVal = 334;
int joyX_Center = 452;
int joyX_MaxVal = 564;*/

int joystickUmbralErrorCentrado = 10; //Umbral de error para la verificación de arranque.
int joystick_UmbralFueraRango = 10;

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


uint16_t tiempoAceleradorActivado = 2000; //ms
uint16_t tiempoFrenoActivado = 2000;
uint16_t tiempoVolanteIzActivado = 2600;
uint16_t tiempoFrenadoVolante = 800;
uint16_t tiempoVolanteDerActivado = 2600;


uint16_t nIteraciones_a         = tiempoAceleradorActivado / periodoDeseado;
uint16_t nIteraciones_f         = tiempoFrenoActivado / periodoDeseado;
uint16_t nIteraciones_vi        = tiempoVolanteIzActivado  / periodoDeseado;
uint16_t nIteraciones_vInhibido = tiempoFrenadoVolante / periodoDeseado;
uint16_t nIteraciones_vd        = tiempoVolanteDerActivado / periodoDeseado;

uint16_t nSumIteraciones_f          = nIteraciones_a            +   nIteraciones_f;
uint16_t nSumIteraciones_vi         = nSumIteraciones_f         +   nIteraciones_vi;
uint16_t nSumIteraciones_vInhibido  = nSumIteraciones_vi        +   nIteraciones_vInhibido;
uint16_t nSumIteraciones_vd         = nSumIteraciones_vInhibido +   nIteraciones_vd;


uint16_t total = nIteraciones_a + nIteraciones_f + nIteraciones_vi + nIteraciones_vInhibido + nIteraciones_vd;
uint16_t contTesting = 0;

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
///***********************************************************************///


///***********************************************************************///
///**********************Variables de programa****************************///
int pinJoystickY = A0;
int pinJoystickX = A1;
int pinActFreno  = A2;
int pinActAcel   = A3;

int pinFijarPosicionFreno = 10; //10
int pinSubirPalanca = A5; //A5
int pinBajarPalanca = 11; //11
int pinModoCarretera = A4; //A4

int pinParoManualEmergencia = 9;



int Joystick_X;
int Joystick_Y;
int ActuadorFreno_Posicion;
int ActuadorAcelerador_Posicion;

uint8_t subirPalanca;
uint8_t bajarPalanca;
uint8_t fijarPosicionFreno = 0;
uint8_t modoCarreteraActivado = 0;

void Leer_Joystick_Virtual();
///**********************Fin Variables de programa************************///
///***********************************************************************///


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
    /*else if(ActuadorFreno_TipoFeedback == TipoFeedback::EncoderIncremental)
    {
        recvWithEndMarker();
        //recvCharsWithStartEndMarkers();
        recuperarValorNumerico(&ActuadorFreno_Posicion);
    }*/
    else
    {
        //Serial.println("**WARNING: No se ha definido el tipo de Feedback del actuador del freno.");
        //Serial.println("Se definirá Resistencia varible por defecto.");
        ActuadorFreno_TipoFeedback = TipoFeedback::ResistenciaVariable;
    }
#endif

#if ACELERADOR_ACTIVADO
    int act2_PosRaw = analogRead(A3); //Acelerador
    smoothAct2 = digitalSmooth(act2_PosRaw, act2SmoothArray);
    ActuadorAcelerador_Posicion = smoothAct2;
#endif

}

void Leer_Botones()
{
    subirPalanca = !digitalRead(pinSubirPalanca);
    bajarPalanca = !digitalRead(pinBajarPalanca);
    fijarPosicionFreno = !digitalRead(pinFijarPosicionFreno);
    modoCarreteraActivado = !digitalRead(pinModoCarretera);
}

/*void pullupsInternos_i2c(boolean habilitar)
{
    if(habilitar)
    {
        pinMode(SDA, INPUT_PULLUP);
        pinMode(SCL, INPUT_PULLUP);
    }
    else
    {
        pinMode(SDA, INPUT);
        pinMode(SCL, INPUT);
        digitalWrite(SDA, LOW);
        digitalWrite(SCL, LOW);
    }
}
*/


void Leer_Joystick_Virtual()
{
    if(contTesting == 0)
    {
        Serial.println("Iniciando la prueba con valores virtuales del Joystick.");
        Serial.println("ESTA PRUEBA SÓLO DEBE HACERSE CON EL SISTEMA DESINSTALADO DEL CARRO.");

    }
    if(contTesting <= nIteraciones_a) // Activar el acelerador a full durante n_a iteraciones
    {
        if(contTesting == 0)
        {
            Serial.println("Acelerador a full...");
        }
        Joystick_Y = joyY_MaxVal;
        Joystick_X = joyX_Center;
    }
    else if(contTesting <= nSumIteraciones_f) // Activar el freno a full durante n_f iteraciones
    {
        if(contTesting == nIteraciones_a + 1)
        {
            Serial.println("Freno a full...");
        }
        Joystick_Y = joyY_MinVal;
        Joystick_X = joyX_Center;
    }
    else if(contTesting <= nSumIteraciones_vi) // Activar el volante a la izquierda a full durante n_i iteraciones
    {
        if(contTesting == nSumIteraciones_f + 1)
        {
            Serial.println("Volante a la izquierda a full...");
        }
        Joystick_Y = joyY_Center;
        Joystick_X = joyX_MinVal;
    }
    else if(contTesting <= nSumIteraciones_vInhibido)
    {
        if(contTesting == nSumIteraciones_f + 1)
        {
            Serial.println("Volante detenido...");
        }
        Joystick_Y = joyY_Center;
        Joystick_X = joyX_Center;
    }
    else if(contTesting <= nSumIteraciones_vd) // Activar el volante a la derecha a full durante n_d iteraciones
    {
        if(contTesting == nSumIteraciones_vInhibido + 1)
        {
            Serial.println("Volante a la derecha...");
        }
        Joystick_Y = joyY_Center;
        Joystick_X = joyX_MaxVal;
    }
    else if(contTesting > nSumIteraciones_vd)
    {
        contTesting = 0;
    }

    contTesting++;
}

#endif

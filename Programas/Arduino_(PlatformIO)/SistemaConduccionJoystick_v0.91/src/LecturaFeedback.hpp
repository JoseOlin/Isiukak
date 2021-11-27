#ifndef LECTURAFEEDBACK
#define LECTURAFEEDBACK

#include "DigitalFilter.hpp"
#include "ComunicacionSerial.hpp"

#include "Config.hpp"



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

int pinFijarPosicionFreno = 10;
int pinSubirPalanca = A5;
int pinBajarPalanca = 11;
int pinModoCarretera = A4;

/*int pinFijarPosicionFreno = 10;
int pinSubirPalanca = A5;
int pinBajarPalanca = A4;
int pinModoCarretera = 11;*/

int pinBotonParoEmergencia = 9;


int Joystick_X;
int Joystick_Y;
int ActuadorFreno_Posicion;
int ActuadorAcelerador_Posicion;

uint8_t SubirPalanca;
uint8_t BajarPalanca;
uint8_t FijarPosicionFreno;
uint8_t ModoCarreteraActivado;

unsigned int PotenciometrosVirtuales[4] = {0,    0,   0,    0};
unsigned int PotenciometrosVirtuales_ValidacionConexion[2][4] = {   {0,    0,   0,    0},
                                                                    {1023, 1023, 1023, 1023}};
uint8_t PinesDigitales_ValoresVirtuales[4] = {LOW,      LOW,    LOW,    LOW};


///**********************Fin Variables de programa************************///
///***********************************************************************///




void Joystick_Leer()
{
    int joystick1_Y;
    int joystick1_X;

    ////Leer potenciómetros del joystick
    joystick1_Y = analogRead(A0); //A0 Eje Y del Joystick (Aceleracion y Freno)
    joystick1_X = analogRead(A1); //A1 Eje X del Joystick (Direccion).

    /// Aplicar filtrado
    smoothJS_Y = digitalSmooth(joystick1_Y, joy_Y_SmoothArray);
    Joystick_Y = smoothJS_Y;

    smoothJS_X = digitalSmooth(joystick1_X, joy_X_SmoothArray);
    Joystick_X = smoothJS_X;
}

void Actuadores_Feedback_Leer()
{

#if FRENO_ACTIVADO
    int act1_PosRaw = analogRead(A2); //Freno
    smoothAct1 = digitalSmooth(act1_PosRaw, act1SmoothArray);
    ActuadorFreno_Posicion = smoothAct1;
#endif

#if ACELERADOR_ACTIVADO
    int act2_PosRaw = analogRead(A3); //Acelerador
    smoothAct2 = digitalSmooth(act2_PosRaw, act2SmoothArray);
    ActuadorAcelerador_Posicion = smoothAct2;
#endif
}


void Leer_Botones()
{
    SubirPalanca = !digitalRead(pinSubirPalanca);
    BajarPalanca = !digitalRead(pinBajarPalanca);
    FijarPosicionFreno = !digitalRead(pinFijarPosicionFreno);
    ModoCarreteraActivado = !digitalRead(pinModoCarretera);
}


void desplegarInfoJoystick()
{
#if INFO_JOYSTICK
    Serial.print("J_Y: ");  Serial.print(Joystick_Y);
    Serial.print(",\tJ_X: "); Serial.print(Joystick_X);
#endif

}

void desplegarInfoBotones()
{
#if INFO_BOTONES
    Serial.print(",\tbFB: "); Serial.print(FijarPosicionFreno); //button Fix Brake
    Serial.print(", bPU: "); Serial.print(SubirPalanca); // button Palanca Up
    Serial.print(", bPD: "); Serial.print(BajarPalanca);// button Palanca Down
    Serial.print(", bMC: "); Serial.print(ModoCarreteraActivado); //button Modo Carretera
#endif
}


void leerFeedback()
{
    Joystick_Leer();
    Leer_Botones();

    Actuadores_Feedback_Leer();
}

void Feedback_fillBuffer()
{
    // Para llenar el arreglo que se utiliza para filtrar la señal y evitar el
    // movimiento brusco de los actuadores al arranque.
    for(int ii = 0; ii < filterSamples + 1; ii++)
    {
        Joystick_Leer();
        Actuadores_Feedback_Leer();
    }
}




#endif

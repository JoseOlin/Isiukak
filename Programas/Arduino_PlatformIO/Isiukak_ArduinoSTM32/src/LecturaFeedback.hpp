#ifndef LECTURAFEEDBACK
#define LECTURAFEEDBACK

#include "DigitalFilter.hpp"
#include "ComunicacionSerial.hpp"
#include "Config.hpp"
#include "Actuators.hpp"
//#include "ControlPedales.hpp"

///************************Variables configuración********************///
int pinJoystickY = A0; //PA0
int pinJoystickX = A1; //PA1
int pinActFreno  = A2; //PA4
int pinActAcel   = A3; //PB0

int pinBotonParoEmergencia = D9; //PC7

int pinFijarPosicionFreno = D10; //PB6
int pinBajarPalanca = D11;      //PA7
int pinSubirPalanca = PC3; //Se usaban pines analógicos, ahora se usan pines digitales Morpho
int pinModoCarretera = PC2;

/// Rango del joystick (Valores experimentales)
/* Joystick Parallax en ST NUCLEO F40*/
// ** Eje Y (Acelerador y freno).
uint8_t JoystickActivado = false;


int joyY_MaxVal = 640; // joyY_Center +
int joyY_Center = 511;
int joyY_MinVal = 376;
int joyY_FrenoCambios = 512; //DEjarlo libre.

// ** Eje X (Volante)
int joyX_MaxVal = 635;  //
int joyX_Center = 510;  //
int joyX_MinVal = 377;  //


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

/* Joystick Parallax

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



int Joystick_X;
int Joystick_X_Raw;
int Joystick_Y;
int Joystick_Y_Raw;

int ActuadorFreno_Posicion;
int ActuadorFreno_Posicion_Raw;
int ActuadorAcelerador_Posicion;
int ActuadorAcelerador_Posicion_Raw;

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


void Joystick_Read()
{

    ////Leer potenciómetros del joystick
    Joystick_Y_Raw = analogRead(pinJoystickY);
    Joystick_X_Raw = analogRead(pinJoystickX);

    /// Aplicar filtrado
    smoothJS_Y = digitalSmooth(Joystick_Y_Raw, joy_Y_SmoothArray);
    Joystick_Y = smoothJS_Y;

    smoothJS_X = digitalSmooth(Joystick_X_Raw, joy_X_SmoothArray);
    Joystick_X = smoothJS_X;
}

void Actuators_Feedback_Read()
{
    ActuadorFreno_Posicion_Raw = analogRead(pinActFreno); //Freno
    smoothAct1 = digitalSmooth(ActuadorFreno_Posicion_Raw, act1SmoothArray);
    ActuadorFreno_Posicion = smoothAct1;

    ActuadorAcelerador_Posicion_Raw = analogRead(pinActAcel); //Acelerador
    smoothAct2 = digitalSmooth(ActuadorAcelerador_Posicion_Raw, act2SmoothArray);
    ActuadorAcelerador_Posicion = smoothAct2;
}


void Buttons_Read()
{
    FijarPosicionFreno = !digitalRead(pinFijarPosicionFreno);
    //FijarPosicionFreno = !FijarPosicionFreno;
    BajarPalanca = !digitalRead(pinBajarPalanca);
    SubirPalanca = !digitalRead(pinSubirPalanca);
    ModoCarreteraActivado = !digitalRead(pinModoCarretera);
}


void desplegarInfoJoystick()
{
#if INFO_JOYSTICK
    Serial.print("J_Y: ");  Serial.print(Joystick_Y);
    Serial.print(",\tJ_X: "); Serial.print(Joystick_X);

    #if JOYSTICK_ACTIVADO
    Serial.print(",  J_ac: 1");
    #endif
#endif
}

void desplegarInfoJoystick_Raw()
{
    #if INFO_JOYSTICK
    Serial.print("J_Y_Raw: ");  Serial.print(Joystick_Y_Raw);
    Serial.print(",\tJ_X_Raw: "); Serial.print(Joystick_X_Raw);
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


void Actuators_Drivers_Read()
{
#if INFO_MOTOR_DRIVERS
    counterIterationsToDriversReading++;

    if(counterIterationsToDriversReading >= IterationsToDriversReading)
    {
        ActuatorBrake_Driver.readStatus();
        ActuatorAccel_Driver.readStatus();
        ActuatorSteer_Driver.readStatus();

        //counterIterationsToDriversReading = 0; // Reset on MotorDriver::displayInfo()
        //displayInfo() must be called after this function.
    }
#endif
}

void leerFeedback()
{
    Joystick_Read();
    Buttons_Read();

    Actuators_Feedback_Read();

    Actuators_Drivers_Read();
}

void Feedback_fillBuffer()
{
    // Para llenar el arreglo que se utiliza para filtrar la señal y evitar el
    // movimiento brusco de los actuadores al arranque.
    for(int ii = 0; ii < filterSamples + 1; ii++)
    {
        Joystick_Read();
        Actuators_Feedback_Read();
    }
}




#endif

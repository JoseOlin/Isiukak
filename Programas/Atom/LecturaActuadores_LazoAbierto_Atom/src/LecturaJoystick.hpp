#ifndef LECTURAJOYSTICK
#define LECTURAJOYSTICK

#include "DigitalFilter.hpp"


///************************Variables configuración********************
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
//** Eje Y (Acelerador y freno).
int joyForward_maxVal = 647;
int joyForward_minVal = 514;

int joyBackward_maxVal = 514;
int joyBackward_minVal = 384;

//** Eje X (Volante)
int joyMaximoIzquierda = 387;
int joyDirectionCenter = 512;  //Centro del joystick.
int joyMaximoDerecha = 643;

//int joyIzquierdaMedio = (joyDirectionCenter - joyMaximoIzquierda)/2 + joyMaximoIzquierda;
//int joyDerechaMedio = (joyMaximoDerecha - joyDirectionCenter)/2 + joyDirectionCenter;
int joyIzquierdaMedio =   joyMaximoIzquierda  +  (joyDirectionCenter - joyMaximoIzquierda)*1/3;
int joyDerechaMedio =     joyDirectionCenter  +  (joyMaximoDerecha - joyDirectionCenter)*2/3;


int umbral_lectura_joystick = 1; //Valor para evitar mover los actuadores con valores muy pequeños en el potenciometro del joystick
/////*********************************************************************



//Leer potenciómetros del joystick y los actuadores.
void Leer_JoystickActuadores()
{
  ////Leer potenciómetros del joystick y aplicar filtrado
  int joystick1_Y = analogRead(A0); //A0 para el Pot de Aceleracion y Freno
  smoothJS_Y = digitalSmooth(joystick1_Y, joy_Y_SmoothArray);
  // this small pause is needed between reading analog pins, otherwise we get the same value twice

  int joystick1_X = analogRead(A1); //A1 para el Pot de la direccion.
  smoothJS_X = digitalSmooth(joystick1_X, joy_X_SmoothArray);
  // small pause is needed between reading analog pins, otherwise we get the same value twice

  //#if FRENO_ACTIVADO
  ////Leer resitencias variables de los actuadores
  int act1_PosRaw = analogRead(A2); //Freno
  smoothAct1 = digitalSmooth(act1_PosRaw, act1SmoothArray);
  // small pause is needed between reading analog pins, otherwise we get the same value twice
  //#endif

  //#if ACELERADOR_ACTIVADO
  int act2_PosRaw = analogRead(A3); //Acelerador
  smoothAct2 = digitalSmooth(act2_PosRaw, act2SmoothArray);
  //#endif

}


#endif

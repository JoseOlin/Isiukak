#ifndef CONTROLACTUADORES
#define CONTROLACTUADORES

#include "LecturaJoystick.hpp"
#include "DigitalFilter.hpp"
#include "DriversMotores.hpp"
#include "Debug.hpp"

//************************ Variables configuración *****************************
/***Considerando que el actuador no se utilizara en todo su rango
se define una constante de mapeo.***/
////Encontrar valores con pruebas en ControlActuadores_Joystick_NoRetro

//Freno.
int actFreno_valorParoEmergencia = 400;
// Extendido 28 - 1009 Retraido.
// Primero considerar carrera completa. Despues considerar carrera de 8 cm en lugar de los 10 posibles (1009/10*8 = 807.2)
//int actFreno_minVal = 28;   // Extendido.
int actFreno_valorExtendido = 400; //Buscar la extensión máxima que puede tener el actuador sin forzar el pedal.

//int actFreno_maxVal = 900; // Retraido.
int actFreno_valorRetraido = 1010;
//Diferencia 900-28 = 872

//Acelerador.
// Extandido  28  -  965 Retraido.
#define ACELERADOR_MAPEO_MEDIO 650     //A menor valor, mas extensión.
#define ACELERADOR_MAPEO_COMPLETO 392

//int actAcel_minVal = 28;
//int actAcel_minVal = 150; //Volver a activar despues de las pruebas
int actAcel_valorExtendido = 392;
//int act2_minVal = 350;  // Extendido.
int actAcel_valorRetraido = 938; //Retraido. El acelerador esta inicialmente ligeramente extendido,
                          //para que quede en contacto con el acelerador.
//int act2_maxVal = 965;
//Diferencia 380 - 200 = 180,    380 - 120 = 260. Nuevo valor.



uint8_t mapeoCompletoAcelerador = 0;
///Valores de umbral para aplicar control.
int umbral_error_actuadores = 3; //Valor mínimo de error en la posición de los actuadores de los pedales.


//************************///////////////////////*******************************


///*****************Variables del programa***********************
//*** Constantes de control PID de los actuadores lineales.
//int Kp = 20; //Buscar adecuada
int Kp = 25;
int Ki = 1;
float Kd = 0;

int acel_posDeseada = 0;
int freno_posDeseada = 0;
int error_acel;
int error_freno;
int controlAcel, controlFreno;
//***************************************************************



void setMotorSpeed_Protocol(int address, int speed);


void ControlarPedales()
{
  //Control del acelerador.
  if(smoothJS_Y > (joyForward_minVal + umbral_lectura_joystick) ) //Se quiere acelerar
  {
    freno_posDeseada = actFreno_valorRetraido; //Valor del actuador retraido.

    acel_posDeseada = map(smoothJS_Y,   joyForward_minVal, joyForward_maxVal,
                                        actAcel_valorRetraido, actAcel_valorExtendido);

  } //Control del freno.
  else if(smoothJS_Y < (joyBackward_maxVal - umbral_lectura_joystick) ) //Se quiere frenar.
  {
    acel_posDeseada = actAcel_valorRetraido;//Valor del actuador retraido.
    //                             x            0                  512
    freno_posDeseada = map(smoothJS_Y, joyBackward_minVal, joyBackward_maxVal,
                                            //28          1009
                                        actFreno_valorExtendido, actFreno_valorRetraido); //Mapeo directo (si el joystick aumenta el valor del actuador aumenta)
    /*
    512-3 = 509 -> Freno casi totalmente retraido  (~1009)
              0 -> Freno totalmente extendido      (28)
    */
  }
  else //El joystick esta centrado. Retraer ambos actuadores.
  {
    freno_posDeseada = actFreno_valorRetraido; //Retraer completamente el freno.
    acel_posDeseada = actAcel_valorRetraido; //Retraer completamente el acelerador.
  }

  //Calcular valores de control con retroalimentacion
  error_freno = smoothAct1 - freno_posDeseada; //
  controlFreno = error_freno*Kp;

  error_acel = acel_posDeseada - smoothAct2; //
  //error_acel = smoothAct2 - acel_posDeseada;
  controlAcel = -error_acel * Kp;//

  //Controlar el freno.
  if(error_freno > umbral_error_actuadores || error_freno < -umbral_error_actuadores)
    setMotorSpeed_Protocol(frenAddress, controlFreno);
  else
    setMotorSpeed_Protocol(frenAddress, 0);

  //Controlar el acelerador.
  if(error_acel > umbral_error_actuadores || error_acel < -umbral_error_actuadores)
    setMotorSpeed_Protocol(acelAddress, controlAcel);
  else
    setMotorSpeed_Protocol(acelAddress, 0);
}

#endif

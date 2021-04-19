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
int actFreno_valorParoEmergencia = 75;
// Extendido 28 - 1009 Retraido.
// Primero considerar carrera completa. Despues considerar carrera de 8 cm en lugar de los 10 posibles (1009/10*8 = 807.2)
//int actFreno_minVal = 28;   // Extendido.
int actFreno_valorExtendido = 137; //Buscar la extensión máxima que puede tener el actuador sin forzar el pedal.

//int actFreno_maxVal = 900; // Retraido.
int actFreno_valorRetraido = 1009;
//Diferencia 900-28 = 872

//Acelerador.
// Extandido  28  -  965 Retraido.
#define ACELERADOR_MAPEO_MEDIO 785     //A menor valor, mas extensión.
#define ACELERADOR_MAPEO_COMPLETO 705

//int actAcel_minVal = 28;
//int actAcel_minVal = 150; //Volver a activar despues de las pruebas
int actAcel_valorExtendido = 785;
//int act2_minVal = 350;  // Extendido.
int actAcel_valorRetraido = 965; //Retraido. El acelerador esta inicialmente ligeramente extendido,
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

int acel_velDeseada = 0;
int freno_velDeseada = 0;
//***************************************************************



void setMotorSpeed_Protocol(int address, int speed);


void ControlarPedales()
{

    if(smoothJS_X < (joyDirectionCenter-umbral_lectura_joystick)   )//Joystick a la izquierda, mover freno
    {
        //Control de la velocidad del actuador del freno.
        if ( smoothJS_Y > (joyForward_minVal + umbral_lectura_joystick) ) //Se quiere extender el actuador
        {
          freno_velDeseada = map(smoothJS_Y,   joyForward_minVal, joyForward_maxVal, 0, 3200);
        }
        else if(smoothJS_Y < (joyBackward_maxVal - umbral_lectura_joystick) ) //Se quiere contraer el actuador
        {
          freno_velDeseada = map(smoothJS_Y, joyBackward_minVal, joyBackward_maxVal,-3200 , 0);
        }
    }
    else if (smoothJS_X > (joyDirectionCenter+umbral_lectura_joystick)) //Joystick a la derecha, mover acelerador.
    {
        //Control de la velocidad del actuador del acelerador.
        if(smoothJS_Y > (joyForward_minVal + umbral_lectura_joystick) ) //Se quiere extender el actuador
        {
          acel_velDeseada = map(smoothJS_Y,   joyForward_minVal, joyForward_maxVal,  0, 3200);
        }
        else if(smoothJS_Y < (joyBackward_maxVal - umbral_lectura_joystick) ) //Se quiere contraer el actuador
        {
          acel_velDeseada = map(smoothJS_Y, joyBackward_minVal, joyBackward_maxVal, -3200 , 0);
        }
    }
    else{
        freno_velDeseada = 0;
        acel_velDeseada = 0;
    }

    //Controlar el freno.
    setMotorSpeed_Protocol(frenAddress, freno_velDeseada);
    //Controlar el acelerador.
    setMotorSpeed_Protocol(acelAddress, acel_velDeseada);
}

#endif

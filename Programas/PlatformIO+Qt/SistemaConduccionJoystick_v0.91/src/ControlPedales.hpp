#ifndef CONTROLACTUADORES
#define CONTROLACTUADORES
/* ***************************** /
act1: Freno.           0x0D
act2: Acelerador.      0x0A

act3: Volante.         0x04  (0000 0100)
*/ // ***************************

#include "LecturaFeedback.hpp"
//#include "DigitalFilter.hpp"
#include "DriversMotores.hpp"
#include "Debug.hpp"

//************************ Variables configuración *****************************
/***Considerando que el actuador no se utilizará en todo su rango
se define una constante de mapeo.***/
////Encontrar valores con pruebas en ControlActuadores_Joystick_NoRetro

/// Freno
// (Valores Actuador ServoCity).
/* Extendido 28 - 1009 Retraido.
//Diferencia 1009 - 28 = 981
// Primero considerar carrera completa.
// Despues considerar carrera de 8 cm en lugar de los 10 posibles (1009/10*8 = 807.2)
int actFreno_valorExtendido = 313; //Buscar la extensión máxima que puede tener el actuador sin forzar el pedal.
int actFreno_valorRetraido = 974;

int actFreno_valorParoEmergencia = 313;
*/

// (Valores Actuador GoBilda).
int actFreno_valorExtendido = 800;
int actFreno_valorRetraido = 60;

int actFreno_valorParoEmergencia = 500; // TODO: Buscar la extensión máxima que puede tener el actuador sin forzar el pedal.

///Acelerador.
// Extendido  28  -  965 Retraido.
//Diferencia 1009 - 28 = 937
#define ACELERADOR_MAPEO_MEDIO 650
#define ACELERADOR_MAPEO_COMPLETO 432 //A menor valor, mas extensión.

int actAcel_valorExtendido = 432;
int actAcel_valorRetraido = 980; //Retraido. El acelerador esta inicialmente ligeramente
                            //extendido, para que quede en contacto con el acelerador.

uint8_t modoCarreteraActivado = 0;
///Valores de umbral para aplicar control.
int umbral_errorActuadores;
int umbral_error_acelerador = 3; //Valor mínimo de error en la posición de los actuadores de los pedales.
int umbral_error_freno = 1;



//************************///////////////////////*******************************


///*****************Variables del programa***********************
//*** Constantes de control PID de los actuadores lineales.
//int ActuadorFreno_Kp = 25; // TODO: Optimizar ganancias de control.
int ActuadorFreno_Kp = 17;
int ActuadorFreno_Ki = 1;

int ActuadorAcelerador_PosDeseada = 0;
int ActuadorFreno_PosDeseada = 0;
int ActuadorAcelerador_ErrorPosicion;
int ActuadorFreno_ErrorPosicion;

int ActuadorAcelerador_Kp = 30;
//Señal de control para actuadores de acelerador y freno.
int ActuadorFreno_Control;
int ActuadorAcelerador_Control;

int Kp;

uint8_t fijarPosicionFreno = 0;

enum TipoActuador{Freno, Acelerador, Volante};
//TipoActuador tipoActuador;
//***************************************************************



void moverActuador(TipoActuador tipoActuador, int ErrorPosicion);

void ControlarPedales(uint8_t fijarPosicionFreno)
{
    /*  */
    if(Joystick_Y > (joyY_Center + umbral_lectura_joystick) )
    {   /// Se desea acelerar.
        // Retraer el freno y controlar la posición del acelerador.
        if(!fijarPosicionFreno)
        {
            ActuadorFreno_PosDeseada = actFreno_valorRetraido; //Valor del actuador retraido.
        }

        ActuadorAcelerador_PosDeseada = map(Joystick_Y,   joyY_Center, joyY_MaxVal,
                                        actAcel_valorRetraido, actAcel_valorExtendido);

    }
    else if(Joystick_Y < (joyY_Center - umbral_lectura_joystick) )
    {   /// Se desea frenar.
        //Retraer el acelerador y controlar la posición del freno.
        ActuadorAcelerador_PosDeseada = actAcel_valorRetraido;//Valor del actuador del acelerador retraido.

        if(!fijarPosicionFreno)
        {
            //                             x            0                  512
            int Joystick_Y_PosAbs = joyY_Center - Joystick_Y; //Cuando la posición del joystick decrece la posición deseada del actuador aumenta.
            ActuadorFreno_PosDeseada = map(Joystick_Y_PosAbs,  0, (joyY_Center - joyY_MinVal),
                                                        actFreno_valorRetraido, actFreno_valorExtendido);
        }
        else
        {
            //Si está activado el modo bloqueo no se recalcula la Posición Deseada, se mantiene la anterior.
            #if DEBUG_ACTUADORES_BLOQUEOFRENO
            Serial.print(", Pos. Freno fijada.");
            #endif
        }
    /*
    512-3 = 509 -> Freno casi totalmente retraido  (~1009)
              0 -> Freno totalmente extendido      (28)
    */
    }
    else //El joystick está centrado. Retraer ambos actuadores.
    {
        if(!fijarPosicionFreno)
        {
            ActuadorFreno_PosDeseada = actFreno_valorRetraido; //Retraer completamente el freno.
        }
        ActuadorAcelerador_PosDeseada = actAcel_valorRetraido; //Retraer completamente el acelerador.
    }

    //Calcular valores de control con retroalimentacion
    ActuadorFreno_ErrorPosicion = ActuadorFreno_PosDeseada - ActuadorFreno_Posicion; //
    moverActuador(TipoActuador::Freno, ActuadorFreno_ErrorPosicion);

  //Controlar el acelerador.
#if ACELERADOR_ACTIVADO
    ActuadorAcelerador_ErrorPosicion = ActuadorAcelerador_PosDeseada - ActuadorAcelerador_Posicion;
    moverActuador(TipoActuador::Acelerador, ActuadorAcelerador_ErrorPosicion);
#endif
}

void moverActuador(TipoActuador tipoActuador, int ErrorPosicion)
{
    bool ComportamientoDirecto; //Este comportamiento tiene que ver con la posición de los engranes del motor.
    int address;

    if(tipoActuador == TipoActuador::Freno)
    {
        ComportamientoDirecto = false; //Comportamiento inverso: Valores de control positivos retraen el actuador.
        Kp = ActuadorFreno_Kp;
        address = ActuadorFreno_Address;

    } else if(tipoActuador == TipoActuador::Acelerador){
        ComportamientoDirecto = false;
        Kp = ActuadorAcelerador_Kp;
        address = ActuadorAcelerador_Address;
    }

    int control;
    if(ComportamientoDirecto){
        control = ErrorPosicion * Kp;
    } else {
        control = -(ErrorPosicion * Kp);
    }

    if(tipoActuador == TipoActuador::Freno)
    {
        ActuadorFreno_Control = control;
        umbral_errorActuadores = umbral_error_freno;

    } else if(tipoActuador == TipoActuador::Acelerador)
    {
        ActuadorAcelerador_Control = control;
        umbral_errorActuadores = umbral_error_acelerador;
    }

    if(abs(ErrorPosicion) > umbral_errorActuadores) {
        setMotorSpeed_Protocol(address, control);
    } else{
        setMotorSpeed_Protocol(address, 0);
    }
}


#endif

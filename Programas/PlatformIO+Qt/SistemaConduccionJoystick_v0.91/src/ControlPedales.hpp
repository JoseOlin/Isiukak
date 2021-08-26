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

///************************ Variables configuración ***********************************///
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
int ActuadorFreno_ValorLimitSwitchRetraido = 120;
int ActuadorFreno_ValorLimitSwitchExtendido = 986;

//int actFreno_valorRetraido = 130;
int ActuadorFreno_valorRetraido = 200;
int ActuadorFreno_valorExtendido = 900;

int ActuadorFreno_valorParoEmergencia = 900; // TODO: Buscar la extensión máxima que puede tener el actuador sin forzar el pedal.

///Acelerador.
// Extendido  28  -  965 Retraido.
//Diferencia 1009 - 28 = 937
#define ACELERADOR_MAPEO_MEDIO 650
#define ACELERADOR_MAPEO_COMPLETO 432 //A menor valor, mas extensión.

int ActuadorAcelerador_valorExtendido = ACELERADOR_MAPEO_MEDIO;
int ActuadorAcelerador_valorRetraido = 974; //Retraido. El acelerador esta inicialmente ligeramente
                            //extendido, para que quede en contacto con el acelerador.


///Valores de umbral para aplicar control.
int Actuadores_umbralError;
int ActuadorAcelerador_umbralError = 3; // Error aceptable en la posición de los actuadores de los pedales.
int ActuadorAcelerador_umbralErrorArranque = ActuadorAcelerador_umbralError * 5;
int ActuadorAcelerador_tiempoLlegada = 2000;

int ActuadorFreno_umbralError = 9;
int ActuadorFreno_umbralErrorArranque = ActuadorFreno_umbralError * 5;
int ActuadorFreno_tiempoLlegada = 1500;

///************************ Fin Variables configuración*******************************///


///*****************Variables del programa***********************
//*** Constantes de control PID de los actuadores lineales.
//int ActuadorFreno_Kp = 25;
//int ActuadorFreno_Kp = 17;
int ActuadorFreno_Kp = 18;
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


boolean ControlPedales_comportamientoDirecto = false;
// Comportamiento Inverso. Joystick al frente Frena.

enum TipoActuador{Freno, Acelerador, Volante};
//TipoActuador tipoActuador;
//***************************************************************



void moverActuador(TipoActuador tipoActuador, int ErrorPosicion);

void ControlarPedales(int Joystick_Y, uint8_t fijarPosicionFreno, boolean ControlPedales_comportamientoDirecto)
{
    /* fijarPosicionFreno:    True: Posición del freno fijado,  False: Freno controlado por Joystick.
       comportamientoDirecto: True: Joystick al frente acelera, False: Joystick al frente frena.*/
    if(ControlPedales_comportamientoDirecto)
    {
        int Joystick_Y_PosAbs = Joystick_Y - joyY_Center;
        if(Joystick_Y > (joyY_Center + umbral_lectura_joystick) )
        {   /// Se desea ACELERAR.
            /// Retraer el Freno y Controlar la posición del acelerador.
            // Retraer el freno
            if(!fijarPosicionFreno)
            {
                ActuadorFreno_PosDeseada = ActuadorFreno_valorRetraido; //Valor del actuador retraido.
            }
            // Controlar la posición del acelerador.

            ActuadorAcelerador_PosDeseada = map(abs(Joystick_Y_PosAbs),
                                                0,                      (joyY_MaxVal - joyY_Center),
                                                ActuadorAcelerador_valorRetraido,  ActuadorAcelerador_valorExtendido);

        }
        else if(Joystick_Y < (joyY_Center - umbral_lectura_joystick) )
        {   /// Se desea FRENAR.
            /// Retraer el acelerador y Controlar la posición del freno.

            // Retraer el acelerador.
            ActuadorAcelerador_PosDeseada = ActuadorAcelerador_valorRetraido;//Valor del actuador del acelerador retraido.

            if(!fijarPosicionFreno)
            {
                // Controlar la posición del freno.                            x            0                  512
                //int Joystick_Y_PosAbs = joyY_Center - Joystick_Y; //Cuando la posición del joystick decrece la posición deseada del actuador aumenta.
                ActuadorFreno_PosDeseada = map(abs(Joystick_Y_PosAbs),
                                                0,                          (joyY_Center - joyY_MinVal),
                                                ActuadorFreno_valorRetraido,     ActuadorFreno_valorExtendido);
            }
            else
            {
                // Si está activado el modo bloqueo no se recalcula la Posición Deseada, se mantiene la anterior.

            #if DEBUG_ACTUADORES_BLOQUEOFRENO
                Serial.print(", Pos. Freno fijada.");
            #endif
            }
        }
        else //El joystick está centrado. Retraer ambos actuadores.
        {
            if(!fijarPosicionFreno)
            {
                ActuadorFreno_PosDeseada = ActuadorFreno_valorRetraido; //Retraer completamente el freno.
            }
            ActuadorAcelerador_PosDeseada = ActuadorAcelerador_valorRetraido; //Retraer completamente el acelerador.
        }
    }
    else // Comportamiento INVERSO.
    {
        int Joystick_Y_PosAbs = Joystick_Y - joyY_Center;
        if(Joystick_Y > (joyY_Center + umbral_lectura_joystick) )
        {   /// Se desea FRENAR.
            // Retraer el acelerador.
            ActuadorAcelerador_PosDeseada = ActuadorAcelerador_valorRetraido; //Valor del actuador del acelerador retraido.

            if(!fijarPosicionFreno)
            {
                // Controlar la posición del freno.                            x            0                  512


                //int Joystick_Y_PosAbs = joyY_Center - Joystick_Y; //Cuando la posición del joystick decrece la posición deseada del actuador aumenta.
                ActuadorFreno_PosDeseada = map(abs(Joystick_Y_PosAbs),
                                                0,                          (joyY_MaxVal - joyY_Center),
                                                ActuadorFreno_valorRetraido,     ActuadorFreno_valorExtendido);
            }
            else
            {
                // Si está activado el modo bloqueo no se recalcula la Posición Deseada, se mantiene la anterior.
                #if DEBUG_ACTUADORES_BLOQUEOFRENO
                Serial.print(", Fijar Pos Frn");
                #endif
            }
        }
        else if(Joystick_Y < (joyY_Center - umbral_lectura_joystick) )
        {   /// Se desea ACELERAR.
            // Retraer el freno
            if(!fijarPosicionFreno)
            {
                ActuadorFreno_PosDeseada = ActuadorFreno_valorRetraido; //Valor del actuador retraido.
            }
            int Joystick_Y_PosAbs =  joyY_Center - Joystick_Y;
            ActuadorAcelerador_PosDeseada = map(abs(Joystick_Y_PosAbs),
                                                0,                      (joyY_Center - joyY_MinVal),
                                                ActuadorAcelerador_valorRetraido,  ActuadorAcelerador_valorExtendido);

        }
        else //El joystick está centrado. Retraer ambos actuadores.
        {
            if(!fijarPosicionFreno)
            {
                ActuadorFreno_PosDeseada = ActuadorFreno_valorRetraido; //Retraer completamente el freno.
            }
            ActuadorAcelerador_PosDeseada = ActuadorAcelerador_valorRetraido; //Retraer completamente el acelerador.
        }
    }

    //Calcular valores de control con retroalimentacion
#if FRENO_ACTIVADO
    ActuadorFreno_ErrorPosicion = ActuadorFreno_PosDeseada - ActuadorFreno_Posicion; //
    moverActuador(TipoActuador::Freno, ActuadorFreno_ErrorPosicion);
#endif

  //Controlar el acelerador.
#if ACELERADOR_ACTIVADO
    ActuadorAcelerador_ErrorPosicion = ActuadorAcelerador_PosDeseada - ActuadorAcelerador_Posicion;
    moverActuador(TipoActuador::Acelerador, ActuadorAcelerador_ErrorPosicion);
#endif
}


void moverActuador(TipoActuador tipoActuador, int ErrorPosicion)
{
    /* tipoActuador: Acelerador o Freno
     * ErrorPosicion: ActuadorFreno_PosDeseada - ActuadorFreno_PosicionActual;
     */

    bool ComportamientoDirecto; //Este comportamiento tiene que ver con la posición de los engranes del motor.
    int address;

    if(tipoActuador == TipoActuador::Freno)
    {
        ComportamientoDirecto = false; //Comportamiento inverso: Valores de control positivos retraen el actuador.
        Kp = ActuadorFreno_Kp;
        address = ActuadorFreno_Address;
        Actuadores_umbralError = ActuadorFreno_umbralError;

    } else if(tipoActuador == TipoActuador::Acelerador){
        ComportamientoDirecto = false;
        Kp = ActuadorAcelerador_Kp;
        address = ActuadorAcelerador_Address;
        Actuadores_umbralError = ActuadorAcelerador_umbralError;
    }

    int control;
    if(ComportamientoDirecto)
    {
        control = ErrorPosicion * Kp;
    } else {
        control = -(ErrorPosicion * Kp);
    }

    if(abs(ErrorPosicion) < Actuadores_umbralError)
    {
        control = 0;
    }

    if(tipoActuador == TipoActuador::Freno)
    {
        ActuadorFreno_Control = control;

    } else if(tipoActuador == TipoActuador::Acelerador)
    {
        ActuadorAcelerador_Control = control;
    }

    setMotorSpeed_Protocol(address, control);
}

void retraerAcelerador()
{
    int errorPosicion = ActuadorAcelerador_valorRetraido - ActuadorAcelerador_valorExtendido; // Se asume el mayor error, para que se retraiga lo antes posible.
    moverActuador(TipoActuador::Acelerador, errorPosicion);
}

void extenderFreno()
{
    int errorPosicionFreno = ActuadorFreno_valorExtendido - ActuadorFreno_valorRetraido; // Se asume el mayor error, para que se extienda lo antes posible.
    moverActuador(TipoActuador::Freno, errorPosicionFreno);
}


#endif

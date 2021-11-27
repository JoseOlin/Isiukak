#ifndef CONTROLACTUADORES
#define CONTROLACTUADORES
/* ***************************** /
act1: Freno.           0x0D
act2: Acelerador.      0x0A

act3: Volante.         0x04  (0000 0100)
*/ // ***************************

#include "LecturaFeedback.hpp"
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
int ActuadorFreno_valorRetraido = 255;
int ActuadorFreno_valorExtendido = 800;

int ActuadorFreno_valorParoEmergencia = 800; // TODO: Buscar la extensión máxima que puede tener el actuador sin forzar el pedal.

///Acelerador.
// Extendido  28  -  965 Retraido.
//Diferencia 1009 - 28 = 937
//#define ACELERADOR_MAPEO_MEDIO 650

#define ACELERADOR_MAPEO_MEDIO 724
#define ACELERADOR_MAPEO_COMPLETO 432 //A menor valor, mas extensión.

int ActuadorAcelerador_valorExtendido = ACELERADOR_MAPEO_MEDIO;
int ActuadorAcelerador_valorRetraido = 974; //Retraido. El acelerador esta inicialmente ligeramente
                            //extendido, para que quede en contacto con el acelerador.

/// Valores de umbral para aplicar control.
int Actuadores_umbralError;
int ActuadorAcelerador_umbralError_Ctrl = 3; // Error aceptable en la posición de los actuadores de los pedales.
int ActuadorAcelerador_tiempoLlegada = 2000;
// Umbral para evaluar si el actuador está en un rango válido
int ActuadorAcelerador_umbralError_Rango = 20;

int ActuadorFreno_umbralError_Ctrl = 9;
int ActuadorFreno_umbralErrorArranque = ActuadorFreno_umbralError_Ctrl * 5;
int ActuadorFreno_tiempoLlegada = 1500;

//int ActuadorFreno_umbralError_Rango = 20;
int ActuadorFreno_umbralError_Rango = 35;

///************************ Fin Variables configuración*******************************///


///*****************Variables del programa***********************
//*** Constantes de control PID de los actuadores lineales.
//int ActuadorFreno_Kp = 25;
//int ActuadorFreno_Kp = 17;

int ActuadorFreno_PosDeseada = 0;
int ActuadorFreno_ErrorPosicion;
int ActuadorFreno_ErrorPosicionInhibido;
int ActuadorFreno_Control; //Señal de control para actuador de freno.
uint8_t ActuadorFreno_EstaInhibido = true;
int ActuadorFreno_Kp = 18;
int ActuadorFreno_Ki = 1;


int ActuadorAcelerador_PosDeseada = 0;
int ActuadorAcelerador_ErrorPosicion;
int ActuadorAcelerador_ErrorPosicionInhibido;

int ActuadorAcelerador_Control;//Señal de control para actuador de acelerador.
uint8_t ActuadorAcelerador_EstaInhibido = true;
int ActuadorAcelerador_Kp = 30;


boolean Joystick_comportamientoDirecto = false;
// Comportamiento Directo. Joystick al frente acelera.
// Comportamiento Inverso. Joystick al frente Frena.

enum TipoActuador{Freno, Acelerador, Volante};
//TipoActuador tipoActuador;
//***************************************************************

/// Prototipos funciones.
void moverActuador(TipoActuador tipoActuador, int ErrorPosicion);



void ControlarPedales(int Joystick_Y,
                      uint8_t fijarPosicionFreno,
                      boolean Joystick_comportamientoDirecto,
                      uint8_t Freno_EstaInhibido,
                      uint8_t Acelerador_EstaInhibido)
{
/*! Joystick_Y (int):
 * fijarPosicionFreno:                 True: Posición del freno fijado,  False: Freno controlado por Joystick.
 * Joystick_comportamientoDirecto:     True: Joystick al frente acelera, False: Joystick al frente frena.
 * Freno_EstaInhibido:                 True: No se aplica control     False: Se aplica control.
 * Acelerador_EstaInhibido:            True: */


    if(Joystick_comportamientoDirecto) // Forward accel, Backwards brake.
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
    else // Comportamiento INVERSO. Forward brake, backwars accel.
    {
        int Joystick_Y_PosAbs = Joystick_Y - joyY_Center;

        if(Joystick_Y > (joyY_Center + umbral_lectura_joystick) )
        {   /// Se desea FRENAR.

            // Retraer el acelerador.
            ActuadorAcelerador_PosDeseada = ActuadorAcelerador_valorRetraido; //Valor del actuador del acelerador retraido.

            if(!fijarPosicionFreno)
            {
                // Controlar la posición del freno.                            x            0                  512
                ActuadorFreno_PosDeseada = map(abs(Joystick_Y_PosAbs),
                                                0,                              (joyY_MaxVal - joyY_Center),
                                                ActuadorFreno_valorRetraido,     ActuadorFreno_valorExtendido);
            }
            //else //Mantiene la posición anterior.


        }
        else if(Joystick_Y < (joyY_Center - umbral_lectura_joystick) )
        {   /// Se desea ACELERAR.

            int Joystick_Y_PosAbs =  joyY_Center - Joystick_Y;
            ActuadorAcelerador_PosDeseada = map(abs(Joystick_Y_PosAbs),
                                                0,                      (joyY_Center - joyY_MinVal),
                                                ActuadorAcelerador_valorRetraido,  ActuadorAcelerador_valorExtendido);

            // Retraer el freno
            if(!fijarPosicionFreno)
            {
                ActuadorFreno_PosDeseada = ActuadorFreno_valorRetraido; //Valor del actuador retraido.
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

    //Calcular valores de control con retroalimentacion
#if FRENO_ACTIVADO

    if(Freno_EstaInhibido)
    {
        ActuadorFreno_ErrorPosicion = ActuadorFreno_ErrorPosicionInhibido;
    }
    else
    {
        ActuadorFreno_ErrorPosicion = ActuadorFreno_PosDeseada - ActuadorFreno_Posicion;
    }

    moverActuador(TipoActuador::Freno, ActuadorFreno_ErrorPosicion);

#endif

  //Controlar el acelerador.
#if ACELERADOR_ACTIVADO
    if(Acelerador_EstaInhibido)
    {
        ActuadorAcelerador_ErrorPosicion = ActuadorAcelerador_ErrorPosicionInhibido;
    }
    else
    {
        ActuadorAcelerador_ErrorPosicion = ActuadorAcelerador_PosDeseada - ActuadorAcelerador_Posicion;
    }
    moverActuador(TipoActuador::Acelerador, ActuadorAcelerador_ErrorPosicion);
#endif

}


void moverActuador(TipoActuador tipoActuador, int ErrorPosicion)
{
    /* tipoActuador:    Acelerador o Freno
     * ErrorPosicion:   ActuadorFreno_PosDeseada - ActuadorFreno_PosicionActual;
     */

    // Comportamiento Directo: Valores de control positivos EXTIENDEN el actuador.
    // Comportamiento inverso: Valores de control positivos RETRAEN el actuador.

    int Kp;

    bool ComportamientoDirecto; //Este comportamiento tiene que ver con la posición de los engranes del motor.
    int address;

    if(tipoActuador == TipoActuador::Freno)
    {
        ComportamientoDirecto = false;
        Kp = ActuadorFreno_Kp;
        address = ActuadorFreno_Address;
        Actuadores_umbralError = ActuadorFreno_umbralError_Ctrl;

    }
    else if(tipoActuador == TipoActuador::Acelerador)
    {
        ComportamientoDirecto = false;
        Kp = ActuadorAcelerador_Kp;
        address = ActuadorAcelerador_Address;
        Actuadores_umbralError = ActuadorAcelerador_umbralError_Ctrl;
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


void Acelerador_Retraer()
{
    int errorPosicion = ActuadorAcelerador_valorRetraido - ActuadorAcelerador_valorExtendido; // Se asume el mayor error, para que se retraiga lo antes posible.
    ActuadorAcelerador_ErrorPosicionInhibido = errorPosicion;
    //moverActuador(TipoActuador::Acelerador, errorPosicion);
}
void Acelerador_Inhibir(uint8_t &acelerador_estaInhibido)
{
    acelerador_estaInhibido = true; // No aplicar control por feeback, sino openloop
}
void Acelerador_Desinhibir(uint8_t &acelerador_estaInhibido)
{
    acelerador_estaInhibido = false;
}


void Freno_Extender()
{
    int errorPosicionFreno = ActuadorFreno_valorExtendido - ActuadorFreno_valorRetraido; // Se asume el mayor error, para que se extienda lo antes posible.
    //Serial.print("errorPosicion: ");
    //Serial.println(errorPosicionFreno);
    ActuadorFreno_ErrorPosicionInhibido = errorPosicionFreno;

    //moverActuador(TipoActuador::Freno, errorPosicionFreno);
}

void Freno_Inhibir(uint8_t &freno_estaInhibido)
{
    freno_estaInhibido = true; // No aplicar control por feeback , sino openloop
}
void Freno_Desinhibir(uint8_t &freno_estaInhibido)
{
    freno_estaInhibido = false; // No aplicar control por feeback , sino openloop
}

void aplicarModoCarretera(uint8_t modoCarreteraActivado)
{
    if(modoCarreteraActivado)
    {
        ActuadorAcelerador_valorExtendido = ACELERADOR_MAPEO_COMPLETO;
    }
    else
    {
        ActuadorAcelerador_valorExtendido = ACELERADOR_MAPEO_MEDIO;
    }
}



void desplegarInfoPedales()
{
#if INFO_ACTUADORES_POS
    // Brake information
    Serial.print(",\tB_p: "); Serial.print(ActuadorFreno_Posicion);
    Serial.print(",   B_t: ");     Serial.print(ActuadorFreno_PosDeseada); //Serial.print(")");

    #if INFO_ACTUADORES_CONTROL
        Serial.print(",   B_e: "); Serial.print(ActuadorFreno_ErrorPosicion); //posDeseada - posActual
        Serial.print(",   B_c: "); Serial.print(ActuadorFreno_Control);
    #endif

    // Gas information
    Serial.print(",\tA_p: "); Serial.print(ActuadorAcelerador_Posicion); //Valor del pot del act2 (Acelerador)
    Serial.print(",   A_t: "); Serial.print(ActuadorAcelerador_PosDeseada); //Serial.print(")");

    #if INFO_ACTUADORES_CONTROL
        Serial.print(",   A_e: "); Serial.print(ActuadorAcelerador_ErrorPosicion);
        Serial.print(",   A_c: "); Serial.print(ActuadorAcelerador_Control); //Valor de control aplicado al actuador de acelerador.
    #endif

#endif
}



#endif

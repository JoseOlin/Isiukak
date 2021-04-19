#ifndef EXTENSOR
#define EXTENSOR

#include <Wire.h>
#include "PCF8574.hpp"
#include "ControlPedales.hpp"

PCF8574 PCF(0x20);

uint8_t entrada2Temp;

void LeerEscribirExtensorPCF(uint8_t* entrada1, uint8_t* entrada2,  uint8_t* entrada3,  uint8_t* entrada4,
                             uint8_t salida1,   uint8_t salida2,    uint8_t salida3)
{
/*
 *
 *
 */
    *entrada1 = PCF.read(0); //Push button mapeo completo Volante.
    *entrada2 = PCF.read(1); //Switch mapeo completo Acelerador.
    *entrada3 = PCF.read(2); //
    *entrada4 = PCF.read(3); //


    entrada2Temp = *entrada1;

    //Serial.print("ent2Temp: "); Serial.print(entrada2Temp);

    PCF.write(4, salida1); //Último LED del Joystick (izquierda a derecha) (JoystickDesconectado)
    PCF.write(5, salida2); //Encoder Desconectado.
    PCF.write(6, salida3); //Actuadores Desconectados.
    PCF.write(7, !entrada2Temp); //Primer LED del Joystick.

    //digitalWrite(pinLedMapeoCompVol, entrada2Temp);

    if(*entrada2 == 1)
    {
        actAcel_valorExtendido = ACELERADOR_MAPEO_COMPLETO;
    }
    else
    {
        actAcel_valorExtendido = ACELERADOR_MAPEO_MEDIO;
    }
}



#endif

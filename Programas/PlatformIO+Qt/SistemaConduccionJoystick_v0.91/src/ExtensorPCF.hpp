#ifndef EXTENSOR_PCF
#define EXTENSOR_PCF

//#include <Wire.h>
//#include <WireNoFreeze.h>

#include "PCF8574.hpp"
#include "ControlPedales.hpp"
#include "Seguridad.hpp"


PCF8574 PCF(0x20); //Los pines A0, A1 y A2 definen la dirección. 0x20 es LOW, LOW, LOW (Conectar a GND los 3).

/// Prototipos de las funciones ///
void ExtensorPCF_Leer(uint8_t* entrada1, uint8_t* entrada2,  uint8_t* entrada3,  uint8_t* entrada4);
void ExtensorPCF_Escribir(uint8_t salida1,  uint8_t salida2, uint8_t salida3, uint8_t salida4);
////////////////////////////////////////


void ExtensorPCF_Leer(uint8_t* entrada1, uint8_t* entrada2,  uint8_t* entrada3,  uint8_t* entrada4)
{
    *entrada1 = PCF.read(0);

#if DEBUG_WIRE
    Serial.println("Pasó el PCF.read");
    //*entrada1 = PCF.receive(0); //Push button mapeo completo Volante.
#endif
    *entrada2 = PCF.read(1);
    *entrada3 = PCF.read(2);
    *entrada4 = PCF.read(3);
}

void ExtensorPCF_Escribir(uint8_t salida1,  uint8_t salida2, uint8_t salida3, uint8_t salida4)
{
    PCF.write(4, salida1); //Último LED del Joystick (izquierda a derecha) (JoystickDesconectado)
    PCF.write(5, salida2); //Encoder Desconectado.
    PCF.write(6, salida3); //Actuadores Desconectados.
    PCF.write(7, salida4); //Primer LED del Joystick.
}



void pullupsInternos_i2c(boolean habilitar)
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

#endif

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
    PCF.write(4, salida1); //
    PCF.write(5, salida2); //
    PCF.write(6, salida3); //
    PCF.write(7, salida4); //
}





#endif

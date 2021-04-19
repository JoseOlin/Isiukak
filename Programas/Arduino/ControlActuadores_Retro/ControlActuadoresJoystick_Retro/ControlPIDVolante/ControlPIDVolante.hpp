//*********Variables y librerias para comunicacion con encoder y control de direccion
#include <SPI.h>
#include <EEPROM.h> //Para almacenar valores en memoria no volatil.


//#define CS 3 //Chip or Slave select Jamiec
#define CS 10 //Chip or Slave select Nuestro


uint16_t ABSposition = 0;
uint16_t ABSposition_last = 0;
float AbsPosDeg;
float AbsPosLastDeg;


int numPulsos = 4096; //2  a la 12.
float factor =(float)360/numPulsos; //0.087890625; //360/4096


unsigned int Pos=0;
float PosDeg = 0.00; //Posicion en grados 
float errorPosDireccion = 0;
float umbralErrorPosDireccion = 4;
//signed char vueltas=-1;
int8_t vueltas = 0;
boolean boot = true;
int gradosVolanteIzquierda = -610;
int gradosVolanteDerecha = 610;


boolean encendido = true;
unsigned int pin_encendido = 9;
boolean vueltasGuardadas = false; //Para saber si en esta sesion el numero de vueltas ya fue almacenado y no volver a guardar.
//**************************************************************************************

enum tiposConduccion {MODO_VELOCIDAD, MODO_POSICION};

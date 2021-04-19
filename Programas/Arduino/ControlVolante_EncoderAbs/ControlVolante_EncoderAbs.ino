/*
Lectura de Encoder AMT 203 (Absoluto) por SPI.
 
 Conector:
 13 11  9  7  5  3  1
 14 12 10  8  6  4  2
 
 Configuración cable:
 				Largo - Corto
 1  N/A
 2  CSB			Blanco - Café.   (Chip Select)
 3  MISO			Café claro - Crema (blanco)
 4  GND			Blanco - Rosa
 5  SCK			Café - Blanco
 6  5 V+			Rosa - Blanco
 7  MOSI 		Blanco - Naranja
 8  B			Blanco - Amarillo
 9  N/A
 10 A			Blanco - Verde
 11 N/A
 12 X			Blanco - Azul
 13 N/A
 14 T_Bit		Naranja - Blanco
 
 Micro: Arduino UNO
 
 17 Diciembre 2013
 
 CSB     10 (SS en Arduino, CSB -Chip Select Bar- en encoder, activo en LOW)
 MOSI    11
 MISO    12
 SCK     13
 
 Codigo de Jamiec (Foro Arduino).
 */

#include <SPI.h>
#include <EEPROM.h> //Para almacenar valores en memoria no volatil.

//#define CS 3 //Chip or Slave select Jamiec
#define CS 10 //Chip or Slave select Nuestro

uint16_t ABSposition = 0;
uint16_t ABSposition_last = 0;


int numPulsos = 4096; //2 a la 12.
float factor =(float)360/numPulsos; //0.087890625; //360/4096

unsigned int Pos=0;
float deg = 0.00;
//signed char vueltas=-1;
int8_t vueltas = 0;
boolean boot = true;
boolean encendido = false;
unsigned int pin_encendido = 9;
boolean vueltasGuardadas = false; //Para saber si en esta sesion el numero de vueltas ya fue almacenado y no volver a guardar.


void setup()
{
  pinMode(CS,OUTPUT);//Slave Select
  digitalWrite(CS,HIGH);
  
  pinMode(pin_encendido, INPUT); //

  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV32);

  Serial.begin(19200);
  Serial.println("starting");
  Serial.print("factor:");
  Serial.println(factor);
  //Serial.print("Vueltas: ");
  //Serial.println(vueltas);
  Serial.flush();

  delay(2000);
  SPI.end();


  //Al encender el sistema la diferencia entre position y position_last puede ser grande (puesto que no hay last). Validar que no considere eso
     //como una vuelta, sino que cargue el valor de la EEPROM.
    
      //Cargar valor de cantidad de vueltas.
      vueltas = EEPROM.read(0); //Leer el byte de la direccion 0 en la EEPROM
      //Serial.print("vueltas: ");
      //Serial.println(vueltas);      
      boot = false;
}


void loop()
{ 
  ABSposition = LeerEncoder();

  if(ABSposition != ABSposition_last)    //if nothing has changed dont wast time sending position
  {
    int diferencia = ABSposition_last - ABSposition;
    
    //Si hay un salto abrupto en la posicion; ejemplo de 360 a 0° (maximo de 350 a 10°).
    if(  (diferencia >  3868)  && !boot)//340°
    {  vueltas++;  }
    if(  diferencia < -3868  && !boot )
    {  vueltas--;  }

    ABSposition_last = ABSposition;    //set last position to current position
    deg = (float)ABSposition;
    deg = deg * factor + vueltas*360;    //
    Pos = ABSposition;
    //Serial.print("Dif:");
    //Serial.print(diferencia);
    Serial.print("V:");
    Serial.print(vueltas);
    Serial.print(", P:"); 
    Serial.print(Pos);     //Position in pulses.
    Serial.print(", D:"); 
    Serial.println(deg);   //Position in degrees.
  }   
  
  encendido = digitalRead(pin_encendido);
 
  //if(encendido && vueltasGuardadas)
  
  if(!encendido && !vueltasGuardadas)
  {
    Serial.println("Apagando");
    
    //Validar que el pin se mantenga bajo por al menos 2 segundos.
    long startTime = millis();
    boolean guardarVueltas = true;
    while( (millis() - startTime) < 5000 )
    {
      
      if(digitalRead(pin_encendido) == HIGH )
      {
        guardarVueltas = false;
        break;
      }  
    }
    if(guardarVueltas) //Si pasaron 2 segundos y pin_encendido sigue bajo. Almacenar "vueltas".
    {
      Serial.print("Saving vueltas: "); Serial.println(vueltas);
    
      //Almacenar variable para vueltas.
      EEPROM.write(0, vueltas); //Addr=0, value=vueltas.
      vueltasGuardadas = true; 
    }
    else
    {
      Serial.println("Posible falso.");
        
    }
  } 
  delay(5);    //wait a bit till next check.


}


#include <Wire.h>
#include "PCF8574.h"
//const int pcfAddress = 0x20;
PCF8574 PCF(0x20);

 uint8_t valor1;
 uint8_t valor2;
 uint8_t valor3;
 uint8_t valor4;

 uint8_t *v2;

 int pin2 = 2;
 int pin3 = 3;
unsigned long inicio, fin, transcurrido;
void setup()
{
   Wire.begin();
   Serial.begin(9600);

   pinMode(pin3, OUTPUT);
   digitalWrite(pin3, HIGH);
   v2 = &valor2;
}


void EscribirSalidas (uint8_t  *val1, uint8_t *val2,  uint8_t *val3,        uint8_t *val4) {

  *val1=PCF.read(0);
  *val2 = PCF.read(1);
  *val3=PCF.read(2);
  *val4=PCF.read(3);
    Serial.print("v2:");
    Serial.print(valor2);
    Serial.print(", v1:");
    Serial.println(valor1);


    PCF.write(4, !*val1);
    PCF.write(5, !*val2);
    PCF.write(6, *val3);
    PCF.write(7, *val4);


}



void loop()
{
  inicio=millis();
  EscribirSalidas (&valor1, &valor2, &valor3, &valor4);
  fin=millis();
  transcurrido=fin-inicio;
   //Serial.print("t:");
   //Serial.println(transcurrido);
   //EscribirSalidas(valor1,valor2,valor3,valor4);
}

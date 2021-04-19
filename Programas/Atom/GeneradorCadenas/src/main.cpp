#include <Arduino.h>



///*** VARIABLES DE PROGRAMA ***********///
boolean vueltaDerecha = true;
long tiempoAnterior = 0, tiempoActual = 0;
int8_t vueltas = 0;
unsigned int contadorIteraciones = 0;

float posMotorDeg = 0.00; //Posicion del motor en grados
float posVolanteActual = 0.0;

//Cálculo de la relación entre las vueltas del volante y las vueltas del motor.
int dientesEje = 13;   //El sprocket del volante tiene 13 dientes.
int dientesMotor = 10; //El sprocket del motor tiene 10 dientes.
float relacionSprockets = (float)dientesEje / dientesMotor;

//Rango de giro del volante a izquierda y derecha.
//El máximo aproximado es 1 y 3/4 de vuelta (360 + 270 = 630), pero se redujo ligeramente para evitar
//llevarla al límite.
int gradosVolanteIzq = -610;
int gradosVolanteDer = 610;

//Para una vuelta de 90° el giro del volante es de menos de 3/4 de vuelta (algo más de media vuelta),
//así que la mayor parte del rango del joystick puede mapearse a este rango de giro del volante.
int gradosVolanteIzqVueltaAngRecto = -210;
int gradosVolanteDerVueltaAngRecto = 210;
//////////////////////////////////////////




///*** FUNCIONES ***///
void desplegarCadenas()
{
    char posMotorBuf[7];
    Serial.print("vls:");
    Serial.print(vueltas);
    //Serial.print(", P:");
    //Serial.print(PosMotorPulsos);     //Position in pulses.
    Serial.print(", M:");   //
    Serial.print(posMotorDeg);
    //sprintf(posMotorBuf, "%07.2f", posMotorDeg);
    //Serial.print(posMotorBuf);   //Posición del motor (no del volante) en grados.
    Serial.print(", V:");
    Serial.println(posVolanteActual);
}


void setup() {
  Serial.begin(115200);
  Serial.println("Init");



}

void loop()
{
    tiempoActual = millis();

    if( (tiempoActual - tiempoAnterior) >= 30 )
    {
      desplegarCadenas();
      tiempoAnterior = millis();

      contadorIteraciones++;
      if(contadorIteraciones > 10)
      {
        if(vueltaDerecha)
          posMotorDeg += 1;
        else
          posMotorDeg -= 1;

        posVolanteActual = posMotorDeg / relacionSprockets;
        if(posVolanteActual >= gradosVolanteDer)
          vueltaDerecha = false;
        if(posVolanteActual <= gradosVolanteIzq)
          vueltaDerecha = true;

        vueltas = (int)posVolanteActual / 360;
      }

      //Serial.print()
    }
}

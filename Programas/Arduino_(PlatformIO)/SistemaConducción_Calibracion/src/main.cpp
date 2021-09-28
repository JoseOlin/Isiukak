/*
Programa para encontrar el intervalo adecuado para los actuadores.
En el modo calibración los actuadores se controlan sin retroalimentación.
El eje vertical controla el acelerador; el horizontal el freno.

act1: Freno.
act2: Acelerador.
*/

#include <Arduino.h>
#include "DigitalFilter.hpp"
#include "LecturaFeedback.hpp"
#include "DriversMotores.hpp"



//*****Variables*****//


int umbral = 20; //Valor para evitar mover los actuadores con valores muy pequeños en el potenciometro

//512 − 384 = 128
//3200/128 = 25
int Kp = 25;

int velocidad;

//********************Variables de programa***********************************//
int pinRefPotsBajo = 2;
int pinRefPotsAlto = 3;

int posJoystickY_Abs = 0;
int posJoystickX_Abs = 0;

bool ComportamientoDirecto = true; //Si valores positivos extienden el actuador y negativos lo retraen.

#define FRENO_ACTIVO 1
#define ACELERADOR_ACTIVO 0

void setup()
{
    Serial.begin(115200);
    //Serial.begin(38400);
    Serial.println("Comunicacion Serial Iniciada.");
    Serial.print("Programa para la calibración de actuadores cargado.");
    //smcSerial.begin(19200);
    smcSerial.begin(9600); //Se probo con 19200 y funciona. Investigar si menor velocidad es menos exigente para el micro.
    //address = frenAddress;

    //exitSafeStart_Protocol(address);
    pinMode(pinRefPotsAlto, OUTPUT);
    pinMode(pinRefPotsBajo, OUTPUT);

    //Poner los pines en la configuración normal (estos pines alimentan los pots
    //y es necesario que no sean fijos, para poder ver si alguno se desconectó).
    digitalWrite(pinRefPotsBajo, LOW);
    digitalWrite(pinRefPotsAlto, HIGH);

    for(int ii = 0; ii < filterSamples; ii++)
    {
      Leer_Feedback();
    }
}

void loop()
{
    Leer_Feedback();


    posJoystickX_Abs = Joystick_X - joyX_Center; // Valor centrado en el origen.
    Serial.print("j_X: "); Serial.print(posJoystickX_Abs);
    posJoystickY_Abs = Joystick_Y - joyY_Center;
    Serial.print("\t j_Y: "); Serial.print(posJoystickY_Abs);


    Serial.print("\t Freno_Pos: "); Serial.print(ActuadorFreno_Posicion);

#if ACELERADOR_ACTIVO
    Serial.print(",\t Acel_Pos: "); Serial.print(ActuadorAcelerador_Posicion);
#endif
    // Movimiento del acelerador
    if(   (Joystick_Y > (joyY_Center + umbral) ) //Mover el actuador hacia enfrente
       || (Joystick_Y < (joyY_Center - umbral) ) )
    {
        #if ACELERADOR_ACTIVO
        velocidad = posJoystickY_Abs * Kp;  // Valor centrado en el origen.
        Serial.print(", acel ");  Serial.print("Ctrl: "); Serial.print(velocidad);
        //setMotorSpeed_Protocol(acelAddress, velocidad);
        ComportamientoDirecto = true;
        moverActuador(Actuadores::Acelerador, velocidad, ComportamientoDirecto );
        #endif
    }

    // Movimiento del freno.
    if(   (Joystick_X > (joyX_Center + umbral) ) //Mover el actuador hacia enfrente
       || (Joystick_X < (joyX_Center - umbral)) )
    {
        velocidad = posJoystickX_Abs * Kp;
        Serial.print(",  fren  "); Serial.print("Ctrl: "); Serial.print(velocidad);
        //setMotorSpeed_Protocol(frenAddress, velocidad);
        ComportamientoDirecto = true;
        moverActuador(Actuadores::Freno, velocidad, ComportamientoDirecto);
    }

    else //No movimiento
    {
#if ACELERADOR_ACTIVO
        setMotorSpeed_Protocol(acelAddress, 0);
#endif
        setMotorSpeed_Protocol(frenAddress, 0);
    }
    Serial.println("");
    delay(10);
}

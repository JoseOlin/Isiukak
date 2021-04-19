#ifndef SEGURIDAD
#define SEGURIDAD

#include <Arduino.h>
#include "Debug.hpp"
#include "ControlPedales.hpp"
#include "ControlVolante.hpp"
#include "ExtensorPCF.hpp"


//********************* Variables configuración ********************************
#define PUESTACERO 0
//Constantes para definición de los actuadores a utilizar
#define FRENO_ACTIVADO 1
#define ACELERADOR_ACTIVADO 1 //Para definir si se usará el acuador de acelerador
//o se enviará la señal directamente a la ECM
#define VOLANTE_ACTIVADO 0


unsigned int miliSegundosActuadorFrenoParoManual = 1500; // Tiempo de actuación del freno para el paro de emergencia.

int cantidadPots = 4;//****************DEFINE LA CANTIDAD DE POTENCIÓMETROS A VERIFICAR
///PARA EFECTOS DE PRUEBAS SE PUEDE PONER EN 2 (PRUEBAS SIN PEDALES), PERO EN OPERACIÓN
///DEBE REVISAR TODOS LOS POTS SIEMPRE (4).

unsigned int umbralPotSuperior = 822;
unsigned int umbralPotInferior = 227;
//********************** Variables configuración *******************************


//********************Variables de programa***********************************//
int pinRefPotsAlto = 3;
int pinRefPotsBajo = 2;

int potenciometros[4] = {A0, A1, A2, A3};
//int pinesJoystick[2] = {A0, A1};
//int pinesActuadores[2] = {A2, A3};

uint8_t joystickPotVertical = true;
uint8_t joystickPotHorizontal = true;
uint8_t JoystickConectado = true;
uint8_t JoystickDesconectado = true; //Usada para mantener el LED activado al-
//gunos segundos.
uint8_t contadorLEDJoystickDesconectado = 0;

uint8_t frenoConectado = true;
uint8_t aceleradorConectado = true;
uint8_t ActuadoresConectados = true;
uint8_t ActuadoresDesconectados = true;

uint8_t contadorLEDActuadoresDesconectados = 0;

uint8_t EncoderDesconectado = false;

uint8_t potenciometrosConectados = true;
boolean NoParoManualEmergencia = true;

boolean mensajesEmergenciaDesplegados = false;
boolean protocoloFrenadoImplementado = false;
//********************Variables de programa***********************************//


boolean VerificarConexionPotenciometros(unsigned int cantPots)
{
    /* Los potenciómetros son la retroalimentacion de los actuadores y los dos ejes
    del Joystick.
    */
    unsigned int valorPot;
    boolean potsAltos = false;
    boolean potsBajos = false;
    boolean potsConectados = true;

    joystickPotVertical = true;
    joystickPotHorizontal = true;

    JoystickConectado = true;
    ActuadoresConectados = true;
    //El encoder no se valida en esta función, se hace de manera automática en cada lectura.


    digitalWrite(pinRefPotsBajo, HIGH);
    digitalWrite(pinRefPotsAlto, HIGH);
    delay(1);

    //Validar que al poner los dos extremos del potenciómetro en alto
    //el wiper mida 1021 a 1023
    for(unsigned int ii=0; ii<cantPots; ii++)
    {
        valorPot = analogRead(potenciometros[ii]);
        //delay(1);
        if(valorPot < umbralPotSuperior)
        {
        //potsConectados = false;
        #if !DEBUG_POTS
            if(!mensajesEmergenciaDesplegados)
        #endif
            {
                Serial.print(",  Pot");
                Serial.print(ii);
                Serial.print(":");
                Serial.print(valorPot);
                Serial.println("*** Desconectado.***");
            }
            if(ii == 0)
            {
                joystickPotVertical = false;
                JoystickDesconectado = true;
                contadorLEDJoystickDesconectado = 6;
            }
            if(ii == 1)
            {
                joystickPotHorizontal = false;
                JoystickDesconectado = true;
                contadorLEDJoystickDesconectado = 6;
            }
            JoystickConectado = joystickPotHorizontal && joystickPotVertical;

            if(ii == 2)
            {
                frenoConectado = false;
                ActuadoresDesconectados = true;
                contadorLEDActuadoresDesconectados = 6;
            }
        #if ACELERADOR_ACTIVADO
            if(ii == 3)
            {
                aceleradorConectado = false;
                ActuadoresDesconectados = true;
                contadorLEDActuadoresDesconectados = 6;
            }
        #endif
        }
    #if ACELERADOR_ACTIVADO
        ActuadoresConectados = frenoConectado && aceleradorConectado;
    #else
        ActuadoresConectados = frenoConectado;
    #endif
    }

    potsAltos = ActuadoresConectados && JoystickConectado;

#if DEBUG_POTS
  if(potsAltos)
  {
        Serial.println(". Todos Altos.");
  }else{
      Serial.print("Pots_H: "); Serial.print(potsAltos);
      //Serial.print(", Pots Bajos: "); Serial.print(potsBajos);
      Serial.print(", Joystick_H: "); Serial.print(JoystickConectado);
      Serial.print(", Actuadores_H: "); Serial.print(ActuadoresConectados);
      //Serial.println("");
  }
#endif

  //Validar que al poner ambos extremos de los potenciómetros a cero
  //todos los wipers marquen 0 ó 1.
  digitalWrite(pinRefPotsBajo, LOW);
  digitalWrite(pinRefPotsAlto, LOW);
  delay(1);
  for(unsigned int ii=0; ii<cantPots; ii++)
  {
    valorPot = analogRead(potenciometros[ii]);
    //delay(1);
    if(valorPot > umbralPotInferior)
    {

      //potsConectados = false;
  #if DEBUG_POTS
      if(!mensajesEmergenciaDesplegados)
      {
        Serial.print(",  Pot"); Serial.print(ii);
        Serial.print(":"); Serial.print(valorPot);
        Serial.print(" ***Desconectado.***");
      }
  #endif
      if(ii == 0)
      {
          joystickPotVertical = false;
          JoystickDesconectado = true;
          contadorLEDJoystickDesconectado = 6;
      }
      if(ii == 1)
      {
          joystickPotHorizontal = false;
          JoystickDesconectado = true;
          contadorLEDJoystickDesconectado = 6;
      }
      JoystickConectado = joystickPotHorizontal && joystickPotVertical;


      if(ii == 2)
      {
          frenoConectado = false;
          ActuadoresDesconectados = true;
          contadorLEDJoystickDesconectado = 6;
      }

  #if ACELERADOR_ACTIVADO
      if(ii == 3)
      {
          aceleradorConectado = false;
          ActuadoresDesconectados = true;
          contadorLEDJoystickDesconectado = 6;
      }
  #endif
    }
  }

  #if ACELERADOR_ACTIVADO
    ActuadoresConectados = frenoConectado && aceleradorConectado;
  #else
    ActuadoresConectados = frenoConectado;
  #endif
    potsBajos =  JoystickConectado && ActuadoresConectados;
    potsConectados = potsAltos && potsBajos;

#if DEBUG_POTS
    if(potsConectados)
    {
        Serial.println(". Todos Bajos.");
    }else{
        Serial.print(", Pots_L: "); Serial.print(potsBajos);
        Serial.print(", Joystick_L: "); Serial.print(JoystickConectado);
        Serial.print(", Actuadores_L: "); Serial.println(ActuadoresConectados);
        //Serial.println("");
    }
#endif

  //Regresar los pines a la configuración normal.
  digitalWrite(pinRefPotsBajo, LOW);
  digitalWrite(pinRefPotsAlto, HIGH);

  return potsConectados;
}

void ParoManualEmergencia()
{
    //El paro manual de emergencia se activa si se presiona el botón correspondiente.
    //Contraer el acelerador.
    //El acelerador se contrae con valores de control negativos.
    Serial.println("Paro Emerg Manual.");
    setMotorSpeed_Protocol(acelAddress, -3200);

    if(ActuadoresConectados)
    {
        //Si los actuadores están conectados seguir utilizando la retroalimentación
        //para frenar el carro.
        //***TO-DO***: Buscar el valor del pot en extensión máxima.
        int frenoPosDeseadaParo = actFreno_valorParoEmergencia;

        error_freno = smoothAct1 - frenoPosDeseadaParo;
        controlFreno = error_freno*Kp;
        setMotorSpeed_Protocol(frenAddress, controlFreno);
    }
    else
    {
        //Si los actuadores están desconectados frenar el carro en lazo abierto (por tiempo)
        //*Los actuadores se extienden con valores positivos de control
        if(!protocoloFrenadoImplementado)
        {
            setMotorSpeed_Protocol(frenAddress, 3200);
            delay(miliSegundosActuadorFrenoParoManual);
            setMotorSpeed_Protocol(frenAddress, 0);
            protocoloFrenadoImplementado = true;
        }
    }
}

void ParoDeEmergencia(  /*unsigned int pinLedMapeoCompVol*/  )
{
    if(!mensajesEmergenciaDesplegados)
    {
        Serial.print("Paro Emerg:");
        if(JoystickDesconectado)
            Serial.print("Jys,");
        if(ActuadoresDesconectados)
            Serial.print("Acts");

    #if VOLANTE_ACTIVADO
        if(EncoderConectado)
            Serial.print(", Enc:");
    #endif

        Serial.println("."); //Fin de linea de error.


        mensajesEmergenciaDesplegados = true;
    }

    //Contraer totalmente el acelerador.
    //El acelerador se contrae con valores de control negativos.
    setMotorSpeed_Protocol(acelAddress, -3200);

    //Poner el freno en lo máximo permitido (por el coche, no por el actuador.)
    if(ActuadoresConectados)
    {
        //Si los actuadores están conectados seguir utilizando la retroalimentación
        //para frenar el carro.
        //***TO-DO***: Buscar el valor del pot en extensión máxima.
        int frenoPosDeseada = actFreno_valorParoEmergencia;

        error_freno = smoothAct1 - frenoPosDeseada;
        controlFreno = error_freno*Kp;
        setMotorSpeed_Protocol(frenAddress, controlFreno);
    }
    else
    {
        //Si la retroalimentacion de los actuadores está desconectada frenar
        //el carro en lazo abierto (por tiempo)
        //*Los actuadores se extienden con valores positivos de control
        // Activar el actuador de freno durante 1.5 segundos.

        setMotorSpeed_Protocol(frenAddress, 3200);
        delay(miliSegundosActuadorFrenoParoManual);
        setMotorSpeed_Protocol(frenAddress, 0);
    }

#if VOLANTE_ACTIVADO
    //Centrar el volante.
    //***TO-DO***: Definir si es mejor centrarlo o mantenerlo en el último estado y frenar
    if(EncoderConectado)
    {
        float posicion_volante_deseada = 0; //En grados.

        //float posicion_volante_actual = PosMotorDeg / relacionSprockets;

        float posMotor_deseada = posicion_volante_deseada * relacionSprockets;
        ControlPosicionVolante(posMotor_deseada, PosMotorDeg_actual, &errorPosDireccion, controlVolanteMaximo);
    }
    else
    {
        //
        setMotorSpeed_Protocol(volnAddress, 0); //Dejar de aplicar control al volante y frenar.
    }
#endif

    //////**Seguir leyendo el encoder y el joystick hasta que sean reconectados.//
    potenciometrosConectados = VerificarConexionPotenciometros(cantidadPots);

#if VOLANTE_ACTIVADO
    LeerConvertirEncoder(&EncoderDesconectado); //Aquí mismo se valida si el encoder está conectado.
    if(potenciometrosConectados && EncoderConectado)
#else
    if(potenciometrosConectados)
#endif
    {
        mensajesEmergenciaDesplegados = false;
    }

    LeerEscribirExtensorPCF(&mapeoCompletoAcelerador, &mapeoCompletoVolante, &entradaPCF3, &entradaPCF4,
                          JoystickDesconectado, EncoderDesconectado, ActuadoresDesconectados);
    //////////////////////////////////////////////////////////////////////////////
}

#endif

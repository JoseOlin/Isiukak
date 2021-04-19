#ifndef SEGURIDAD
#define SEGURIDAD

#include <Arduino.h>
#include "Debug.hpp"
#include "ControlPedales.hpp"
#include "ControlVolante.hpp"
#include "ExtensorPCF.hpp"


//********************* Variables configuración ********************************
#define PUESTACERO 0

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

uint8_t JoystickConectado = true;
uint8_t ActuadoresConectados = true;
uint8_t potenciometrosConectados = true;
boolean NoParoManualEmergencia = true;

boolean mensajesEmergenciaDesplegados = false;
boolean protocoloFrenadoImplementado = false;
//********************Variables de programa***********************************//


boolean VerificarConexionPotenciometros(unsigned int cantPots)
{/* Los potenciómetros son la retroalimentacion de los actuadores y los dos ejes
    del Joystick.

    */
  unsigned int valorPot;
  boolean potsConectados = true;
  JoystickConectado = true;
  ActuadoresConectados = true;
  //El encoder no se valida en esta función, se hace de manera automática en cada lectura.

  //Validar que al poner los dos extremos del potenciómetro en alto
  //el wiper mida 1021 a 1023
  digitalWrite(pinRefPotsBajo, HIGH);
  digitalWrite(pinRefPotsAlto, HIGH);
  delay(1);
  for(unsigned int ii=0; ii<cantPots; ii++)
  {
    valorPot = analogRead(potenciometros[ii]);
    //delay(1);
    if(valorPot < umbralPotSuperior)
    {
      potsConectados = false;
      if(!mensajesEmergenciaDesplegados)
      {
        Serial.print(",  Pot");
        Serial.print(ii);
        Serial.print(":");
        Serial.print(valorPot);
        Serial.println("*** Desconectado.***");
      }
      if(ii==0 || ii==1)
        JoystickConectado = false;
      else if(ii==2 || ii==3)
        ActuadoresConectados = false;
    }
  }

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
      potsConectados = false;
      if(!mensajesEmergenciaDesplegados)
      {
        Serial.print(",  Pot"); Serial.print(ii);
        Serial.print(":"); Serial.print(valorPot);
        Serial.print(" ***Desconectado.***");
      }
      if(ii==0 || ii==1)
        JoystickConectado = false;
      else if(ii==2 || ii==3)
        ActuadoresConectados = false;
    }
  }

  if(potsConectados)
  {
    #if DEBUG_SEGURIDAD
    Serial.println(". Todos conectados.");
    #endif
  }
  else
  {
    //Serial.println("");
  }

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

void ParoDeEmergencia(/*unsigned int pinLedMapeoCompVol*/)
{
  if(!mensajesEmergenciaDesplegados)
  {
    Serial.print("Paro Emerg:");
    if(!JoystickConectado)
        Serial.print("Jys,");
    if(!ActuadoresConectados)
        Serial.print("Acts");
    if(!EncoderConectado)
        Serial.print(", Enc:");
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


  //////**Seguir leyendo el encoder y el joystick hasta que sean reconectados.//
  potenciometrosConectados = VerificarConexionPotenciometros(cantidadPots);
  LeerConvertirEncoder(); //Aquí mismo se valida si el encoder está conectado.

  if(potenciometrosConectados && EncoderConectado)
  {
        mensajesEmergenciaDesplegados = false;
  }

  LeerEscribirExtensorPCF(&mapeoCompletoAcelerador, &mapeoCompletoVolante, &entradaPCF3, &entradaPCF4,
                          JoystickConectado, EncoderConectado, ActuadoresConectados);
  //////////////////////////////////////////////////////////////////////////////
}

#endif

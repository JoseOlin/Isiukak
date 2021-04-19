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
#define FRENO_ACTIVADO 0
#define ACELERADOR_ACTIVADO 0 //Para definir si se usará el actuador de acelerador
//o se enviará la señal directamente a la ECM (La computadora del carro)
#define VOLANTE_ACTIVADO 1  //Para denotar que se controlará el volante con Encoder.
#define ENCODER_ACTIVADO 0 //Para tener retroalimentación de posición del volante.


unsigned int miliSegundosActuadorFrenoParoManual = 1500; // Tiempo de actuación del freno para el paro de emergencia.

int cantidadPots = 4;//****************DEFINE LA CANTIDAD DE POTENCIÓMETROS A VERIFICAR
///PARA EFECTOS DE PRUEBAS SE PUEDE PONER EN 2 (PRUEBAS SIN PEDALES), PERO EN OPERACIÓN
///DEBE REVISAR TODOS LOS POTS SIEMPRE (4).

unsigned int umbralPotSuperior = 1000;
unsigned int umbralPotInferior = 80;

//unsigned int umbralActuadoresSuperior = 900;
//unsigned int umbralActuadoresInferior = 95;  //150
unsigned int umbralActuadoresSuperior = 850;
unsigned int umbralActuadoresInferior = 185;

//********************** Variables configuración *******************************


//********************Variables de programa***********************************//
int pinRefPotsBajo = 2;
int pinRefPotsAlto = 3;

int potenciometros[4] = {A0, A1, A2, A3};
//int pinesJoystick[2] = {A0, A1};
//int pinesActuadores[2] = {A2, A3};

uint8_t joystickPotVertical = true;
uint8_t joystickPotHorizontal = true;
uint8_t JoystickConectado = true;
uint8_t JoystickDesconectado = true; //Usada para mantener el LED activado al-
//gunos segundos, por ello una segunda variable, no es una tontería, ¿por quién
//nos tomas?
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
    del Joystick.  */
    unsigned int valorPot;
    boolean potsAltos = false;
    boolean potsBajos = false;
    boolean potsConectados = true;

    //Inicializacion de variables en caso de que se hayan vuelto a conectar.
    joystickPotVertical = true;
    joystickPotHorizontal = true;

    JoystickConectado = true;

    frenoConectado = true;
    aceleradorConectado = true;
    ActuadoresConectados = true;
    //El encoder no se valida en esta función, se hace de manera automática en cada lectura.

    digitalWrite(pinRefPotsBajo, HIGH);
    digitalWrite(pinRefPotsAlto, HIGH);
    delay(1);

    //Validar que al poner los dos extremos del potenciómetro en ALTO
    //el wiper mida arriba del umbral definido.
    for(unsigned int ii = 0;   ii<cantPots;     ii++)
    {
        valorPot = analogRead(potenciometros[ii]);

        #if DEBUG_POTS
        Serial.print("\tii: "); Serial.print(ii);
        Serial.print(",\tvalorPot: "); Serial.println(valorPot);
        #endif

        delay(1);

        if(ii == 0) //Joystick vertical
        {
            if(valorPot < umbralPotSuperior)
            {
            #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(",  **Joy_V ");
                    Serial.print("desconectado.**");
                    Serial.print(",\tvalorPot: "); Serial.println(valorPot);
                }
            #endif
                joystickPotVertical = false;
                contadorLEDJoystickDesconectado = 6;
            }
        }
        if(ii == 1) //Joystick Horizontal.
        {
            if(valorPot < umbralPotSuperior)
            {
            #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(", **Joy_H ");
                    Serial.print("desconectado.**");
                    Serial.print(",\tvalorPot: "); Serial.println(valorPot);
                }
            #endif
                joystickPotHorizontal = false;
                contadorLEDJoystickDesconectado = 6;
            }
        }
        JoystickConectado = joystickPotHorizontal && joystickPotVertical;
        //JoystickDesconectado = !JoystickConectado; //No aquí, este valor
        //se actualiza en el ciclo principal después de que el contadorLED__Desconectados  llega a 0.
    #if FRENO_ACTIVADO
        if(ii == 2) //Freno
        {
            if(valorPot < umbralActuadoresSuperior)
            {
            #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(", **Freno ");
                    Serial.print("desconectado.**");
                    Serial.print(",\tvalorPot: "); Serial.println(valorPot);
                }
            #endif
                frenoConectado = false;
                contadorLEDActuadoresDesconectados = 6;
            }
        }
    #endif
    #if ACELERADOR_ACTIVADO
        if(ii == 3)  //Acelerador.
        {
            if(valorPot < umbralActuadoresSuperior)
            {
                #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(", **Acelerador ");
                    Serial.println("desconectado.**");
                    Serial.print(",\tvalorPot: "); Serial.println(valorPot);
                }
                #endif
                aceleradorConectado = false;
                contadorLEDActuadoresDesconectados = 6;
            }
        }
    #endif

    #if ACELERADOR_ACTIVADO
        ActuadoresConectados = frenoConectado && aceleradorConectado;
    #else
        ActuadoresConectados = frenoConectado;
    #endif
        /////ActuadoresDesconectados = !ActuadoresConectados; //Para retro en los LEDs
    }

    potsAltos = ActuadoresConectados && JoystickConectado;

#if DEBUG_POTS
    if(potsAltos) //(potsAltos = ActuadoresConectados && JoystickConectado;)
    {
        Serial.println(". Todos Altos.");
    } else {
        Serial.print("Falla Pots_H: ");
        if(!JoystickConectado) Serial.print(" Joys_H, ");
        if(!ActuadoresConectados) Serial.print(" Acts_H.");
        Serial.print("\n");
    }
#endif

    //Validar que al poner ambos extremos de los potenciómetros a cero
    //todos los wipers marquen 0 ó 1.
    digitalWrite(pinRefPotsBajo, LOW);
    digitalWrite(pinRefPotsAlto, LOW);
    delay(1);
    for(unsigned int ii = 0;    ii < cantPots;     ii++)
    {
        valorPot = analogRead(potenciometros[ii]);
        delay(1);
    #if DEBUG_POTS
        Serial.print("\tii: "); Serial.print(ii);
        Serial.print(",\tvalorPot: "); Serial.println(valorPot);
    #endif

        if(ii == 0)
        {
            if(valorPot > umbralPotInferior)
            {
            #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(", **Joy_V");
                    Serial.print(" desconectado.**");
                    Serial.print(",\tvalorPot: "); Serial.println(valorPot);
                }
            #endif
                joystickPotVertical = false;
                contadorLEDJoystickDesconectado = 6;
            }
        }
        if(ii == 1)
        {
            if(valorPot > umbralPotInferior)
            {
            #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(",  **Joy_H");
                    Serial.print(" desconectado.**");
                    Serial.print(",\tvalorPot: "); Serial.println(valorPot);
                }
            #endif
                joystickPotHorizontal = false;
                contadorLEDJoystickDesconectado = 6;
            }
        }
        JoystickConectado = joystickPotHorizontal && joystickPotVertical;
        //JoystickDesconectado = !JoystickConectado; //No aquí. En principal
    #if FRENO_ACTIVADO
        if(ii == 2)
        {
            if(valorPot > umbralActuadoresInferior)
            {
                //potsConectados = false;
                #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(",  **Freno");
                    Serial.print(" desconectado.**");
                    Serial.print(",\tvalorPot: "); Serial.println(valorPot);
                }
                #endif
                frenoConectado = false;
                contadorLEDJoystickDesconectado = 6;
            }
        }
    #endif
    #if ACELERADOR_ACTIVADO
        if(ii == 3)
        {
            if(valorPot > umbralActuadoresInferior)
            {
                //potsConectados = false;
                #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(",  **Acelerador");
                    Serial.print(" desconectado.**");
                    Serial.print(",\tvalorPot: "); Serial.println(valorPot);
                }
                #endif
                aceleradorConectado = false;
                contadorLEDJoystickDesconectado = 6;
            }
        }
    #endif
  }

  #if ACELERADOR_ACTIVADO
    ActuadoresConectados = frenoConectado && aceleradorConectado;
  #else
    #if FRENO_ACTIVADO
        ActuadoresConectados = frenoConectado;
    #else
        ActuadoresConectados = true;
    #endif
  #endif
    //ActuadoresDesconectados = !ActuadoresConectados; //Esto no se hace aquí,
    //se hace en el ciclo principal después de que el contador llega a cero.

    potsBajos =  JoystickConectado && ActuadoresConectados;

    potsConectados = potsAltos && potsBajos;

#if DEBUG_POTS
    if(potsConectados)
    {
        Serial.println(". Todos Bajos.");
    }else{
        Serial.print("Falla Pots_L: ");
        if(!JoystickConectado) Serial.print(" Joys_L, ");
        if(!ActuadoresConectados) Serial.print(" Acts_L.");
        Serial.print("\n");
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

void ParoDeEmergencia(  )
{
    if(!mensajesEmergenciaDesplegados)
    {
        Serial.print("Paro Emerg:");
        if(JoystickDesconectado)
            Serial.print("Jys,");
        if(ActuadoresDesconectados)
            Serial.print("Acts");

    #if ENCODER_ACTIVADO
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
#if FRENO_ACTIVADO
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
#endif

#if ENCODER_ACTIVADO
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

#if VOLANTE_ACTIVADO
    setMotorSpeed_Protocol(volnAddress, 0); //Dejar de aplicar control al volante y frenar.
#endif

    //////**Seguir leyendo el encoder y el joystick hasta que sean reconectados.//
    potenciometrosConectados = VerificarConexionPotenciometros(cantidadPots);
    Serial.print("cantidadPots: "); Serial.print(cantidadPots);

#if ENCODER_ACTIVADO
    LeerConvertirEncoder(&EncoderDesconectado); //Aquí mismo se valida si el encoder está conectado.
    if(potenciometrosConectados && EncoderConectado) //EncoderConectado se actualiza dentro LeerEncoder().
#else
    //EncoderDesconectado = false; //Si el encoder no está activado no enviar señal de error.
    if(potenciometrosConectados)
#endif
    {
        mensajesEmergenciaDesplegados = false;
    }

    //LeerEscribirExtensorPCF(&mapeoCompletoAcelerador, &mapeoCompletoVolante, &entradaPCF3, &entradaPCF4,
    //                      JoystickDesconectado, EncoderDesconectado, ActuadoresDesconectados);

    LeerEscribirExtensorPCF(&mapeoCompletoVolante, &mapeoCompletoAcelerador, &entradaPCF3, &entradaPCF4,
                            !JoystickDesconectado, !EncoderDesconectado, !ActuadoresDesconectados);

    delay(100);
    //////////////////////////////////////////////////////////////////////////////
}

#endif

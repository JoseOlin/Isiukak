#ifndef SEGURIDAD
#define SEGURIDAD

///********************** Seguridad.hpp ***************************************///

#include "ComunicacionSerial.hpp"
#include "Config.hpp"
#include "Debug.hpp"
#include "ControlPedales.hpp"
#include "ControlVolante.hpp"
#include "ControlPalanca.hpp"
//#include "ExtensorPCF.hpp"

///**************************************************************************///
///********************* Variables configuración ****************************///

unsigned int miliSegundos_ActuadorFrenoParo_LazoAbierto = 1500; // Tiempo de actuación del freno para el paro de emergencia.

unsigned int cantidadPots = 4; //****************DEFINE LA CANTIDAD DE POTENCIÓMETROS A VERIFICAR


// Umbrales para la verificación de conexión de los potenciómetros del Joystick
unsigned int umbralPotJoy_Superior = 1000;
unsigned int umbralPotJoy_Inferior = 80;

// Umbrales para la verificación de conexión de los potenciómetros de los Actuadores.
//unsigned int umbralActuadoresSuperior = 900;
//unsigned int umbralActuadoresInferior = 95;  //150
unsigned int umbralPotActuadores_Superior = 850;
unsigned int umbralPotActuadores_Inferior = 185;
//unsigned int umbralActuadoresSuperior = 750;
//unsigned int umbralActuadoresInferior = 300;


//unsigned int cantIteracionesParaVerificacion = 25;
//25; //Aprox. cada 500 ms
//100; Cada 2 s
//250; //Aprox cada 5s
//500; //Aprox cada 10s
unsigned int periodoVerificacion = 2000; // Periodo de verificación en ms.

unsigned int cantIteracionesParaVerificacion = periodoVerificacion / periodoDeseado;

///********************* Fin Variables configuración ************************///


///********************* Variables de programa ********************************///

/// TODO: Cambiar el orden de los pines para dejar el 2 para Serial y que sea compatible con ST NUCLEO (Rx:, Tx: ).
int pinGNDVirtual = 2;
int pin5VVirtual = 3;

//int pinesJoystick[2] = {A0, A1};
//int pinesActuadores[2] = {A2, A3};
int potenciometros[4] = {A0, A1, A2, A3};

uint8_t JoystickPotVertical_Conectado = true;
uint8_t JoystickPotHorizontal_Conectado = true;
uint8_t Joystick_Conectado = true;

// Variables de sensores desconectados
uint8_t Freno_Conectado = true;
uint8_t Acelerador_Conectado = true;
uint8_t Actuadores_Conectados = true;
uint8_t Potenciometros_Conectados = true;

// Variables de sensores fuera de rango válido.
uint8_t ActuadoresRangoValidoBoot = false;
uint8_t JoystickCentrado = false;


uint8_t JoystickY_FueraRango = false;
uint8_t JoystickX_FueraRango = false;
uint8_t ActuadorAcelerador_FueraRango = false;
uint8_t ActuadorFreno_FueraRango = false;

uint8_t Potenciometros_EnRangoValido = true;


uint8_t ActuadorFreno_Moving = false;
uint8_t ActuadoresMoving = false;


uint8_t errorConexionesArranque = false;

/// Las variables LED_* se actualizan en aplicarRutinasSeguridad.
uint8_t LED_JoystickVerDesconectado = false;
uint8_t LED_JoystickHorDesconectado = false;
uint8_t LED_ActuadorFrenoDesconectado = false;
uint8_t LED_ActuadorAceleradorDesconectado = false;

boolean mensajeErrorArranque_Registrado = false;
uint8_t mensajeError_JoystickVer_Registrado = false;
uint8_t mensajeError_JoystickHor_Registrado = false;
uint8_t mensajeError_ActuadorFreno_Registrado = false;
uint8_t mensajeError_ActuadorAcelerador_Registrado = false;


//
uint8_t mensajeError_AceleradorFueraRango_Registrado = false;
uint8_t mensajeError_FrenoFueraRango_Registrado= false;
uint8_t mensajeError_JoystickY_FueraRango_Registrado = false;
uint8_t mensajeError_JoystickX_FueraRango_Registrado = false;

uint8_t LED_ActuadorAceleradorFueraRango = false;
uint8_t LED_ActuadorFrenoFueraRango = false;
uint8_t LED_JoystickYFueraRango = false;
uint8_t LED_JoystickX_FueraRango = false;

unsigned int contadorIteraciones = 0;

boolean NoParoManualEmergencia = true;
uint16_t delayParoEmergencia = 100;

boolean mensajesEmergenciaDesplegados = false;
boolean protocoloFrenadoImplementado = false;

unsigned int contadorPatronErroresArranque = 0;



bool arduinoNanoConectado = false;

/*
 * Se implementan los Niveles de error de acuerdo a Safety Concept for Autonomous Vehicles. Cap. 23 de Autonomous Driving
 * F0: OK
 * F1: Maintenance Required
 * F2: Return home. Return to maintenance/service station with reduced speed
 * F3: Safe parking. Stop at the next available parking space
 * F4: Immediate Stop. Stop the vehicle immediately at the side of the road without endangering other road users
 * F5: Emergency Stop. Immediate, controlled braking to a standstill with steering function, if possible
 * F6: Emergency braking. Immediate stopping of the vehicle by activating the brakes
 */
enum ErrorCodes { OK,
                  MaintenanceRequired,
                  ReturnHome,
                  SafeParking,
                  ImmediateStop,
                  EmergencyStop,
                  EmergencyBraking };

ErrorCodes estadoDelSistema;

enum NivelesDigitales {ALTO, BAJO};
///******************** Fin Variables de programa******************************///


///*************************** Prototipos de funciones ************************//


boolean verificarConexionPotenciometro(unsigned int indicePot, NivelesDigitales nivel, unsigned int umbral);
boolean VerificarConexionPotenciometros(unsigned int cantPots);
void ExtensorPCF_LeerEscribir();
void ExtensorPCF_ErroresArranque_LeerEscribir(uint8_t salida1, uint8_t salida2, uint8_t salida3, uint8_t salida4);
void volante_Inhibir();
void volante_Desinhibir();

boolean evaluarConexionesActuadores(uint8_t Freno_Conectado, uint8_t Acelerador_Conectado);
///*************************** Fin Prototipos *********************************//
///******************************************************************************/

///*********************** Funciones de verificación en el arranque ************///
boolean joytickBootCentered(int joy_X, int joy_Y)
{

    int errorJoyX = abs(joy_X - joyX_Center);
    boolean joystickIsCentered = true;

    #if JOYSTICK_ACTIVADO
    if(errorJoyX > joystickUmbralErrorCentrado)
    {
        joystickIsCentered = false;
    }

    int errorJoyY = abs(joy_Y - joyY_Center);
    if(errorJoyY > joystickUmbralErrorCentrado)
    {
        joystickIsCentered = false;
    }
    #endif

    return joystickIsCentered;
}

boolean actuators_BootValidPosition(int posFreno, int posAcelerador)
{

    boolean frenoRangoValido = true; // El freno podría haberse dejado extendido al apagar
        // Ese comportamiento es aceptable, siempre que la lectura esté dentro del rango
        // de extensión y retracción del actuador.
    boolean aceleradorRetraido = true; // El acelerador siempre debe estar retraído al arranque.
    boolean ActuadoresRangoValido;

#if ACELERADOR_ACTIVADO
    int errorAceleradorRetraido = posAcelerador - ActuadorAcelerador_valorRetraido;
    if(errorAceleradorRetraido > ActuadorAcelerador_umbralErrorArranque)
    {
        aceleradorRetraido = false;
        Serial.print("**El Acelerador no está retraído. Pos: ");
        Serial.println(posAcelerador);
    }
#endif

#if FRENO_ACTIVADO
    if(posFreno < (ActuadorFreno_valorRetraido - ActuadorFreno_umbralErrorArranque))
    {
        frenoRangoValido = false;
        Serial.println("**El Freno está por debajo del rango de retracción válido.**");
    }
    if(posFreno > (ActuadorFreno_valorExtendido + ActuadorFreno_umbralErrorArranque))
    {
        frenoRangoValido = false;
        Serial.println("**El Freno está por encima del rango de extensión válido.**");
    }
#endif
    ActuadoresRangoValido = aceleradorRetraido && frenoRangoValido;

    return ActuadoresRangoValido;
}

boolean actuatorsAreMoving()
{
    /*!
     *
     *
     */
    //boolean actuatorsWorking = true;
    //boolean brakeWorking = true;
    //boolean gasWorking = true;

    boolean comportamientoDirecto = false;
    uint8_t fijarPosicionFreno = false;

    int joystick_Y = joyY_Center;

#if FRENO_ACTIVADO

    // Validar que el freno se puede retraer.
    int contadorLlegadaFreno = 0;

    ControlarPedales(joystick_Y , fijarPosicionFreno, comportamientoDirecto);
    while(ActuadorFreno_ErrorPosicion > ActuadorFreno_umbralError)
    {
        ControlarPedales(joystick_Y, fijarPosicionFreno, comportamientoDirecto);
        delay(1);
        contadorLlegadaFreno++;
        if(contadorLlegadaFreno > ActuadorFreno_tiempoLlegada)
        {
            //brakeWorking = false;
            Serial.println("**El freno no llegó al setpoint.");
            Serial.print("ContadorFreno: "); Serial.println(contadorLlegadaFreno);
            //break;
            return false;
        }
    }

    joystick_Y = joyY_MaxVal;
    contadorLlegadaFreno = 0;

    ControlarPedales(joystick_Y, fijarPosicionFreno, comportamientoDirecto);
    while(ActuadorFreno_ErrorPosicion > ActuadorFreno_umbralError)
    {
        ControlarPedales(joystick_Y, fijarPosicionFreno, comportamientoDirecto);
        delay(1);
        contadorLlegadaFreno++;
        if(contadorLlegadaFreno > ActuadorFreno_tiempoLlegada)
        {
            //brakeWorking = false;
            Serial.println("**El freno no llegó al setpoint.");
            Serial.print("ContadorFreno: "); Serial.println(contadorLlegadaFreno);
            //break;
            return false;
        }
    }

    joystick_Y = joyY_Center;
    contadorLlegadaFreno = 0;

    ControlarPedales(joystick_Y, fijarPosicionFreno, comportamientoDirecto);
    while(ActuadorFreno_ErrorPosicion > ActuadorFreno_umbralError)
    {
        ControlarPedales(joystick_Y, fijarPosicionFreno, comportamientoDirecto);
        delay(1);
        contadorLlegadaFreno++;
        if(contadorLlegadaFreno > ActuadorFreno_tiempoLlegada)
        {
            //brakeWorking = false;
            Serial.println("**El freno no llegó al setpoint.**");
            //break;
            return false;
        }
    }
#endif

#if ACELERADOR_ACTIVADO
    joystick_Y = joyY_Center - 30;
    int contadorTiempoLlegada = 0;

    ControlarPedales(joystick_Y, fijarPosicionFreno, comportamientoDirecto);
    while(ActuadorAcelerador_ErrorPosicion > ActuadorAcelerador_umbralError)
    {
        ControlarPedales(joystick_Y, fijarPosicionFreno, comportamientoDirecto);
        delay(1);
        contadorTiempoLlegada++;
        if(contadorTiempoLlegada > ActuadorAcelerador_tiempoLlegada)
        {
            //gasWorking = false;
            Serial.println("**El Acelerador no llegó al setpoint.");
            //break;
            return false;
        }
    }

    joystick_Y = joyY_Center;
    contadorTiempoLlegada = 0;

    ControlarPedales(joystick_Y, fijarPosicionFreno, comportamientoDirecto);
    while(ActuadorAcelerador_ErrorPosicion > ActuadorAcelerador_umbralError)
    {
        ControlarPedales(joystick_Y, fijarPosicionFreno, comportamientoDirecto);
        delay(1);
        contadorTiempoLlegada++;
        if(contadorTiempoLlegada > ActuadorAcelerador_tiempoLlegada)
        {
            //gasWorking = false;
            Serial.println("**El Acelerador no llegó al setpoint.**");
            //break;
            return false;
        }
    }
#endif

    return true;
}


/*! Al arranque se verifica:
 + Que los potenciómetros de los Actuadores y Joystick estén conectados.
 + Que el joystick esté centrado en ambos ejes.
 - Que la posición de los actuadores se retraída. PENDIENTE.
 - Que ambos actuadores puedan moverse. Código propuesto; PENDIENTE de integración. Para minimizar el tiempo de arranque
    esto podría ejecutarse sólo cuando algún switch o botón esté presionado.

* \return Retorna true si hay errores, false si no hay errores */
boolean verificacionSeguridadArranque()
{
    boolean errorConexionesStart = false;

    Potenciometros_Conectados = VerificarConexionPotenciometros(cantidadPots);
    //Serial.print("Pots Conectados: ");

    if(Potenciometros_Conectados)
    {
        estadoDelSistema = ErrorCodes::OK;
    }
    else
    {
        estadoDelSistema = ErrorCodes::EmergencyBraking;
        Serial.println("**La revisión de potenciómetros devolvió errores.**");
    }

#if VALIDAR_RANGO
    retraerAcelerador();
    delay(500);

    ActuadoresRangoValidoBoot = actuatorsNormalPositionBoot(ActuadorFreno_Posicion, ActuadorAcelerador_Posicion);
    if(!ActuadoresRangoValidoBoot)
    {
        estadoDelSistema = ErrorCodes::ImmediateStop;
        Serial.println("**Los actuadores no están en su rango válido.**");
    }
#else
    ActuadoresRangoValidoBoot = true;
#endif


    JoystickCentrado = joytickBootCentered(Joystick_X, Joystick_Y);
    if(!JoystickCentrado)
    {
        estadoDelSistema = ErrorCodes::EmergencyBraking;
        Serial.print("**El Joystick no está centrado. X: "); Serial.print(Joystick_X);
        Serial.print(", Y: "); Serial.println(Joystick_Y);
    }
#if VALIDAR_MOVING
    ActuadoresMoving = actuatorsAreMoving();
#else
    ActuadoresMoving = true;
#endif

    errorConexionesStart = !Potenciometros_Conectados || !JoystickCentrado || !ActuadoresRangoValidoBoot || !ActuadoresMoving;

    return errorConexionesStart;
}

///******************* Fin Funciones de verificación en el arranque ************///

/*! \brief Valida que el joystick esté dentro de su rango válido joyMinVal y joyMaxVal
 * así como los actuadores Actuador_valorRetraido y Actuador_valorExtendido.
 * Si el pin analógico mide un valor fuera de ese rango (más un umbral) se considera
 * que hay un error.
 * Return true si el potenciómetro está dentro del rango válido, false si está fuera del rango.
 *
 * \return true si el potenciómetro está dentro del rango válido, false si está fuera del rango. */
boolean validarLimites_Potenciometros()
{
    boolean potenciometros_EnRango = true;

    if( (Joystick_Y > (joyY_MaxVal + joystick_UmbralFueraRango))
    ||  (Joystick_Y < (joyY_MinVal - joystick_UmbralFueraRango)) )
    {
        JoystickY_FueraRango = true;
    }

    if(Joystick_X > (joyX_MaxVal + joystick_UmbralFueraRango)
    || Joystick_X < (joyX_MinVal - joystick_UmbralFueraRango))
    {
        JoystickX_FueraRango = true;
    }

    // El pot del actuador del acelerador aumenta al retraerse.
    if(ActuadorAcelerador_Posicion > (ActuadorAcelerador_valorRetraido + ActuadorAcelerador_umbralErrorArranque)
    || ActuadorAcelerador_Posicion < (ActuadorAcelerador_valorExtendido - ActuadorAcelerador_umbralErrorArranque))
    {
        ActuadorAcelerador_FueraRango = true;
    }

    // El pot del actuador del freno aumenta al extenderse.
    if(ActuadorFreno_Posicion > (ActuadorFreno_valorExtendido + ActuadorFreno_umbralErrorArranque)
    || ActuadorFreno_Posicion < (ActuadorFreno_valorRetraido - ActuadorFreno_umbralErrorArranque))
    {
        ActuadorFreno_FueraRango = true;
    }

    potenciometros_EnRango = !JoystickY_FueraRango && !JoystickX_FueraRango && !ActuadorAcelerador_FueraRango && !ActuadorFreno_FueraRango;
    return potenciometros_EnRango;
}


/*! \brief Función para validar la conexión de los potenciómetros.
 * Si ambos extremos están en alto, el wiper debe medir algo cercano a 1023.  */
void verificacionPots_ponerExtremosEnAlto()
{
    // Conexión directa a las salidas digitales.
    digitalWrite(pinGNDVirtual, HIGH);
    digitalWrite(pin5VVirtual, HIGH);
}

/*! \brief Función para validar la conexión de los potenciómetros.
 * Si ambos extremos están en BAJO, el wiper debe medir algo cercano a 0. */
void verificacionPots_ponerExtremosEnBajo()
{
    // Conexión directa a las salidas digitales.
    digitalWrite(pinGNDVirtual, LOW);
    digitalWrite(pin5VVirtual, LOW);

    // Salidas del Arduino en Alto -> Salidas del Transistor en Bajo.
    //digitalWrite(pinGNDVirtual, HIGH);
    //digitalWrite(pin5VVirtual, HIGH);
}

/*! \brief Activar el Voltaje Virtual de los pines que alimentan los potenciómetros.
 * pinGNDVirtual=LOW, pin5VVirtual=HIGH. En esta configuración los pots funcionan normalmente. */
void verificacionPots_activarVoltajeVirtual()
{
    // Conexión directa a las salidas digitales.
    digitalWrite(pinGNDVirtual, LOW);
    digitalWrite(pin5VVirtual, HIGH);

    // Voltaje virtual con transistores
    //digitalWrite(pinGNDVirtual, HIGH);
    //digitalWrite(pin5VVirtual, LOW);
}

/*! \brief Verificar que los potenciómetros estén conectados.
 * Para hacer la verificación los potenciómetros se conectan a pines digitales (GND Virtual y 5V Virtual.
 * Al poner los extremos en LOW el wiper deberá medir 0V o muy cercano,
 * Al poner los extremos en HIGH el wiper deberá medir 5V o muy cercano.
 * Si las dos validaciones anteriores no se cumplen se asume desconexión.
 * Return true si los potenciómetros están conectados, false si están desconectados.
 *
 * PARÁMETROS:
 * \param cantPots: Cantidad de potenciómetros a verificar.
 * \return true si los potenciómetros están conectados, false si están desconectados.  */
boolean VerificarConexionPotenciometros(unsigned int cantPots)
{
    /* Los potenciómetros son la retroalimentacion de los actuadores y los dos ejes
    del Joystick.  */
    if(cantPots < 4)
    {
        Serial.print("**ADVERTENCIA: No se están verificando todos los Potenciómetros. **");
    }

    //unsigned int valorPot;
    boolean potsAltos = false;
    boolean potsBajos = false;

    boolean potsConectados = true;

    //Inicializacion de variables en caso de que se hayan vuelto a conectar.
    JoystickPotVertical_Conectado = true;
    JoystickPotHorizontal_Conectado = true;
    Joystick_Conectado = true;

    Freno_Conectado = true;
    Acelerador_Conectado = true;
    Actuadores_Conectados = true;
    /// En caso de usar encoder en el volante, no se valida en esta función,
    /// se hace de manera automática en cada lectura.


    ///*****************************************************///
    ///***************** Validación en ALTO.****************///
    verificacionPots_ponerExtremosEnAlto();
    delay(1);

    // Validar que al poner los dos extremos del potenciómetro en ALTO
    // el valor del wiper esté arriba del umbral umbralPotJoy_Superior.

#if JOYSTICK_ACTIVADO
    JoystickPotVertical_Conectado = verificarConexionPotenciometro(0, NivelesDigitales::ALTO, umbralPotJoy_Superior); // 0 -> Joystick vertical
    JoystickPotHorizontal_Conectado = verificarConexionPotenciometro(1, NivelesDigitales::ALTO, umbralPotJoy_Superior);
    Joystick_Conectado = JoystickPotHorizontal_Conectado && JoystickPotVertical_Conectado;
#endif

#if FRENO_ACTIVADO
    Freno_Conectado = verificarConexionPotenciometro(2, NivelesDigitales::ALTO, umbralPotActuadores_Superior);
#endif

#if ACELERADOR_ACTIVADO
    Acelerador_Conectado = verificarConexionPotenciometro(3, NivelesDigitales::ALTO, umbralPotActuadores_Superior);
#endif

    Actuadores_Conectados = evaluarConexionesActuadores(Freno_Conectado, Acelerador_Conectado);

    potsAltos = Actuadores_Conectados && Joystick_Conectado;

    #if DEBUG_POTS_ERROR
    if(!potsAltos) //(potsAltos = ActuadoresConectados && JoystickConectado;)
    {
        Serial.print("**Falla Pots_H: ");
        if(!Joystick_Conectado)
            Serial.print(" Joys_H, ");
        if(!Actuadores_Conectados)
            Serial.print(" Acts_H.");
        Serial.print("** \n");
    }
    #endif
    ///***************** FIN Validación en ALTO.*********************///
    ///**************************************************************///


    ///**************************************************************///
    ///****************** Validación en BAJO*************************///
    // Validar que al poner ambos extremos de los potenciómetros a cero
    // todos los wipers marquen 0 ó 1.
    verificacionPots_ponerExtremosEnBajo();
    delay(1);

#if JOYSTICK_ACTIVADO
    JoystickPotVertical_Conectado = verificarConexionPotenciometro(0, NivelesDigitales::BAJO, umbralPotJoy_Inferior);
    JoystickPotHorizontal_Conectado = verificarConexionPotenciometro(1, NivelesDigitales::BAJO, umbralPotJoy_Inferior);
    Joystick_Conectado = JoystickPotHorizontal_Conectado && JoystickPotVertical_Conectado;
#else
         Joystick_Conectado = true;
#endif

#if FRENO_ACTIVADO
    Freno_Conectado = verificarConexionPotenciometro(2, NivelesDigitales::BAJO, umbralPotActuadores_Inferior);
#endif

#if ACELERADOR_ACTIVADO
    Acelerador_Conectado = verificarConexionPotenciometro(3, NivelesDigitales::BAJO, umbralPotActuadores_Inferior);
#endif

    Actuadores_Conectados = evaluarConexionesActuadores(Freno_Conectado, Acelerador_Conectado);

    potsBajos =  Joystick_Conectado && Actuadores_Conectados;
    ///******************FIN Validación en BAJO**********************///
    ///**************************************************************///

    #if DEBUG_POTS_ERROR
    if(!potsBajos)
    {
        Serial.print("**Falla Pots_L: ");
        if(!Joystick_Conectado)
            Serial.print(" Joys_L, ");
        if(!Actuadores_Conectados)
            Serial.print(" Acts_L.");
        Serial.print("**\n");
    }
    #endif

    //Regresar los pines a la configuración normal.
    verificacionPots_activarVoltajeVirtual();

    potsConectados = potsAltos && potsBajos;

    return potsConectados;
}

/*! \brief Verifica que un potenciómetros esté conectado.
 * Es invocada por VerificarConexionPotenciometros.
 * \param indicePot:  Indice del potenciómetro a verificar:
 * 0=JoystickY,   1=JoystickX,   2=Freno,   3=Acelerador
 * \param nivel:
 * \param umbral:
 * \return  true si el potenciómetro está conectado, false si está desconectado. */
boolean verificarConexionPotenciometro(unsigned int indicePot, NivelesDigitales nivel, unsigned int umbral)
{ 
     unsigned int valorPot = analogRead(potenciometros[indicePot]);
     boolean potConectado = true;

    #if DEBUG_POTS
    Serial.print("\tii: "); Serial.print(indicePot);
    Serial.print(",\tvalorPot: "); Serial.println(valorPot);
    #endif

    if(nivel == NivelesDigitales::ALTO)
    {
        if(valorPot < umbral)
        {
        #if DEBUG_POTS_ERROR
            if(!mensajesEmergenciaDesplegados)
            {
                Serial.print(",  **Pot_"); Serial.print(indicePot);
                Serial.print(",\t**HighVal: "); Serial.println(valorPot);
            }
        #endif
            potConectado = false;
        }
        else
        {
            potConectado = true;
        }
    }
    else if(nivel == NivelesDigitales::BAJO)
    {
        if(valorPot > umbralPotJoy_Inferior)
        {
        #if DEBUG_POTS_ERROR
            if(!mensajesEmergenciaDesplegados)
            {
                Serial.print(",  **Pot_"); Serial.print(indicePot);
                Serial.print(",\t**LowVal: "); Serial.println(valorPot);
            }
        #endif
            potConectado = false;
        }
        else
        {
            potConectado = true;
        }
    }

    return potConectado;
}

boolean evaluarConexionesActuadores(uint8_t Freno_Conectado, uint8_t Acelerador_Conectado)
{
    boolean actuators_connected = false;
#if ACELERADOR_ACTIVADO
    #if FRENO_ACTIVADO
        actuators_connected = Freno_Conectado && Acelerador_Conectado;
    #else
        actuators_connected = Acelerador_Conectado;
    #endif
#else
    #if FRENO_ACTIVADO
        actuators_connected = Freno_Conectado;
    #else
        actuators_connected = true;
    #endif
#endif

    return actuators_connected;
}


/*! Aplicar las medidas de seguridad en función del error.  */
void aplicarRutinasSeguridad()
{
    /// Instrucciones de validación de potenciómetros conectados.
    if(!Acelerador_Conectado)
    {
        if(estadoDelSistema < ErrorCodes::ImmediateStop)
        {
            estadoDelSistema = ErrorCodes::ImmediateStop;
        }
        retraerAcelerador();
        //extenderFreno();
        //volante_Inhibir();

        if(!mensajeError_ActuadorAcelerador_Registrado)
        {
            Serial.println("**Acelerador Desconectado**");
            mensajeError_ActuadorAcelerador_Registrado = true;
            LED_ActuadorAceleradorDesconectado = true; // Encender el LED de error
        }
    }

    if(!Freno_Conectado)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyBraking)
        {
            estadoDelSistema = ErrorCodes::EmergencyBraking;
        }
        extenderFreno();
        // TODO: B. Evaluar la opción de activar control OpenLoop del freno en este caso.
        retraerAcelerador();
        // TODO: C. Automatizar la palanca de cambios y ponerla en Neutral.
        // TODO: C. Encender luces preventivas.

        if(!mensajeError_ActuadorFreno_Registrado)
        {
            Serial.println("**Freno Desconectado**");
            mensajeError_ActuadorFreno_Registrado = true;
            LED_ActuadorFrenoDesconectado = true; // Encender el LED de error
        }
    }

    if(!JoystickPotVertical_Conectado)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyBraking)
        {
            estadoDelSistema = ErrorCodes::EmergencyBraking;
        }
        extenderFreno();
        retraerAcelerador();

        if(!mensajeError_JoystickVer_Registrado)
        {
            Serial.println("**Joystick_Y Desconectado**");
            LED_JoystickVerDesconectado = true; // Encender el LED de error
            mensajeError_JoystickVer_Registrado = true;
        }
    }

    if(!JoystickPotHorizontal_Conectado)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyStop)
        {
            estadoDelSistema = ErrorCodes::EmergencyStop;
        }
        volante_Inhibir();
        ControlarVolante();

        //tipoControlVolante = TiposControlVolante::MODO_INHIBIDO;

        if(!mensajeError_JoystickHor_Registrado)
        {
            Serial.println("**Joystick_X Desconectado**");
            mensajeError_JoystickHor_Registrado = true;
            LED_JoystickHorDesconectado = true; // Encender el LED de error
        }
    }

    // TODO: Optimizar las funciones de seguridad por desconexión.
    //volante_Inhibir();
    //ControlarVolante();


    /// Instrucciones de validación de Potenciómetros dentro del rango válido
    if(ActuadorAcelerador_FueraRango)
    {
        if(estadoDelSistema < ErrorCodes::ImmediateStop)
        {
            estadoDelSistema = ErrorCodes::ImmediateStop;
        }
        retraerAcelerador();
        //extenderFreno();
        //volante_Inhibir();

        if(!mensajeError_AceleradorFueraRango_Registrado)
        {
            Serial.println("**Acelerador Fuera de Rango**");
            mensajeError_AceleradorFueraRango_Registrado = true;
            LED_ActuadorAceleradorFueraRango = true; // Encender el LED de error
        }
    }

    if(ActuadorFreno_FueraRango)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyBraking)
        {
            estadoDelSistema = ErrorCodes::EmergencyBraking;
        }
        extenderFreno();
        // TODO: B. Evaluar la opción de activar control OpenLoop del freno en este caso.
        retraerAcelerador();
        // TODO: C. Automatizar la palanca de cambios y ponerla en Neutral.
        // TODO: C. Encender luces preventivas.

        if(!mensajeError_FrenoFueraRango_Registrado)
        {
            Serial.println("**Freno Fuera de Rango válido**");
            mensajeError_FrenoFueraRango_Registrado = true;
            LED_ActuadorFrenoFueraRango = true; // Encender el LED de error
        }
    }

    if(JoystickY_FueraRango)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyBraking)
        {
            estadoDelSistema = ErrorCodes::EmergencyBraking;
        }
        extenderFreno();
        retraerAcelerador();

        if(!mensajeError_JoystickY_FueraRango_Registrado)
        {
            Serial.println("**Joystick_Y Fuera Rango**");
            LED_JoystickYFueraRango = true; // Encender el LED de error
            mensajeError_JoystickY_FueraRango_Registrado = true;
        }
    }

    if(JoystickX_FueraRango)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyStop)
        {
            estadoDelSistema = ErrorCodes::EmergencyStop;
        }
        volante_Inhibir();
        ControlarVolante();

        if(!mensajeError_JoystickX_FueraRango_Registrado)
        {
            Serial.println("**Joystick_X Fuera Rango**");
            mensajeError_JoystickX_FueraRango_Registrado = true;
            LED_JoystickX_FueraRango = true; // Encender el LED de error
        }
    }


    // Seguir leyendo los potenciómetros en caso de que se reconecten.
    Potenciometros_Conectados = VerificarConexionPotenciometros(cantidadPots);

    // Seguir leyendo los potenciómetros en caso de que vuelvan al rango válido.
    Potenciometros_EnRangoValido = validarLimites_Potenciometros();


    if(Potenciometros_Conectados && Potenciometros_EnRangoValido)
    {
        // El sistema volverá a funcionar, pero debe indicarse en el log que hubo un error.
        estadoDelSistema = ErrorCodes::SafeParking;
        // TODO: Agregar incidencia en el log.
        Serial.println("**Los componentes se han reconectado y están en el rango válido**");

        // Si un componente se reconecta, reiniciar las banderas de mensaje de Error registrado
        // mientras que los LEDs se mantendrán encendidos hasta el próximo inicio del sistema
        // para mantener alerta al usuario.
        mensajeError_JoystickVer_Registrado = false;
        mensajeError_JoystickHor_Registrado = false;
        mensajeError_ActuadorAcelerador_Registrado = false;
        mensajeError_ActuadorFreno_Registrado = false;

        mensajeError_JoystickY_FueraRango_Registrado = false;

        volante_Desinhibir();
    }
}


/*!
 *
 */
void desplegarPatronErroresArranque()
{
    static unsigned int periodoPatronErrores = 500;

    if(contadorPatronErroresArranque < periodoPatronErrores) {

        ExtensorPCF_ErroresArranque_LeerEscribir(JoystickCentrado, Potenciometros_Conectados, ActuadoresRangoValidoBoot, ActuadoresMoving);
    }
    else if(contadorPatronErroresArranque < (2 * periodoPatronErrores) )  {
        ExtensorPCF_ErroresArranque_LeerEscribir(0, 0, 0, 0); //Apagar todos los LED's
    }
    else {
        contadorPatronErroresArranque = 0;
    }

    contadorPatronErroresArranque++;

}


/*! \brief Pone el volante en modo Inhibido y manda llamar al control del volante para que aplique el modo.
 */
void volante_Inhibir()
{
    tipoControlVolante = TiposControlVolante::MODO_INHIBIDO;
    ControlarVolante();
}

void volante_Desinhibir()
{
    //tipoC = MODO_POSICION_LIN;
    //tipoC = MODO_POSICION_LOG;
    //tipoC = MODO_VELOCIDAD_OPENLOOP; //Modo de control por velocidad sin retroalimentación del encoder.
    tipoControlVolante = TiposControlVolante::MODO_OPENLOOP_PORPARTES;
}

void ParoManualEmergencia()
{
    /* El paro manual de emergencia se activa si se presiona el botón correspondiente.
     * El comportamiento propuesto en este caso es:
     * - Contraer el acelerador. El acelerador se contrae con valores de control negativos.
     * - Extender el freno.
*/
    Serial.println("**Paro de Emergencia Manual.**");


    retraerAcelerador();

    if(Freno_Conectado)
    {
        //Si el freno está conectados utilizar la retroalimentación
        //para frenar automáticamente el carro.
        int ActuadorFreno_PosDeseadaParo = ActuadorFreno_valorParoEmergencia;

        ActuadorFreno_ErrorPosicion = ActuadorFreno_PosDeseadaParo - ActuadorFreno_Posicion;
        //ActuadorFreno_Control = ActuadorFreno_ErrorPosicion * ActuadorFreno_Kp;
        moverActuador(TipoActuador::Freno, ActuadorFreno_ErrorPosicion);
    #if DEBUG_PAROEMERGENCIA
        Serial.println("Freno Conectado.");
    #endif
    }
    else
    {
        //Si el freno está desconectado frenar en lazo abierto
        extenderFreno();
    #if DEBUG_PAROEMERGENCIA
        Serial.println("Freno Desconectado.");
    #endif
    }

    volante_Inhibir();
}


/*
void ParoDeEmergencia(  )
{
    /// TODO: Función anterior, borrar después de que funcione aplicarRutinasSeguridad()
    // El paro de emergencia se activa cuando se detecta algún componente desconectado.

    if(!mensajesEmergenciaDesplegados)
    {
        Serial.print("Paro Emerg:");
        if(!Joystick_Conectado){
            Serial.println("**Joystick Desconectado**"); }
        if(!Actuadores_Conectados) {
            Serial.print("**Actuadores Desconectados**"); }

    #if ENCODER_ACTIVADO
        if(EncoderConectado)
            Serial.println(", **Encoder Desconectado**");
    #endif

        mensajesEmergenciaDesplegados = true; //Para que sólo se despliegue una vez y quede en la pantalla.
    }

    // Contraer totalmente el acelerador.
    // El acelerador se contrae con valores de control negativos.
    setMotorSpeed_Protocol(ActuadorAcelerador_Address, -3200);

    // Poner el freno en lo máximo permitido (por el coche, no por el actuador.)
    #if FRENO_ACTIVADO
    if(Actuadores_Conectados)
    {
        //Si los actuadores están conectados seguir utilizando la retroalimentación
        //para frenar el carro.
        // ***TO-DO***: Buscar el valor del pot en extensión máxima.
        int ActuadorFreno_PosDeseada = ActuadorFreno_valorParoEmergencia;

        ActuadorFreno_ErrorPosicion = ActuadorFreno_Posicion - ActuadorFreno_PosDeseada ;
        ActuadorFreno_Control = ActuadorFreno_ErrorPosicion * ActuadorFreno_Kp;
        setMotorSpeed_Protocol(ActuadorFreno_Address, ActuadorFreno_Control);
    }
    else
    {
        //Si la retroalimentacion de los actuadores está desconectada frenar
        //el carro en lazo abierto (por tiempo)
        // *Los actuadores se extienden con valores positivos de control
        // Activar el actuador de freno durante 1.5 segundos.

        setMotorSpeed_Protocol(ActuadorFreno_Address, 3200);
        delay(miliSegundos_ActuadorFrenoParo_LazoAbierto);
        setMotorSpeed_Protocol(ActuadorFreno_Address, 0);
    }
    #endif

    #if ENCODER_ACTIVADO
    //Centrar el volante.
    // ***TO-DO***: Definir si es mejor centrarlo o mantenerlo en el último estado y frenar
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
    //setMotorSpeed_Protocol(volnAddress, 0); //Dejar de aplicar control al volante y frenar.
    #endif

    ////// **Seguir leyendo el encoder y el joystick hasta que sean reconectados.//
    Potenciometros_Conectados = VerificarConexionPotenciometros(cantidadPots);
    //Serial.print("cantidadPots: "); Serial.print(cantidadPots);

#if ENCODER_ACTIVADO
    LeerConvertirEncoder(&EncoderDesconectado); //Aquí mismo se valida si el encoder está conectado.
    if(potenciometrosConectados && EncoderConectado) //EncoderConectado se actualiza dentro LeerEncoder().
#else
    //EncoderDesconectado = false; //Si el encoder no está activado no enviar señal de error.
    if(Potenciometros_Conectados)
#endif
    {
        mensajesEmergenciaDesplegados = false;
    }

    //LeerEscribirExtensorPCF(&mapeoCompletoAcelerador, &mapeoCompletoVolante, &entradaPCF3, &entradaPCF4,
    //                      JoystickDesconectado, EncoderDesconectado, ActuadoresDesconectados);

    ExtensorPCF_LeerEscribir();


    //////////////////////////////////////////////////////////////////////////////
}
*/

#if PCF_ACTIVADO
void ExtensorPCF_LeerEscribir()
{

    uint8_t input0, input1, input2, input3;
    ExtensorPCF_Leer(&input0, &input1, &input2, &input3);

    fijarPosicionFreno    = !input0;
    modoCarreteraActivado = !input1;
    subirPalanca          = !input2;
    bajarPalanca          = !input3;

    ExtensorPCF_Escribir(!LED_ActuadorAceleradorDesconectado,
                         !LED_JoystickHorDesconectado,
                         !LED_ActuadorFrenoDesconectado,
                         !LED_JoystickVerDesconectado);
}

void ExtensorPCF_ErroresArranque_LeerEscribir(uint8_t salida1, uint8_t salida2, uint8_t salida3, uint8_t salida4)
{
    uint8_t input0,input1, input2, input3;
    ExtensorPCF_Leer(&input0, &input1, &input2, &input3);

    fijarPosicionFreno    = !input0;
    modoCarreteraActivado = !input1;
    subirPalanca          = !input2;
    bajarPalanca          = !input3;

    ExtensorPCF_Escribir(!salida1,
                         !salida2,
                         !salida3,
                         !salida4);
}
#endif

//#if ENCODER_ACTIVADO
/*bool VerificarConexionArduinoNano()
{
    // Función que se utiliza cuando el feedback de posición del actuador del freno
    // se hace con el encoder incremental.
    // En las pruebas realizadas a veces perdía el último dígito (por ejemplo 34 en lugar de 346)
    // por lo que se optó por usar un potenciómetro de precisión para la retroalimentación.
    //https://forum.arduino.cc/index.php?topic=500027.0
    //Verificar que se reciban 5 dígitos consecutivos.

    Serial.println("Verificación Conexión Arduino Nano iniciada.");

    const byte numChars = 16;
    char receivedChars[numChars];
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    bool newData = false;

    long tiempoMaximoRespuestaNano = 10000;
    long tiempoAntesLectura = millis();
    long tiempoActualLectura = millis();

    bool nanoConectado = false;

    smcSerial.println("UUUUUUUUU");
    while(nanoConectado == false)
    {
        if( (tiempoActualLectura - tiempoAntesLectura) < tiempoMaximoRespuestaNano)
        {
            //Serial.println("Dentro del if de tiempoMaximoRespuestaNano");
            if(Serial.available() > 0)
            {
                rc = Serial.read();
                //Serial.println(rc);

                if (recvInProgress == true)
                {
                    if (rc != endMarker)
                    {
                        receivedChars[ndx] = rc;
                        ndx++;
                        if (ndx >= numChars)
                        {
                            ndx = numChars - 1;
                        }
                    }
                    else { //rc == endMarker
                        receivedChars[ndx] = '\0'; // terminate the string
                        recvInProgress = false;
                        ndx = 0;
                        newData = true;
                    }
                }
                else if (rc == startMarker) {
                    recvInProgress = true;
                }
            } //endwhile

            if(newData)
            {
                //Serial.println("Mensaje Recibido del Nano: ");
                //Serial.println(receivedChars);
                if(strcmp(receivedChars, "Nano") == 0)
                {
                    // True si Arduino Nano está respondiendo.
                    //Serial.println("Nano Conectado");
                    nanoConectado = true;

                    //return true;
                } else { // False de lo contrario.
                    //Serial.println("Nano Desconectado");
                    nanoConectado = false;
                    //return false;
                }
                newData = false;
                //break;
            }
            tiempoActualLectura = millis();

        }
        else  // (tiempoActualLectura - tiempoAntesLectura) >= tiempoMaximoRespuestaNano)
        {
            Serial.println("El Arduino Nano tardó demasiado en responder.");
            break;
        }
    }

    return nanoConectado;

}
*/
//#endif

#endif

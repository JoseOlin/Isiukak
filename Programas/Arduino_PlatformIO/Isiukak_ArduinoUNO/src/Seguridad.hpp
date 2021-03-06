#ifndef SEGURIDAD
#define SEGURIDAD

///********************** Seguridad.hpp ***************************************///
//#include <Arduino.h>

#include "Config.hpp"

#include "ComunicacionSerial.hpp"
#include "Debug.hpp"
#include "ControlPedales.hpp"
#include "ControlVolante.hpp"
#include "ControlPalanca.hpp"
#include "LecturaFeedback.hpp" //Includes Testing.hpp


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


uint8_t periodoDeseado = 30; //ms Periodo de funcionamiento del sistema en ms.
unsigned int periodoVerificacion = 2000; // Periodo de verificación en ms.

unsigned int cantIteracionesParaVerificacion = periodoVerificacion / periodoDeseado;
///********************* Fin Variables configuración ************************///


///********************* Variables de programa ********************************///

/// TODO: Cambiar el orden de los pines para dejar el 2 para Serial y que sea compatible con ST NUCLEO (Rx:, Tx: ).
int pinGNDVirtual = 2;
int pin5VVirtual = 3;

int potenciometros[4] = {A0, A1, A2, A3};

// Variables de potenciómetros desconectados
uint8_t Joystick_X_Conectado = false;
uint8_t Joystick_Y_Conectado = false;
uint8_t Joystick_Conectado = false;
uint8_t ActuadorAcelerador_Conectado = false;
uint8_t ActuadorFreno_Conectado = false;
uint8_t Actuadores_Conectados = false;

uint8_t Potenciometros_Conectados = false;

// Variables de sensores fuera de rango válido.
uint8_t Joystick_X_EnRango = false;
uint8_t Joystick_Y_EnRango = false;
uint8_t Joystick_EnRango = false;

uint8_t ActuadorAcelerador_EnRango = false;
uint8_t ActuadorFreno_EnRango = false;
uint8_t Actuadores_EnRango = false;

uint8_t Potenciometros_EnRangoValido = false;

// Variable
uint8_t Joystick_Centrado = false;

//uint8_t Actuadores_EnRangoValidoBoot = false;

// Variables para gestión de mensajes de error por desconexión.
uint8_t mensajeError_Joystick_X_Desconectado_Registrado = false;
uint8_t mensajeError_Joystick_Y_Desconectado_Registrado = false;
uint8_t mensajeError_Acelerador_Desconectado_Registrado = false;
uint8_t mensajeError_Freno_Desconectado_Registrado = false;


uint8_t mensajeError_Joystick_X_FueraRango_Registrado = false;
uint8_t mensajeError_JoystickY_FueraRango_Registrado = false;
uint8_t mensajeError_Acelerador_FueraRango_Registrado = false;
uint8_t mensajeError_Freno_FueraRango_Registrado = false;

uint8_t mensaje_Pots_Reconectados_y_EnRango_Registrado = false;

uint8_t mensajeError_Joystick_NoCentrado_Registrado = false;

boolean mensajeError_Arranque_Registrado = false;
boolean mensajesEmergenciaDesplegados = false;

// Variables validación de actuadores operativos.
uint8_t ActuadorFreno_Moving = false;
uint8_t ActuadorAcelerador_Moving = false;
uint8_t ActuadoresMoving = false;

uint8_t erroresArranque = false;

boolean posibleFalsoCorriente = false;


/// Las variables LED_* se mantienen activas hasta el reinicio del sistema,
/// aún si el componente se reconecta o vuelve al rango, para mantener alerta al usuario.
uint8_t LED_Joystick_X_Desconectado = false;
uint8_t LED_Joystick_Y_Desconectado = false;
uint8_t LED_ActuadorAcelerador_Desconectado = false;
uint8_t LED_ActuadorFreno_Desconectado = false;

uint8_t LED_JoystickX_FueraRango = false;
uint8_t LED_Joystick_Y_FueraRango = false;
uint8_t LED_ActuadorAcelerador_FueraRango = false;
uint8_t LED_ActuadorFreno_FueraRango = false;

uint8_t LED_Joystick_NoCentrado = false;


unsigned int contadorIteraciones = 0;

boolean BotonParoEmergenciaPulsado = true;
uint16_t delayParoEmergencia = 100;

//boolean protocoloFrenadoImplementado = false;

//unsigned int contadorPatronErroresArranque = 0;



/* Se implementan los Niveles de error de acuerdo a Safety Concept for Autonomous Vehicles.
 * Cap. 23 de Autonomous Driving.
 * F0: OK
 * F1: Maintenance Required
 * F2: Return home. Return to maintenance/service station with reduced speed
 * F3: Safe parking. Stop at the next available parking space
 * F4: Immediate Stop. Stop the vehicle immediately at the side of the road without endangering other road users
 * F5: Emergency Stop. Immediate, controlled braking to a standstill with steering function, if possible
 * F6: Emergency braking. Immediate stopping of the vehicle by activating the brakes  */
enum ErrorCodes { OK,                   // F0: OK
                  MaintenanceRequired,  // F1: Maintenance Required.
                  ReturnHome,           // F2: Return home. Return to maintenance/service station with reduced speed
                  SafeParking,          // F3: Safe parking. Stop at the next available parking space
                  ImmediateStop,        // F4: Immediate Stop. Stop the vehicle immediately at the side of the road without endangering other road users
                  EmergencyStop,        // F5: Emergency Stop. Immediate, controlled braking to a standstill with steering function, if possible
                  EmergencyBraking };   // F6: Emergency braking. Immediate stopping of the vehicle by activating the brakes

ErrorCodes EstadoDelSistema;

enum NivelesDigitales {BAJO, ALTO};
///*************************** Fin Variables de programa *****************************///


///**************************** Prototipos de funciones ******************************///
//boolean verificacionSeguridad_Boot();
//void aplicarRutinasSeguridad_boot(uint8_t &JoystickCentrado, ErrorCodes &EstadoDelSistema);

boolean potJoystick_EstaEnRango(int valorPot, int valorMin, int valorMax, int umbralFueraRango);
boolean Joystick_X_EstaEnRango();
boolean Joystick_Y_EstaEnRango();
void Joystick_EstaEnRango(int joystick_X, int joystick_Y,
        uint8_t &joystickX_EnRango, uint8_t &joystickY_EnRango, uint8_t &joystick_EnRango);

boolean Actuador_Acelerador_EstaEnRango();
boolean Actuador_Freno_EstaEnRango();

void Pots_verificacion_activarVoltajeVirtual();
void Pots_verificacion_ponerExtremosEnAlto();
void Pots_verificacion_ponerExtremosEnBajo();

uint8_t Potenciometros_VerificarConexion(
        uint8_t &joystick_X_conectado,          uint8_t &joystick_Y_conectado,      uint8_t &joystick_conectado,
        uint8_t &actuadorAcelerador_conectado,  uint8_t &actuadorFreno_conectado,   uint8_t &actuadores_conectados);

uint8_t Potenciometro_VerificarConexionSingular(unsigned int indicePot, NivelesDigitales nivel, unsigned int umbral);

boolean Potenciometros_EstanEnRango(
        const int joystick_X, const int joystick_Y,
        const int actuadorAcelerador_Posicion, const int actuadorFreno_Posicion,

        uint8_t &JoystickX_EnRango,          uint8_t &JoystickY_EnRango,     uint8_t &Joystick_EnRango,
        uint8_t &ActuadorAcelerador_EnRango, uint8_t &ActuadorFreno_EnRango, uint8_t &Actuadores_EnRango);

//boolean evaluarConexionesActuadores(uint8_t Freno_Conectado, uint8_t Acelerador_Conectado);
///******************************* Fin Prototipos*************************************///
///***********************************************************************************///


///*********************** Funciones de verificación en el arranque ************///
boolean leerBotonParoEmergencia()
{
    boolean botonParoEmergenciaPulsado;

    botonParoEmergenciaPulsado = !digitalRead(pinBotonParoEmergencia); // Normalmente alto.

    return botonParoEmergenciaPulsado;
}


boolean joystickBootCentered(int joy_X, int joy_Y)
{

    boolean joystickIsCentered = false;

#if JOYSTICK_ACTIVADO
    int errorJoyX = abs(joy_X - joyX_Center);
    int errorJoyY = abs(joy_Y - joyY_Center);

    if(errorJoyX > joystickUmbralErrorCentrado)
    {
        joystickIsCentered = false;
    }
    else
    {
        joystickIsCentered = true;
    }

    if(errorJoyY > joystickUmbralErrorCentrado)
    {
        joystickIsCentered = false;
    } else
    {
        joystickIsCentered = true;
    }

#else
    joystickIsCentered = true;
#endif

    return joystickIsCentered;
}


boolean actuatorsAreMoving()
{
    /*!
     *
     *
     */
    boolean actuatorsMoving = true;
    //boolean brakeWorking = true;
    //boolean gasWorking = true;

#if VALIDAR_MOVING
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
#endif

    return actuatorsMoving;
}



boolean verificacionSeguridad_Boot()
{
    /*! Al arranque se verifica:
     + Que los potenciómetros de los Actuadores y Joystick estén conectados.
     + Que el joystick esté centrado en ambos ejes.
     - Que la posición de los actuadores se retraída. PENDIENTE.
     - Que ambos actuadores puedan moverse. Código propuesto; PENDIENTE de integración. Para minimizar el tiempo de arranque
        esto podría ejecutarse sólo cuando algún switch o botón esté presionado.

    * \return Retorna true si hay errores, false si no hay errores */
    boolean errores_Boot = false;

    Potenciometros_Conectados = Potenciometros_VerificarConexion(Joystick_Y_Conectado,      Joystick_X_Conectado,           Joystick_Conectado,
                                                                ActuadorFreno_Conectado,   ActuadorAcelerador_Conectado,   Actuadores_Conectados);


#if VALIDAR_LIMITES_POTS
    Potenciometros_EnRangoValido = Potenciometros_EstanEnRango(Joystick_X, Joystick_Y, ActuadorAcelerador_Posicion, ActuadorFreno_Posicion,
                                                    Joystick_X_EnRango, Joystick_Y_EnRango, Joystick_EnRango,
                                                    ActuadorAcelerador_EnRango, ActuadorFreno_EnRango, Actuadores_EnRango );
#else
    Potenciometros_EnRangoValido = true;
#endif

    Joystick_Centrado = joystickBootCentered(Joystick_X, Joystick_Y);

#if VALIDAR_MOVING
    ActuadoresMoving = actuatorsAreMoving();
#else
    ActuadoresMoving = true;
#endif

    //errorConexionesStart = !Potenciometros_Conectados || !JoystickCentrado || !Potenciometros_EnRangoValido || !ActuadoresMoving;
    errores_Boot =  !Joystick_Centrado || !Joystick_EnRango || !Potenciometros_Conectados;

    return errores_Boot;
}


/*!  * \brief aplicarRutinasSeguridad_boot
 *
 *                                      */
void aplicarRutinasSeguridad_boot(uint8_t &JoystickCentrado, ErrorCodes &estadoDelSistema)
{
    if(!JoystickCentrado)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyBraking)
        {
            estadoDelSistema = ErrorCodes::EmergencyBraking;

            Acelerador_Inhibir(ActuadorAcelerador_EstaInhibido);
            Acelerador_Retraer();

            volante_Inhibir();

            if(!mensajeError_Joystick_NoCentrado_Registrado)
            {
               Serial.println("**El Joystick no está centrado**");
               mensajeError_Joystick_NoCentrado_Registrado = true;
               LED_Joystick_NoCentrado = true;
            }
        }
    }

    // Seguir leyendo en caso de que el error se corrija.
    JoystickCentrado = joystickBootCentered(Joystick_X, Joystick_Y);

    if(JoystickCentrado)
    {
        // Si el joystick se vuelve a centrar arrancar el sistema, reiniciar la variable de
        // mensaje de error, pero el LED se deja encendido.

        // El sistema volverá a funcionar, pero debe indicarse en el log que hubo un error.
        if(estadoDelSistema > ErrorCodes::SafeParking)
        {
            estadoDelSistema = ErrorCodes::SafeParking;

            mensajeError_Joystick_NoCentrado_Registrado = false;
        }
        volante_Desinhibir();
    }
}


///******************* Fin Funciones de verificación en el arranque ************///



boolean potJoystick_EstaEnRango(int valorPot, int valorMin, int valorMax, int umbralFueraRango)
{
    boolean potEnRango = false;

    if(valorPot > (valorMax + umbralFueraRango)
    || valorPot < (valorMin - umbralFueraRango))
    {
        potEnRango = false;
    }
    else
    {
        potEnRango = true;
    }

    return potEnRango;
}


boolean Joystick_X_EstaEnRango(const int joystick_X)
{
    boolean joystickX_EnRango = false;
    joystickX_EnRango = potJoystick_EstaEnRango(joystick_X,
                                                joyX_MinVal, joyX_MaxVal, joystick_UmbralFueraRango);

    return joystickX_EnRango;
}


boolean Joystick_Y_EstaEnRango(const int joystick_Y)
{
    boolean joystickY_EnRango = false;
    joystickY_EnRango = potJoystick_EstaEnRango(joystick_Y,
                                                joyY_MinVal, joyY_MaxVal, joystick_UmbralFueraRango);

    return joystickY_EnRango;
}


void Joystick_EstaEnRango(  const int joystick_X, const int joystick_Y,
                            uint8_t &JoystickX_EnRango, uint8_t &JoystickY_EnRango,  uint8_t &Joystick_EnRango )
{
    //boolean joystickX_EnRango = false;
    //boolean joystickY_EnRango = false;

    Joystick_EnRango = false;

    JoystickX_EnRango = Joystick_X_EstaEnRango(joystick_X);
    JoystickY_EnRango = Joystick_Y_EstaEnRango(joystick_Y);

    // Si cualquiera de los dos es true, la salida debe ser true (Fuera de Rango).
    Joystick_EnRango = JoystickX_EnRango && JoystickY_EnRango;
}

void Actuador_Acelerador_EstaEnRango(const int actuadorAcelerador_Posicion, uint8_t &Acelerador_EnRango)
{
    // El pot del actuador del acelerador aumenta al retraerse.
    if(actuadorAcelerador_Posicion > (ActuadorAcelerador_valorRetraido + ActuadorAcelerador_umbralError_Rango)
    || actuadorAcelerador_Posicion < (ActuadorAcelerador_valorExtendido - ActuadorAcelerador_umbralError_Rango))
    {
    #if DEBUG_ACTUATORS_RANGE
        //Serial.print("**GasOutRange: ");
        //Serial.print("valExt: "); Serial.print(ActuadorAcelerador_valorExtendido);
        //Serial.print("pos: "); Serial.print(actuadorAcelerador_Posicion); Serial.println("**");
    #endif
        Acelerador_EnRango = false;
    }
    else
    {
        Acelerador_EnRango = true;
    }

    //return Acelerador_EnRango;
}


void Actuador_Freno_EstaEnRango(const int actuadorFreno_Posicion, uint8_t &Freno_EnRango)
{
   if( actuadorFreno_Posicion > (ActuadorFreno_valorExtendido + ActuadorFreno_umbralError_Rango)
    || actuadorFreno_Posicion < (ActuadorFreno_valorRetraido - ActuadorFreno_umbralError_Rango))
    {
    #if DEBUG_ACTUATORS_RANGE
        Serial.print("**BrakeOutRange: "); Serial.print(actuadorFreno_Posicion); Serial.print("**");
    #endif
        Freno_EnRango = false;
    }
    else
    {
        Freno_EnRango = true;
    }

    //return Freno_EnRango;
}



boolean Potenciometros_EstanEnRango(const int joystick_X, const int joystick_Y,
                                    const int actuadorAcelerador_Posicion, const int actuadorFreno_Posicion,
                                    uint8_t &joystickX_EnRango, uint8_t &joystickY_EnRango, uint8_t &joystick_EnRango,
                                    uint8_t &actuadorAcelerador_EnRango, uint8_t &actuadorFreno_EnRango, uint8_t &actuadores_EnRango )
{
/*! \brief Valida que el joystick esté dentro de su rango válido joyMinVal y joyMaxVal
 * así como los actuadores Actuador_valorRetraido y Actuador_valorExtendido.
 *
 * Si el pin analógico mide un valor fuera de ese rango (más un umbral) se considera que
 * hay un error.
 *
 * \return true si el potenciómetro está dentro del rango válido, false si está fuera del rango.
****************************************************************************************/
    /*
    uint8_t JoystickY_EnRango = false;
    uint8_t JoystickX_EnRango = false;
    */
    boolean potenciometros_EnRango = false;


#if VALIDAR_LIMITES_JOYSTICK
    Joystick_EstaEnRango(joystick_X, joystick_Y,
                         joystick_EnRango, joystickY_EnRango, joystickX_EnRango);
#else
    joystick_EnRango = true;
#endif


#if VALIDAR_LIMITES_ACTUADORES
    Actuador_Acelerador_EstaEnRango(actuadorAcelerador_Posicion, actuadorAcelerador_EnRango);
    Actuador_Freno_EstaEnRango(actuadorFreno_Posicion, actuadorFreno_EnRango);
#else
    actuadorAcelerador_EnRango = true;
    actuadorFreno_EnRango = true;
#endif

    actuadores_EnRango = actuadorAcelerador_EnRango && actuadorFreno_EnRango;


    potenciometros_EnRango =    joystick_EnRango && actuadores_EnRango;

    return potenciometros_EnRango;
}


void Pots_verificacion_ponerExtremosEnAlto()
{
/*! \brief Función para validar la conexión de los potenciómetros.
 * Si ambos extremos están en alto, el wiper debe medir algo cercano a 1023.
****************************************************************************************/
    // Conexión directa a las salidas digitales.
    digitalWrite(pinGNDVirtual, HIGH);
    digitalWrite(pin5VVirtual, HIGH);
}


void Pots_verificacion_ponerExtremosEnBajo()
{
/*! \brief Función para validar la conexión de los potenciómetros.
 * Si ambos extremos están en BAJO, el wiper debe medir algo cercano a 0.
****************************************************************************************/
    // Conexión directa a las salidas digitales.
    digitalWrite(pinGNDVirtual, LOW);
    digitalWrite(pin5VVirtual, LOW);

    // Salidas del Arduino en Alto -> Salidas del Transistor en Bajo.
    //digitalWrite(pinGNDVirtual, HIGH);
    //digitalWrite(pin5VVirtual, HIGH);
}


void Pots_verificacion_activarVoltajeVirtual()
{
/*! \brief Activar el Voltaje Virtual de los pines que alimentan los potenciómetros.
 * pinGNDVirtual=LOW, pin5VVirtual=HIGH. En esta configuración los pots funcionan normalmente. */

    // Conexión directa a las salidas digitales.
    digitalWrite(pinGNDVirtual, LOW);
    digitalWrite(pin5VVirtual, HIGH);

    // Voltaje virtual con transistores
    //digitalWrite(pinGNDVirtual, HIGH);
    //digitalWrite(pin5VVirtual, LOW);
}


uint8_t Potenciometros_VerificarConexion (
    uint8_t &joystick_X_conectado,          uint8_t &joystick_Y_conectado,      uint8_t &joystick_conectado,
    uint8_t &actuadorAcelerador_conectado,  uint8_t &actuadorFreno_conectado,   uint8_t &actuadores_conectados)
{
/*! \brief Verificar que los potenciómetros estén conectados.
 * Para hacer la verificación los potenciómetros se conectan a pines digitales (GND Virtual y 5V Virtual.
 * Al poner los extremos en LOW el wiper deberá medir 0V o muy cercano,
 * Al poner los extremos en HIGH el wiper deberá medir 5V o muy cercano.
 * Si las dos validaciones anteriores no se cumplen se asume desconexión.
 * Return true si los potenciómetros están conectados, false si están desconectados.
 *
 * PARÁMETROS:
 * \param
 * \return true si los potenciómetros están conectados, false si están desconectados.  */

    /* Los potenciómetros son la retroalimentacion de los actuadores del
     * freno y el acelerador, así como los dos ejes del Joystick.  */

    // Inicialización de parámetros por referencia.
    joystick_X_conectado = false;
    joystick_Y_conectado = false;

    joystick_conectado = false;

    actuadorAcelerador_conectado = false;
    actuadorFreno_conectado = false;

    actuadores_conectados = false;


    // Variables locales para validar que el wiper va a HIGH cuando ambos extremos van a HIGH.
    uint8_t joystick_y_high = false;
    uint8_t joystick_x_high = false;
    uint8_t joystick_high = false;

    uint8_t actuador_freno_high = false;
    uint8_t actuador_acelerador_high = false;
    uint8_t actuadores_high = false;

    uint8_t pots_high = false;



    /// En caso de usar encoder en el volante, no se valida en esta función, se hace de
    /// manera automática en cada lectura.

    ///*******************************************************************************///
    ///******************************* Validación en ALTO ****************************///

    Pots_verificacion_ponerExtremosEnAlto();
    delay(1);

    // Validar que al poner los dos extremos del potenciómetro en ALTO
    // el valor del wiper esté arriba del umbral umbralPotJoy_Superior.

#if JOYSTICK_ACTIVADO
    //Joystick_Y_Conectado = verificarConexionPotenciometro(0, NivelesDigitales::ALTO, umbralPotJoy_Superior); // 0 -> Joystick vertical
    joystick_y_high = Potenciometro_VerificarConexionSingular(0, NivelesDigitales::ALTO, umbralPotJoy_Superior);
    //Joystick_X_Conectado = verificarConexionPotenciometro(1, NivelesDigitales::ALTO, umbralPotJoy_Superior);
    joystick_x_high = Potenciometro_VerificarConexionSingular(1, NivelesDigitales::ALTO, umbralPotJoy_Superior);
#else
    // Si no está activado, definirlos conectados.
    joystick_y_high = true;
    joystick_x_high = true;
#endif


#if FRENO_ACTIVADO
    //ActuadorFreno_Conectado = verificarConexionPotenciometro(2, NivelesDigitales::ALTO, umbralPotActuadores_Superior);
    actuador_freno_high = Potenciometro_VerificarConexionSingular(2, NivelesDigitales::ALTO, umbralPotActuadores_Superior);
#else
    actuador_freno_high = true;
#endif

#if ACELERADOR_ACTIVADO
    actuador_acelerador_high = Potenciometro_VerificarConexionSingular(3, NivelesDigitales::ALTO, umbralPotActuadores_Superior);
#else
    actuador_acelerador_high = true;
#endif

    joystick_high = joystick_y_high && joystick_x_high;
    actuadores_high = actuador_freno_high && actuador_acelerador_high;

    pots_high = actuadores_high  && joystick_high;

    #if DEBUG_POTS_ERROR
    if(!pots_high)
    {
        Serial.print("**Falla Pots_H: ");
        if(!Joystick_Conectado) {
            Serial.print(" Joys_H, "); }
        if(!Actuadores_Conectados){
            Serial.print(" Acts_H."); }
        Serial.print("** \n");
    }
    #endif
    ///*************************** FIN Validación en ALTO ****************************///
    ///*******************************************************************************///


    ///*******************************************************************************///
    ///****************************** Validación en BAJO******************************///
    // Validar que al poner ambos extremos de los potenciómetros a cero
    // todos los wipers marquen 0 ó 1.
    uint8_t joystick_y_low = false;
    uint8_t joystick_x_low = false;
    uint8_t joystick_low = false;

    uint8_t actuador_freno_low = false;
    uint8_t actuador_acelerador_low = false;
    uint8_t actuadores_low = false;

    uint8_t pots_low = false;

    Pots_verificacion_ponerExtremosEnBajo();
    delay(1);

#if JOYSTICK_ACTIVADO
    joystick_y_low = Potenciometro_VerificarConexionSingular(0, NivelesDigitales::BAJO, umbralPotJoy_Inferior);
    joystick_x_low = Potenciometro_VerificarConexionSingular(1, NivelesDigitales::BAJO, umbralPotJoy_Inferior);
#else
    joystick_y_low = true;
    joystick_x_low = true;
#endif

#if FRENO_ACTIVADO
    actuador_freno_low = Potenciometro_VerificarConexionSingular(2, NivelesDigitales::BAJO, umbralPotActuadores_Inferior);
#else
    actuador_freno_low = true;
#endif

#if ACELERADOR_ACTIVADO
    actuador_acelerador_low = Potenciometro_VerificarConexionSingular(3, NivelesDigitales::BAJO, umbralPotActuadores_Inferior);
#else
    actuador_acelerador_low = true;
#endif

    joystick_low = joystick_y_low && joystick_x_low;
    actuadores_low = actuador_freno_low && actuador_acelerador_low;

    pots_low = joystick_low && actuadores_low;
    ///******************FIN Validación en BAJO**********************///
    ///**************************************************************///

    #if DEBUG_POTS_ERROR
    if(!pots_low)
    {
        Serial.print("**Falla Pots_L: ");
        if(!joystick_low)
            Serial.print(" Joys_L, ");
        if(!actuadores_low)
            Serial.print(" Acts_L.");
        Serial.println("**");
    }
    #endif

    //Regresar los pines de voltaje virtual a la configuración normal.
    Pots_verificacion_activarVoltajeVirtual();

    uint8_t potsConectados = false;

    potsConectados = pots_high && pots_low;

    joystick_Y_conectado = joystick_y_high && joystick_y_low;
    joystick_X_conectado = joystick_x_high && joystick_x_low;
    joystick_conectado = joystick_Y_conectado && joystick_X_conectado;

    actuadorFreno_conectado = actuador_freno_high && actuador_freno_low;
    actuadorAcelerador_conectado = actuador_acelerador_high && actuador_acelerador_low;
    actuadores_conectados = actuadorFreno_conectado && actuadorAcelerador_conectado;

    return potsConectados;
}


uint8_t Potenciometro_VerificarConexionSingular(unsigned int indicePot, NivelesDigitales nivel, unsigned int umbral)
{
/*! \brief Verifica que un potenciómetro esté conectado.
 * Es invocada por VerificarConexionPotenciometros.
 * \param indicePot:  Indice del potenciómetro a verificar:
 * 0=JoystickY,   1=JoystickX,   2=Freno,   3=Acelerador
 * \param nivel:
 * \param umbral:
 * \return  true si el potenciómetro está conectado, false si está desconectado.
 ***************************************************************************************/

    /// TODO: Verificar que la variable mensajesEmergenciaDesplegados no esté evitando que se muestre
    /// el mensaje de error para algunos pots (por ejemplo, si el primero está desconectado y no se muestra
    /// el erro de que el segundo también está desconectado.
    unsigned int valorPot;

#if TESTING_MODE
    int indNivel;
    if(nivel == NivelesDigitales::BAJO)
        indNivel = 0;
    else if(nivel == NivelesDigitales::ALTO)
        indNivel = 1;
    valorPot = PotenciometrosVirtuales_ValidacionConexion[indNivel][indicePot];
#else
     valorPot = analogRead(potenciometros[indicePot]);
#endif

    uint8_t potConectado = false;

    #if DEBUG_POTS
    Serial.print("\tii: "); Serial.print(indicePot);
    Serial.print(",\tvalorPot: "); Serial.println(valorPot);
    #endif

    if(nivel == NivelesDigitales::ALTO)
    {
        if(valorPot < umbral)
        {
            potConectado = false;

        #if DEBUG_POTS_ERROR
            Serial.print(",  **Pot_"); Serial.print(indicePot);
            Serial.print(",\t**HighVal: "); Serial.println(valorPot);
        #endif
        }
        else
        {
            potConectado = true;
        }
    }
    else if(nivel == NivelesDigitales::BAJO)
    {
        if(valorPot > umbral)
        {
            potConectado = false;

        #if DEBUG_POTS_ERROR
            Serial.print(",  **Pot_"); Serial.print(indicePot);
            Serial.print(",\t**LowVal: "); Serial.println(valorPot);
        #endif
        }
        else
        {
            potConectado = true;
        }
    }

    return potConectado;
}


void aplicarRutinasSeguridad(
        uint8_t Joystick_X_Conectado, uint8_t Joystick_Y_Conectado,
        uint8_t ActuadorAcelerador_Conectado, uint8_t ActuadorFreno_Conectado,

        uint8_t Joystick_X_EnRango,   uint8_t Joystick_Y_EnRango,
        uint8_t ActuadorAcelerador_EnRango, uint8_t ActuadorFreno_EnRango,

        ErrorCodes &estadoDelSistema,
        uint8_t &acelerador_estaInhibido, uint8_t &freno_estaInhibido)
{
/*! Aplicar las medidas de seguridad en función del error.  */

    /// Validación de potenciómetros conectados.
    if(!Joystick_X_Conectado)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyStop)
        {
            estadoDelSistema = ErrorCodes::EmergencyStop;
        }
        volante_Inhibir();

        //tipoControlVolante = TiposControlVolante::MODO_INHIBIDO;

        if(!mensajeError_Joystick_X_Desconectado_Registrado)
        {
            Serial.println("**Joystick_X Desconectado**");
            mensajeError_Joystick_X_Desconectado_Registrado = true;
            LED_Joystick_X_Desconectado = true; // Encender el LED de error
        }
    }
    else
    {
        mensajeError_Joystick_X_Desconectado_Registrado = false;
    }

    if(!Joystick_Y_Conectado)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyBraking)
        {
            estadoDelSistema = ErrorCodes::EmergencyBraking;
        }
        Freno_Inhibir(freno_estaInhibido);
        Freno_Extender();

        Acelerador_Inhibir(acelerador_estaInhibido);
        Acelerador_Retraer();

        if(!mensajeError_Joystick_Y_Desconectado_Registrado)
        {
            Serial.println("**Joystick_Y Desconectado**");
            LED_Joystick_Y_Desconectado = true; // Encender el LED de error
            mensajeError_Joystick_Y_Desconectado_Registrado = true;
        }
    }
    else
    {
       mensajeError_Joystick_Y_Desconectado_Registrado = false;
    }

    if(!ActuadorAcelerador_Conectado)
    {
        if(estadoDelSistema < ErrorCodes::ImmediateStop)
        {
            estadoDelSistema = ErrorCodes::ImmediateStop;
        }
        Acelerador_Inhibir(acelerador_estaInhibido);
        Acelerador_Retraer();

        // Agregar variable para inhibir el acelerador y seguir controlando
        // los demás actuadores.

        if(!mensajeError_Acelerador_Desconectado_Registrado)
        {
            Serial.println("**Acelerador Desconectado**");
            mensajeError_Acelerador_Desconectado_Registrado = true;
            LED_ActuadorAcelerador_Desconectado = true; // Encender el LED de error
        }
    }
    else
    {
        mensajeError_Acelerador_Desconectado_Registrado = false;
    }

    if(!ActuadorFreno_Conectado)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyStop)
        {
            estadoDelSistema = ErrorCodes::EmergencyStop;
        }

        Freno_Inhibir(freno_estaInhibido); //Not apply feedback control.
        // TODO: B. Evaluar la opción de usar el eje Y del Joystick como control OpenLoop del freno
        // (Deshabilitando el acelerador).
        Freno_Extender(); //Open Loop extension.

        // TODO: C. Automatizar la palanca de cambios y ponerla en Neutral.
        // TODO: C. Encender luces preventivas.

        if(!mensajeError_Freno_Desconectado_Registrado)
        {
            Serial.println("**Freno Desconectado**");
            mensajeError_Freno_Desconectado_Registrado = true;
            LED_ActuadorFreno_Desconectado = true; // Encender el LED de error
        }
    }
    else
    {
        mensajeError_Freno_Desconectado_Registrado = false;
    }



    /// Validación de Potenciómetros dentro del rango válido
    if(!Joystick_X_EnRango)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyStop)
        {
            estadoDelSistema = ErrorCodes::EmergencyStop;
        }
        volante_Inhibir();

        if(!mensajeError_Joystick_X_FueraRango_Registrado)
        {
            Serial.println("**Joystick_X OutOfRange**");
            mensajeError_Joystick_X_FueraRango_Registrado = true;
            LED_JoystickX_FueraRango = true; // Encender el LED de error
        }
    }
    else
    {
        mensajeError_Joystick_X_FueraRango_Registrado = false;
    }

    if(!Joystick_Y_EnRango)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyBraking)
        {
            estadoDelSistema = ErrorCodes::EmergencyBraking;
        }
        Freno_Inhibir(freno_estaInhibido);
        Freno_Extender();

        Acelerador_Inhibir(acelerador_estaInhibido);
        Acelerador_Retraer();

        if(!mensajeError_JoystickY_FueraRango_Registrado)
        {
            Serial.println("**Joystick_Y OutOfRange**");
            mensajeError_JoystickY_FueraRango_Registrado = true;
            LED_Joystick_Y_FueraRango = true; // Encender el LED de error
        }
    }
    else
    {
        mensajeError_JoystickY_FueraRango_Registrado = false;
    }

#if VALIDAR_LIMITES_ACTUADORES
    if(!ActuadorAcelerador_EnRango)
    {
        if(estadoDelSistema < ErrorCodes::SafeParking)
        {
            estadoDelSistema = ErrorCodes::SafeParking;
        }
        //retraerAcelerador();

        if(!mensajeError_Acelerador_FueraRango_Registrado)
        {
            Serial.println("**Acelerador Fuera de Rango**");
            mensajeError_Acelerador_FueraRango_Registrado = true;
            LED_ActuadorAcelerador_FueraRango = true; // Encender el LED de error
        }
    }
    else
    {
        mensajeError_Acelerador_FueraRango_Registrado = false;
    }

    if(!ActuadorFreno_EnRango)
    {
        if(estadoDelSistema < ErrorCodes::SafeParking)
        {
            estadoDelSistema = ErrorCodes::SafeParking;
        }
        //extenderFreno();
        // TODO: B. Evaluar la opción de activar control OpenLoop del freno en este caso.
        //retraerAcelerador();


        if(!mensajeError_Freno_FueraRango_Registrado)
        {
            Serial.println("**Freno Fuera de Rango válido**");
            mensajeError_Freno_FueraRango_Registrado = true;
            LED_ActuadorFreno_FueraRango = true; // Encender el LED de error
        }
    }
    else
    {
        mensajeError_Freno_FueraRango_Registrado = false;
    }
#endif


    // En caso de que los elementos se reconecten en una lectura posterior, reiniciar los
    // mensajes, pero dejar encendidos los LEDS.
    if(Joystick_Y_Conectado && Joystick_Y_EnRango)
    {
        if(ActuadorAcelerador_Conectado/*&& ActuadorAcelerador_EnRango*/)
        {
            Acelerador_Desinhibir(acelerador_estaInhibido);
        }
        if(ActuadorFreno_Conectado /*&& ActuadorFreno_EnRango*/)
        {
            Freno_Desinhibir(freno_estaInhibido);
        }
    }

    if(Joystick_X_Conectado && Joystick_X_EnRango)
    {
        volante_Desinhibir();
    }



    if(Potenciometros_Conectados && Potenciometros_EnRangoValido)
    {
        if(estadoDelSistema > ErrorCodes::SafeParking)
        {
            // El sistema volverá a funcionar, pero debe indicarse en el log que hubo un error.
            estadoDelSistema = ErrorCodes::SafeParking;
            if(!mensaje_Pots_Reconectados_y_EnRango_Registrado)
            {
                Serial.println("**Componentes reconectados y en rango válido**");
                mensaje_Pots_Reconectados_y_EnRango_Registrado = true;
            }
        }
    }
    else
    {
        mensaje_Pots_Reconectados_y_EnRango_Registrado = false;
    }

    /// TODO: A. Validar las acciones de aplicarRutinasSeguridad.
    // TODO: Agregar incidencia en el log.
    // TODO: Optimizar las funciones de seguridad por desconexión.
    // TODO: C. Automatizar la palanca de cambios y ponerla en Neutral.
    // TODO: C. Encender luces preventivas.
}



void ParoBotonEmergencia()
{
    /* El paro manual de emergencia se activa si se presiona el botón correspondiente.
     * El comportamiento propuesto en este caso es:
     * - Contraer el acelerador. El acelerador se contrae con valores de control negativos.
     * - Extender el freno.
*/
    Serial.println("**Paro de Emergencia Manual.**");


    Acelerador_Inhibir(ActuadorAcelerador_EstaInhibido);
    Acelerador_Retraer();

    if(ActuadorFreno_Conectado)
    {
        //Si el freno está conectados utilizar la retroalimentación
        //para frenar automáticamente el carro.
        int ActuadorFreno_PosDeseadaParo = ActuadorFreno_valorParoEmergencia;

        ActuadorFreno_ErrorPosicion = ActuadorFreno_PosDeseadaParo - ActuadorFreno_Posicion;
        //ActuadorFreno_Control = ActuadorFreno_ErrorPosicion * ActuadorFreno_Kp;
        moverActuador(TipoActuador::Freno, ActuadorFreno_ErrorPosicion);
        #if DEBUG_PAROEMERGENCIA
        Serial.print("Closed Loop Brake. Error: ");
        Serial.println(ActuadorAcelerador_ErrorPosicion);
        #endif
    }
    else
    {
        //Si el freno está desconectado frenar en lazo abierto
        Freno_Inhibir(ActuadorFreno_EstaInhibido);
        Freno_Extender();
        #if DEBUG_PAROEMERGENCIA
        Serial.println("Open Loop Brake.");
        #endif
    }

    volante_Inhibir();
}

void verificacionSeguridad_Periodica(uint8_t &Potenciometros_Conectados)
{
/*! Si en el ciclo anterior todo resultó conectado, revisar los pots cada ciertas iteraciones
 * Si algo está desconectado, revisar cada ciclo, en caso de que los pots se reconecten.
 *
 ***************************************************************************************/
    contadorIteraciones++;
    if( (contadorIteraciones >= cantIteracionesParaVerificacion) || !Potenciometros_Conectados )
    {

        Potenciometros_Conectados  =
        Potenciometros_VerificarConexion(Joystick_X_Conectado,  Joystick_Y_Conectado,   Joystick_Conectado,
                                        ActuadorAcelerador_Conectado,   ActuadorFreno_Conectado,   Actuadores_Conectados);
        contadorIteraciones = 0;
    }
}


void verificacionSeguridad_Constante(uint8_t &Potenciometros_EnRangoValido)
{

    Potenciometros_EnRangoValido = Potenciometros_EstanEnRango(
                        Joystick_X, Joystick_Y,
                        ActuadorAcelerador_Posicion, ActuadorFreno_Posicion,
                        Joystick_X_EnRango, Joystick_Y_EnRango, Joystick_EnRango,
                        ActuadorAcelerador_EnRango, ActuadorFreno_EnRango, Actuadores_EnRango);
}


void desplegarInfoEstadoSistema()
{
    Serial.print(", edo: "); Serial.print(EstadoDelSistema);
}



#endif

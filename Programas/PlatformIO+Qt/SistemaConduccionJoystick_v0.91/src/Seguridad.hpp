#ifndef SEGURIDAD
#define SEGURIDAD

///********************** Seguridad.hpp ***************************************///



#include "ComunicacionSerial.hpp"
#include "Config.hpp"
#include "Debug.hpp"
#include "ControlPedales.hpp"
#include "ControlVolante.hpp"
#include "ControlPalanca.hpp"
#include "ExtensorPCF.hpp"

///**************************************************************************///
///********************* Variables configuración ****************************///
///**************************************************************************///
#define PUESTACERO 0


//o se enviará la señal directamente a la ECM (La computadora del carro)
#define ENCODER_ACTIVADO 0 //Para tener retroalimentación de posición del volante.

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



uint8_t periodoDeseado = 25; //ms Periodo de funcionamiento del sistema en ms.
//unsigned int cantIteracionesParaVerificacion = 25;
//25; //Aprox. cada 500 ms
//100; Cada 2 s
//250; //Aprox cada 5s
//500; //Aprox cada 10s
unsigned int periodoVerificacion = 2000; // Periodo de verificación en ms.

unsigned int cantIteracionesParaVerificacion = periodoVerificacion / periodoDeseado;

///**************************************************************************///
///********************* Fin Variables configuración ************************///
///**************************************************************************///


///****************************************************************************///
///********************Variables de programa***********************************///
///****************************************************************************///
/// TODO: Cambiar el orden de los pines para dejar el 2 para Serial y que sea compatible con ST NUCLEO.
int pinGNDVirtual = 2;
int pin5VVirtual = 3;

//int pinesJoystick[2] = {A0, A1};
//int pinesActuadores[2] = {A2, A3};
int potenciometros[4] = {A0, A1, A2, A3};

uint8_t JoystickPotVertical_Conectado = true;
uint8_t JoystickPotHorizontal_Conectado = true;
uint8_t Joystick_Conectado = true;

uint8_t Freno_Conectado = true;
uint8_t Acelerador_Conectado = true;
uint8_t Actuadores_Conectados = true;
uint8_t Potenciometros_Conectados = true;

uint8_t errorConexionesArranque = false;

uint8_t LED_JoystickVerDesconectado = false;
uint8_t LED_JoystickHorDesconectado = false;
uint8_t LED_ActuadorFrenoDesconectado = false;
uint8_t LED_ActuadorAceleradorDesconectado = false;

boolean mensajeErrorArranque_Registrado = false;
uint8_t mensajeError_JoystickVer_Registrado = false;
uint8_t mensajeError_JoystickHor_Registrado = false;
uint8_t mensajeError_ActuadorFreno_Registrado = false;
uint8_t mensajeError_ActuadorAcelerador_Registrado = false;


unsigned int contadorIteraciones = 0;

boolean NoParoManualEmergencia = true;
uint16_t delayParoEmergencia = 100;

boolean mensajesEmergenciaDesplegados = false;
boolean protocoloFrenadoImplementado = false;

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
///******************************************************************************/
///******************** Fin Variables de programa******************************///
///******************************************************************************/


//*************************** Prototipos de funciones ************************//
boolean VerificarConexionPotenciometros(unsigned int cantPots);

void ExtensorPCF_LeerEscribir();
//*************************** Fin Prototipos *********************************//



boolean verificacionSeguridadArranque()
{
    // Al arranque se verifica que los potenciómetros de actuadores y Joystick estén
    // conectados.
    // Si la verificación al arranque es satisfactoria el sistema inicia, aunque
    // cada determinado número de ciclos (cantIteracionesParaVerificacion) se vuelve a
    // realizar una verificación.
    // De momento se usan funciones distintas porque la del arranque además de definir
    // si algún elemento está desconectado envía un patrón de encendido a los LED's
    boolean errorConexionesStart = false;

    Potenciometros_Conectados = VerificarConexionPotenciometros(cantidadPots);

    Serial.print("Pots Conectados: ");
    Potenciometros_Conectados ? Serial.println("SI.") : Serial.println("NO.");

    if(Potenciometros_Conectados)
    {
        Serial.println("Sistema activado.");
        estadoDelSistema = ErrorCodes::OK;
    }
    else
    {
        Serial.println("Sistema NO activado. La revisión de potenciómetros devolvió errores");
    }
    errorConexionesStart = !Potenciometros_Conectados;

    return errorConexionesStart;
    //desplegarPatronErrores();
}

boolean VerificarConexionPotenciometros(unsigned int cantPots)
{
/* Función para verificar que los potenciómetros estén conectados.
 * Para hacer la verificación los potenciómetros se conectan a pines digitales.
 * Al poner los extremos en LOW el wiper deberá medir 0V o muy cercano,
 * Al poner los extremos en HIGH el wiper deberá medir 5V o muy cercano.
 *
 * PARÁMETROS:
  cantPots: Cantidad de potenciómetros a verificar
*/
    /* Los potenciómetros son la retroalimentacion de los actuadores y los dos ejes
    del Joystick.  */
    if(cantPots < 4)
    {
        // TODO: Enviar patrón de alerta a los LEDs.
        Serial.print("ADVERTENCIA: NO SE ESTÁN VERIFICANDO TODOS LOS POTS. ");
        Serial.print("ESTA CONFIGURACIÓN SÓLO DEBERÍA ACTIVARSE PARA EFECTOS DE PRUEBAS");
    }

    unsigned int valorPot;
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


    digitalWrite(pinGNDVirtual, HIGH);
    digitalWrite(pin5VVirtual, HIGH);
    delay(1);
    // TODO: Verificar si el delay dentro de VerificarConexionPotenciometros es necesario.

    /// Validación en ALTO.
    // Validar que al poner los dos extremos del potenciómetro en ALTO
    // el valor del wiper esté arriba del umbral umbralPotJoy_Superior.

    /*
#if JOYSTICK_ACTIVADO
    JoystickPotVertical_Conectado = verificarConexionPotenciometro(0, NivelesDigitales::ALTO, umbralPotJoy_Superior);
    JoystickPotHorizontal_Conectado = verificarConexionPotenciometro(1, NivelesDigitales::ALTO, umbralPotJoy_Superior);
    Joystick_Conectado = JoystickPotHorizontal_Conectado && JoystickPotVertical_Conectado;
#else
    Joystick_Conectado = true;
#endif

#if FRENO_ACTIVADO
    if(ActuadorFreno_TipoFeedback == TipoFeedback::ResistenciaVariable) {
        Freno_Conectado = verificarConexionPotenciometro(2, NivelesDigitales::ALTO, umbralPotActuadores_Superior);
    }
#endif
#if ACELERADOR_ACTIVADO
    Acelerador_Conectado = verificarConexionPotenciometro(3, NivelesDigitales::ALTO, umbralPotActuadores_Superior);
#endif
    evaluarConexionesActuadores();
*/
    /////ActuadoresDesconectados = !ActuadoresConectados; //Para retro en los LEDs



    for(unsigned int ii = 0;   ii<cantPots;     ii++)
    {
        valorPot = analogRead(potenciometros[ii]);

        #if DEBUG_POTS
        Serial.print("\tii: "); Serial.print(ii);
        Serial.print(",\tvalorPot: "); Serial.println(valorPot);
        #endif

        //delay(1);
        // TODO: Verificar si el delay de VerificarConexionPotenciometros DENTRO DEL FOR es necesario.
#if JOYSTICK_ACTIVADO
        if(ii == 0) //Joystick vertical
        {
            if(valorPot < umbralPotJoy_Superior)
            {
            #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(",  **Joy_V** ");
                    Serial.print(",\tHighVal: "); Serial.println(valorPot);
                }
            #endif
                JoystickPotVertical_Conectado = false;
            }
        }
        if(ii == 1) //Joystick Horizontal.
        {
            if(valorPot < umbralPotJoy_Superior)
            {
            #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(", **Joy_H**");
                    Serial.print(",\tHighVal: "); Serial.println(valorPot);
                }
            #endif
                JoystickPotHorizontal_Conectado = false;
            }
        }


        Joystick_Conectado = JoystickPotHorizontal_Conectado && JoystickPotVertical_Conectado;
#else
        Joystick_Conectado = true;
#endif
        //JoystickDesconectado = !JoystickConectado; //No aquí, este valor
        //se actualiza en el ciclo principal después de que el contadorLED__Desconectados  llega a 0.
    #if FRENO_ACTIVADO
        if(ActuadorFreno_TipoFeedback == TipoFeedback::ResistenciaVariable)
        {
            if(ii == 2) //Freno
            {
                if(valorPot < umbralPotActuadores_Superior)
                {
                #if DEBUG_POTS_ERROR
                    if(!mensajesEmergenciaDesplegados)
                    {
                        Serial.print(", **Freno** ");
                        Serial.print(",\tHighVal: "); Serial.println(valorPot);
                    }
                #endif
                    Freno_Conectado = false;
                }
            }
        }
    #endif

    #if ACELERADOR_ACTIVADO
        if(ii == 3)  //Acelerador.
        {
            if(valorPot < umbralPotActuadores_Superior)
            {
                #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(", **Accel** ");
                    Serial.print(",\tHighVal: "); Serial.println(valorPot);
                }
                #endif
                Acelerador_Conectado = false;
            }
        }
    #endif

    #if ACELERADOR_ACTIVADO
        Actuadores_Conectados = Freno_Conectado && Acelerador_Conectado;
    #else
        #if FRENO_ACTIVADO
                Actuadores_Conectados = Freno_Conectado;
        #else
                Actuadores_Conectados = true;
        #endif
    #endif
        /////ActuadoresDesconectados = !ActuadoresConectados; //Para retro en los LEDs
    }

    potsAltos = Actuadores_Conectados && Joystick_Conectado;

    #if DEBUG_POTS
    if(potsAltos) //(potsAltos = ActuadoresConectados && JoystickConectado;)
    {
        Serial.println(". Todos Altos.");
    } else {
        Serial.print("Falla Pots_H: ");
        if(!Joystick_Conectado) Serial.print(" Joys_H, ");
        if(!Actuadores_Conectados) Serial.print(" Acts_H.");
        Serial.print("\n");
    }
    #endif

    /// Validación en BAJO
    // Validar que al poner ambos extremos de los potenciómetros a cero
    // todos los wipers marquen 0 ó 1.
    digitalWrite(pinGNDVirtual, LOW);
    digitalWrite(pin5VVirtual, LOW);
    delay(1);

/*
    #if JOYSTICK_ACTIVADO
    JoystickPotHorizontal_Conectado = verificarConexionPotenciometro(0, NivelesDigitales::ALTO, umbralPotJoy_Inferior);
    JoystickPotHorizontal_Conectado = verificarConexionPotenciometro(1, NivelesDigitales::ALTO, umbralPotJoy_Inferior);
    #else
         Joystick_Conectado = true;
    #endif
*/

    for(unsigned int ii = 0;    ii < cantPots;     ii++)
    {
        valorPot = analogRead(potenciometros[ii]);
        //delay(1);
    #if DEBUG_POTS
        Serial.print("\tii: "); Serial.print(ii);
        Serial.print(",\tvalorPot: "); Serial.println(valorPot);
    #endif

#if JOYSTICK_ACTIVADO
        if(ii == 0)
        {
            if(valorPot > umbralPotJoy_Inferior )
            {
            #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(", **Joy_V**");
                    Serial.print(",\tLowVal: "); Serial.println(valorPot);
                }
            #endif
                JoystickPotVertical_Conectado = false;
            }
        }
        if(ii == 1)
        {
            if(valorPot > umbralPotJoy_Inferior)
            {
            #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(",  **Joy_H**");
                    Serial.print(",\tLowVal: "); Serial.println(valorPot);
                }
            #endif
                JoystickPotHorizontal_Conectado = false;
            }
        }
        Joystick_Conectado = JoystickPotHorizontal_Conectado && JoystickPotVertical_Conectado;
#else
     Joystick_Conectado = true;
#endif
        //JoystickDesconectado = !JoystickConectado; //No aquí. En principal
    #if FRENO_ACTIVADO
        if(ActuadorFreno_TipoFeedback == TipoFeedback::ResistenciaVariable)
        {
            if(ii == 2)
            {
                if(valorPot > umbralPotActuadores_Inferior)
                {
                    //potsConectados = false;
                    #if DEBUG_POTS_ERROR
                    if(!mensajesEmergenciaDesplegados)
                    {
                        Serial.print(",  **Freno**");
                        Serial.print(",\tLowVal: "); Serial.println(valorPot);
                    }
                    #endif
                    Freno_Conectado = false;
                }
            }
        }
        else if(ActuadorFreno_TipoFeedback == TipoFeedback::EncoderIncremental)
        {
            //TODO: Implementar función para validar que el encoder del freno esté conectado.
        }
    #endif

    #if ACELERADOR_ACTIVADO
        if(ii == 3)
        {
            if(valorPot > umbralPotActuadores_Inferior)
            {
                //potsConectados = false;
                #if DEBUG_POTS_ERROR
                if(!mensajesEmergenciaDesplegados)
                {
                    Serial.print(",  **Accel**");
                    Serial.print(",\tLowVal: "); Serial.println(valorPot);
                }
                #endif
                Acelerador_Conectado = false;
            }
        }
    #endif
  }

    #if ACELERADOR_ACTIVADO
        #if FRENO_ACTIVADO
            Actuadores_Conectados = Freno_Conectado && Acelerador_Conectado;
        #else
            Actuadores_Conectados = Acelerador_Conectado;
        #endif
    #else
        #if FRENO_ACTIVADO
            Actuadores_Conectados = Freno_Conectado;
        #else
            Actuadores_Conectados = true;
        #endif
    #endif
    //ActuadoresDesconectados = !ActuadoresConectados; //Esto no se hace aquí,
    //se hace en el ciclo principal después de que el contador llega a cero.

    potsBajos =  Joystick_Conectado && Actuadores_Conectados;

    potsConectados = potsAltos && potsBajos;

    #if DEBUG_POTS
    if(potsConectados)
    {
        Serial.println(". Todos Bajos.");
    }
    else
    {
        Serial.print("Falla Pots_L: ");
        if(!Joystick_Conectado)
            Serial.print(" Joys_L, ");
        if(!Actuadores_Conectados)
            Serial.print(" Acts_L.");
        Serial.print("\n");
    }
    #endif

    //Regresar los pines a la configuración normal.
    digitalWrite(pinGNDVirtual, LOW);
    digitalWrite(pin5VVirtual, HIGH);

    return potsConectados;
}


boolean verificarConexionPotenciometro(unsigned int indicePot, NivelesDigitales nivel, unsigned int umbral)
{
     unsigned int valorPot = analogRead(potenciometros[indicePot]);
     boolean potConectado = true;

    #if DEBUG_POTS
    Serial.print("\tii: "); Serial.print(indicePot);
    Serial.print(",\tvalorPot: "); Serial.println(valorPot);
    #endif

    //delay(1);
    // TODO: Verificar si el delay de VerificarConexionPotenciometros DENTRO DEL FOR es necesario.

    if(nivel == NivelesDigitales::ALTO) //Joystick vertical
    {
        if(valorPot < umbral)
        {
        #if DEBUG_POTS_ERROR
            if(!mensajesEmergenciaDesplegados)
            {
                Serial.print(",  **Pot_"); Serial.print(indicePot); Serial.print("** ");
                Serial.print(",\tHighVal: "); Serial.println(valorPot);
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
        if(valorPot > umbralPotJoy_Inferior )
        {
        #if DEBUG_POTS_ERROR
            if(!mensajesEmergenciaDesplegados)
            {
                Serial.print(",  **Pot_"); Serial.print(indicePot); Serial.print("** ");
                Serial.print(",\tLowVal: "); Serial.println(valorPot);
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

void evaluarConexionesActuadores()
{
#if ACELERADOR_ACTIVADO
    #if FRENO_ACTIVADO
        Actuadores_Conectados = Freno_Conectado && Acelerador_Conectado;
    #else
            Actuadores_Conectados = Acelerador_Conectado;
    #endif
#else
    #if FRENO_ACTIVADO
            Actuadores_Conectados = Freno_Conectado;
    #else
            Actuadores_Conectados = true;
    #endif
#endif
}

//boolean verificarJoystick_PotHorizontal(unsigned int indicePot, NivelesDigitales nivel)
//{}



void aplicarRutinasSeguridad()
{
    if(!Acelerador_Conectado)
    {
        if(estadoDelSistema < ErrorCodes::ImmediateStop)
        {
            estadoDelSistema = ErrorCodes::ImmediateStop;
        }
        retraerAcelerador();
        if(!mensajeError_ActuadorAcelerador_Registrado)
        {
            Serial.println("**Actuador Acelerador Desconectado**");
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
        // TODO: Evaluar la opción de activar control OpenLoop del freno en este caso.
        retraerAcelerador();
        // TODO: Automatizar la palanca de cambios y ponerla en Neutral.
        // TODO: Encender luces preventivas.

        if(!mensajeError_ActuadorFreno_Registrado)
        {
            Serial.println("**Actuador Freno Desconectado**");
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
        // TODO: Evaluar la opción de activar control OpenLoop del freno en este caso.
        retraerAcelerador();
        // TODO: Automatizar la palanca de cambios y ponerla en Neutral.
        // TODO: Encender luces preventivas.

        if(!mensajeError_JoystickVer_Registrado)
        {
            Serial.println("**Joystick Vertical Desconectado**");
            mensajeError_JoystickVer_Registrado = true;
            LED_JoystickVerDesconectado = true; // Encender el LED de error
        }
    }

    if(!JoystickPotHorizontal_Conectado)
    {
        if(estadoDelSistema < ErrorCodes::EmergencyStop)
        {
            estadoDelSistema = ErrorCodes::EmergencyStop;
        }
        tipoControlVolante = TiposControlVolante::MODO_INHIBIDO;

        if(!mensajeError_JoystickVer_Registrado)
        {
            Serial.println("**Joystick Horizontal Desconectado**");
            mensajeError_JoystickVer_Registrado = true;
            LED_JoystickVerDesconectado = true; // Encender el LED de error
        }
    }

    // Una vez que aplica las acciones asociadas a los errores, seguir leyendo los potenciómetros
    // en caso de que se reconecten

    Potenciometros_Conectados = VerificarConexionPotenciometros(cantidadPots);
    if(Potenciometros_Conectados)
    {
        // El sistema volverá a funcionar, pero debe indicarse en el log que hubo un error.
        estadoDelSistema = ErrorCodes::SafeParking;
        // TODO: Agregar incidencia en el log.
        Serial.println("Los componentes se han reconectado");

        // Si un componente se reconecta, reiniciar las banderas de mensaje de Error registrado
        // mientras que los LEDs se mantendrán encendidos hasta el próximo inicio del sistema
        // para mantener alerta al usuario.
        mensajeError_JoystickVer_Registrado = false;
        mensajeError_JoystickHor_Registrado = false;
        mensajeError_ActuadorAcelerador_Registrado = false;
        mensajeError_ActuadorFreno_Registrado = false;

        tipoControlVolante = TiposControlVolante::MODO_OPENLOOP_PORPARTES;
    }
}


void ParoManualEmergencia()
{
    /* El paro manual de emergencia se activa si se presiona el botón correspondiente.
     * El comportamiento propuesto en este caso es:
     * - Contraer el acelerador. El acelerador se contrae con valores de control negativos.
     * - Extender el freno.
*/
    Serial.println("Paro Emerg Manual.");

    retraerAcelerador();

    if(Freno_Conectado)
    {
        //Si el freno está conectados utilizar la retroalimentación
        //para frenar automáticamente el carro.
        // TODO: Buscar el valor del pot en extensión máxima.
        // TODO: Modificar el paro de emergencia para el nuevo actuador con encoder.
        int ActuadorFreno_PosDeseadaParo = actFreno_valorParoEmergencia;

        ActuadorFreno_ErrorPosicion = ActuadorFreno_PosDeseadaParo - ActuadorFreno_Posicion;
        //ActuadorFreno_Control = ActuadorFreno_ErrorPosicion * ActuadorFreno_Kp;
        moverActuador(TipoActuador::Freno, ActuadorAcelerador_ErrorPosicion);
    }
    else
    {
        //Si el freno está desconectado frenar en lazo abierto
        extenderFreno();
    }

}

void ParoDeEmergencia(  ) /// Función anterior, borrar después de que funcione aplicarRutinasSeguridad()
{
    /* El paro de emergencia se activa cuando se detecta algún componente desconectado.
     *
     *
     */
    if(!mensajesEmergenciaDesplegados)
    {
        Serial.print("Paro Emerg:");
        if(!Joystick_Conectado)
            Serial.print("JysDscnc,");
        if(!Actuadores_Conectados)
            Serial.print("ActsDscnc");

    #if ENCODER_ACTIVADO
        if(EncoderConectado)
            Serial.print(", EncDescnc");
    #endif

        Serial.println("."); //Fin de linea de error.

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
        //***TO-DO***: Buscar el valor del pot en extensión máxima.
        int ActuadorFreno_PosDeseada = actFreno_valorParoEmergencia;

        ActuadorFreno_ErrorPosicion = ActuadorFreno_Posicion - ActuadorFreno_PosDeseada ;
        ActuadorFreno_Control = ActuadorFreno_ErrorPosicion * ActuadorFreno_Kp;
        setMotorSpeed_Protocol(ActuadorFreno_Address, ActuadorFreno_Control);
    }
    else
    {
        //Si la retroalimentacion de los actuadores está desconectada frenar
        //el carro en lazo abierto (por tiempo)
        //*Los actuadores se extienden con valores positivos de control
        // Activar el actuador de freno durante 1.5 segundos.

        setMotorSpeed_Protocol(ActuadorFreno_Address, 3200);
        delay(miliSegundos_ActuadorFrenoParo_LazoAbierto);
        setMotorSpeed_Protocol(ActuadorFreno_Address, 0);
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
    //setMotorSpeed_Protocol(volnAddress, 0); //Dejar de aplicar control al volante y frenar.
    #endif

    //////**Seguir leyendo el encoder y el joystick hasta que sean reconectados.//
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



void ExtensorPCF_LeerEscribir()
{
    ExtensorPCF_Leer(&fijarPosicionFreno, &modoCarreteraActivado, &bajarPalanca, &subirPalanca);
    ExtensorPCF_Escribir(!LED_ActuadorAceleradorDesconectado,
                         !LED_JoystickHorDesconectado,
                         !LED_ActuadorFrenoDesconectado,
                         !LED_JoystickVerDesconectado);
}

bool VerificarConexionArduinoNano()
{
    /*Función que se utiliza cuando el feedback de posición del actuador del freno
    * se hace con el encoder incremental.
    * En las pruebas realizadas a veces perdía el último dígito (por ejemplo 34 en lugar de 346)
    * por lo que se optó por usar un potenciómetro de precisión para la retroalimentación.
    //https://forum.arduino.cc/index.php?topic=500027.0
    //Verificar que se reciban 5 dígitos consecutivos.*/

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

    // TODO: Hacer una rutina al arranque que mueva el freno para garantizar que el encoder está funcionando.
}


#endif

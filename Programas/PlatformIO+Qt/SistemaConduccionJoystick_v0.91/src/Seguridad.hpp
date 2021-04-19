#ifndef SEGURIDAD
#define SEGURIDAD

#include "ComunicacionSerial.hpp"
#include "Debug.hpp"
#include "Config.hpp"
#include "ControlPedales.hpp"
#include "ControlVolante.hpp"
#include "ControlPalanca.hpp"
#include "ExtensorPCF.hpp"

/******************************************************************************/
///********************* Variables configuración ****************************///
/******************************************************************************/
#define PUESTACERO 0


//o se enviará la señal directamente a la ECM (La computadora del carro)
#define ENCODER_ACTIVADO 0 //Para tener retroalimentación de posición del volante.

unsigned int miliSegundosActuadorFrenoParoManual = 1500; // Tiempo de actuación del freno para el paro de emergencia.

unsigned int cantidadPots = 4; //****************DEFINE LA CANTIDAD DE POTENCIÓMETROS A VERIFICAR
///PARA EFECTOS DE PRUEBAS SE PUEDE PONER EN 2 (PRUEBAS SIN PEDALES, SÓLO JOYSTICK), PERO EN OPERACIÓN
///DEBE REVISAR TODOS LOS POTS SIEMPRE (4).

// Umbrales para la verificación de conexión de los potenciómetros del Joystick
unsigned int umbralPotSuperior = 1000;
unsigned int umbralPotInferior = 80;

// Umbrales para la verificación de conexión de los potenciómetros de los Actuadores.
//unsigned int umbralActuadoresSuperior = 900;
//unsigned int umbralActuadoresInferior = 95;  //150
unsigned int umbralActuadoresSuperior = 850;
unsigned int umbralActuadoresInferior = 185;
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

/******************************************************************************/
///********************* Variables configuración ****************************///
/******************************************************************************/

/******************************************************************************/
///********************Variables de programa***********************************//
/******************************************************************************/
int pinRefPotsBajo = 2;
int pinRefPotsAlto = 3;

int potenciometros[4] = {A0, A1, A2, A3};
//int pinesJoystick[2] = {A0, A1};
//int pinesActuadores[2] = {A2, A3};

uint8_t joystickPotVertical = true;
uint8_t joystickPotHorizontal = true;
uint8_t JoystickConectado = true;
uint8_t LEDJoystickDesconectado = true; //Usada para mantener el LED activado al-
//gunos segundos, por ello una segunda variable, no es una tontería, ¿por quién
//nos tomas? Hay que pensar mejor los nombres de las variables, te concedemos eso.
uint8_t contadorLEDJoystickDesconectado = 0;

uint8_t errorConexionesArranque = false;
boolean mensajeErrorArranqueDesplegado = false;
uint8_t frenoConectado = true;
uint8_t aceleradorConectado = true;
uint8_t ActuadoresConectados = true;
uint8_t LEDActuadoresDesconectados = true;

unsigned int contadorIteraciones = 0;
uint8_t contadorLEDActuadoresDesconectados = 0;

uint8_t LEDEncoderDesconectado = false;

uint8_t potenciometrosConectados = true;
boolean NoParoManualEmergencia = true;
uint16_t delayParoEmergencia = 100;

boolean mensajesEmergenciaDesplegados = false;
boolean protocoloFrenadoImplementado = false;

bool arduinoNanoConectado = false;
/******************************************************************************/
///******************** Fin Variables de programa******************************/
/******************************************************************************/


//*************************** Prototipos de funciones ************************//
boolean VerificarConexionPotenciometros(unsigned int cantPots);
void desplegarPatronErrores();
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

    potenciometrosConectados = VerificarConexionPotenciometros(cantidadPots);

    Serial.print("Pots Conectados: ");
    potenciometrosConectados ? Serial.println("SI.") : Serial.println("NO.");

    potenciometrosConectados
              ? Serial.println("Sistema activado.")
              : Serial.println("Sistema NO activado. La revisión de potenciómetros devolvió errores");
    errorConexionesStart = !potenciometrosConectados;

    return errorConexionesStart;
    //desplegarPatronErrores();

}

void desplegarPatronLEDsJoystickDesconectado()
{

}

void desplegarPatronLEDsActuadoresDesconectados()
{

}

void desplegarPatronErrores()
{
    //Encender LEDS
    if(!JoystickConectado)
    {
        LEDJoystickDesconectado = true;
        //desplegarPatronLEDsJoystickDesconectado();
    }
    if(!ActuadoresConectados)
    {
        LEDActuadoresDesconectados = true;
        //desplegarPatronLEDsActuadoresDesconectados();
    }
    //Apagar y encender el LED de Joystick Desconectado
    LeerEscribirExtensorPCF(&fijarPosicionFreno, &modoCarreteraActivado, &subirPalanca, &bajarPalanca,
                            !LEDJoystickDesconectado, !LEDEncoderDesconectado, !LEDActuadoresDesconectados);

    delay(delayParoEmergencia);

    //Apagar LEDs
    if(!JoystickConectado)
    {
        LEDJoystickDesconectado = false;
        //desplegarPatronLEDsJoystickDesconectado();
    }
    if(!ActuadoresConectados)
    {
        LEDActuadoresDesconectados = false;
        //desplegarPatronLEDsActuadoresDesconectados();
    }
    //Apagar y encender el LED de Joystick Desconectado
    LeerEscribirExtensorPCF(&fijarPosicionFreno, &modoCarreteraActivado, &subirPalanca, &bajarPalanca,
                            !LEDJoystickDesconectado, !LEDEncoderDesconectado, !LEDActuadoresDesconectados);

    delay(delayParoEmergencia);


}

void verificarConexionesYActualizarLEDs()
{

    //Serial.print("contadorIteraciones");
    //Serial.println(contadorIteraciones);

    // Las variables *Conectado son globales y se actualizan dentro de VerificarConexionPotenciometros().


        //La variable potenciometrosConectados define si se activa el paro de emergencia.
        potenciometrosConectados = VerificarConexionPotenciometros(cantidadPots);


        if(contadorLEDJoystickDesconectado > 0)
        {   contadorLEDJoystickDesconectado--;
        } else{
            if(JoystickConectado)
            {   LEDJoystickDesconectado = false;   }//Ver documentación en la declaración.
        }

        if(contadorLEDActuadoresDesconectados > 0)
        {   contadorLEDActuadoresDesconectados--;
        } else {
            if(ActuadoresConectados)
            {   LEDActuadoresDesconectados = false;   }
        }

        #if ENCODER_ACTIVADO
        if(contadorLEDEncoderDesconectado > 0)
        {   contadorLEDEncoderDesconectado--;
        }else{
            if(EncoderConectado)
                EncoderDesconectado = false;  //TO-DO***Verificar que se actualice aquí, no dentro de la función
                ///Dentro de la función activar EncoderConectado, EncoderDEsconectado cuando el contador llegue a 0.
        }
        #endif
    //}
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
    joystickPotVertical = true;
    joystickPotHorizontal = true;

    JoystickConectado = true;

    frenoConectado = true;
    aceleradorConectado = true;
    ActuadoresConectados = true;
    /// En caso de usar encoder en el volante, no se valida en esta función,
    /// se hace de manera automática en cada lectura.

    digitalWrite(pinRefPotsBajo, HIGH);
    digitalWrite(pinRefPotsAlto, HIGH);
    delay(1);
    // TODO: Verificar si el delay dentro de VerificarConexionPotenciometros es necesario.

    // Validar que al poner los dos extremos del potenciómetro en ALTO
    // el valor del wiper esté arriba del umbral definido.
    for(unsigned int ii = 0;   ii<cantPots;     ii++)
    {
        valorPot = analogRead(potenciometros[ii]);

        #if DEBUG_POTS
        Serial.print("\tii: "); Serial.print(ii);
        Serial.print(",\tvalorPot: "); Serial.println(valorPot);
        #endif

        //delay(1);
        // TODO: Verificar si el delay de VerificarConexionPotenciometros DENTRO DEL FOR es necesario.
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
        if(ActuadorFreno_TipoFeedback == TipoFeedback::ResistenciaVariable)
        {
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
        //delay(1);
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
        if(ActuadorFreno_TipoFeedback == TipoFeedback::ResistenciaVariable)
        {
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
        }
        else if(ActuadorFreno_TipoFeedback == TipoFeedback::EncoderIncremental)
        {
            //TODO: Implementar función para validar que el encoder del freno esté conectado.
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
    }
    else
    {
        Serial.print("Falla Pots_L: ");
        if(!JoystickConectado)
            Serial.print(" Joys_L, ");
        if(!ActuadoresConectados)
            Serial.print(" Acts_L.");
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
    /* El paro manual de emergencia se activa si se presiona el botón correspondiente.
     * El comportamiento propuesto en este caso es:
     * - Contraer el acelerador. El acelerador se contrae con valores de control negativos.
     * - Extender el freno.
*/
    Serial.println("Paro Emerg Manual.");
    setMotorSpeed_Protocol(ActuadorAcelerador_Address, -3200);

    if(ActuadoresConectados)
    {
        //Si los actuadores están conectados seguir utilizando la retroalimentación
        //para frenar el carro.
        // TODO: Buscar el valor del pot en extensión máxima.
        // TODO: Modificar el paro de emergencia para el nuevo actuador con encoder.
        int ActuadorFreno_PosDeseadaParo = actFreno_valorParoEmergencia;

        ActuadorFreno_ErrorPosicion = ActuadorFreno_Posicion - ActuadorFreno_PosDeseadaParo;
        ActuadorFreno_Control = ActuadorFreno_ErrorPosicion * ActuadorFreno_Kp;
        setMotorSpeed_Protocol(ActuadorFreno_Address, ActuadorFreno_Control);
    }
    else
    {
        //Si los actuadores están desconectados frenar el carro en lazo abierto (por tiempo)
        // *Los actuadores se extienden con valores positivos de control
        if(!protocoloFrenadoImplementado)
        {
            setMotorSpeed_Protocol(ActuadorFreno_Address, 3200);
            delay(miliSegundosActuadorFrenoParoManual);
            setMotorSpeed_Protocol(ActuadorFreno_Address, 0);
            protocoloFrenadoImplementado = true;
        }
    }

}

void ParoDeEmergencia(  )
{
    /* El paro de emergencia se activa cuando se detecta algún componente desconectado.
     *
     *
     */
    if(!mensajesEmergenciaDesplegados)
    {
        Serial.print("Paro Emerg:");
        if(LEDJoystickDesconectado)
            Serial.print("JysDscnc,");
        if(LEDActuadoresDesconectados)
            Serial.print("ActsDscnc");

    #if ENCODER_ACTIVADO
        if(EncoderConectado)
            Serial.print(", Enc:");
    #endif

        Serial.println("."); //Fin de linea de error.

        mensajesEmergenciaDesplegados = true; //Para que sólo se despliegue una vez y quede en la pantalla.
    }

    // Contraer totalmente el acelerador.
    // El acelerador se contrae con valores de control negativos.
    setMotorSpeed_Protocol(ActuadorAcelerador_Address, -3200);

    // Poner el freno en lo máximo permitido (por el coche, no por el actuador.)
    #if FRENO_ACTIVADO
    if(ActuadoresConectados)
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
        delay(miliSegundosActuadorFrenoParoManual);
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
    potenciometrosConectados = VerificarConexionPotenciometros(cantidadPots);
    //Serial.print("cantidadPots: "); Serial.print(cantidadPots);

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

    LeerEscribirExtensorPCF(&fijarPosicionFreno, &modoCarreteraActivado, &subirPalanca, &bajarPalanca,
                            !LEDJoystickDesconectado, !LEDEncoderDesconectado, !LEDActuadoresDesconectados);


    //////////////////////////////////////////////////////////////////////////////
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

/*****************************************************************************

La configuración general del sistema puede consultarse en README.md

******************************************************************************/

#include "Seguridad.hpp"
//#include "Testing.hpp"

//****************************** Variables de programa *************************//
/*int pinJoystickY = A0;
int pinJoystickX = A1;
int pinActFreno  = A2;
int pinActAcel   = A3;

int pinFijarPosicionFreno = A4;
int pinSubirPalanca = A5;
int pinBajarPalanca = 10;
int pinModoCarretera = 11;

int pinParoManualEmergencia = 9;
*/
boolean posibleFalsoCorriente = false;

//Variables para la medición del periodo del sistema.
long tiempoAnterior = 0, tiempoActual = 0;

boolean actualizacionExitosa = false;
//******************************************************************************//

void feedbackOnly();
void feedbackAndControl();
void desplegarInfoArranque();

void desplegarInfoJoystick();
void desplegarInfoBotones();
void desplegarInfoPedales();
void desplegarInfoVolante();
void desplegarInfoPalanca(int joystick_Y);
void verificarModoCarretera();

void verificacionSeguridad_Periodica();
void verificacionSeguridad_Constante();



//void pullupsInternos_i2c(boolean habilitar);
//void puestaACeroEncoder();

void configurarPines()
{
    analogReference(DEFAULT);
    //DEFAULT: the default analog reference of 5 volts (on 5V Arduino boards) or 3.3 volts (on 3.3V Arduino boards)
    //EXTERNAL: the voltage applied to the AREF pin (0 to 5V only).

    pinMode(pinParoManualEmergencia, INPUT_PULLUP); //Configurar el pin por defecto en alto.

    pinMode(pin5VVirtual, OUTPUT);
    pinMode(pinGNDVirtual, OUTPUT);

    pinMode(pinOutput_PalancaBajar, OUTPUT);
    pinMode(pinOutput_PalancaSubir, OUTPUT);

    pinMode(pinFijarPosicionFreno, INPUT);
    pinMode(pinSubirPalanca, INPUT);
    pinMode(pinBajarPalanca, INPUT);
    pinMode(pinModoCarretera, INPUT);

    digitalWrite(pinOutput_PalancaBajar, LOW);
    digitalWrite(pinOutput_PalancaSubir, LOW);

    //pinMode(pin_encendido, INPUT_PULLUP); //Por defecto en alto
}


void setup()
{
    /// TODO: Portar a ST NUCLEO?.

    //Serial.begin(38400);
    Serial.begin(115200);
    Serial.println("Comunicación Serial Iniciada.");

    /// TODO: Investigar si menor velocidad Serial es menos exigente para el micro.

    configurarPines();

    // Encender todos los LEDS del Joystick para indicar que está encendido.

    verificacionPots_activarVoltajeVirtual();

    // Para llenar el arreglo que se utiliza para filtrar la señal y evitar el
    // movimiento brusco de los actuadores al arranque.
    for(int ii = 0; ii < filterSamples + 1; ii++)
    {
        Leer_Joystick();
        Leer_Feedback();
    }

    // Verificación de seguridad al arranque. Si alguna no pasa NO activar el sistema.
    errorConexionesArranque = verificacionSeguridadArranque();
    if(errorConexionesArranque)
    {
        Serial.println("**Se detectaron errores durante el arranque.**");
        //Serial.println("**Por seguridad el sistema NO se activará.**");
    }

    // ***Seleccionar el modo de operación del volante.***********
    #if VOLANTE_ACTIVADO           // Definido en Seguridad.hpp
        volante_Desinhibir();
    #endif

    //smcSerial.begin(19200);
    smcSerial.begin(9600); // Se probó con 19200 y funciona.

/*#if DEBUG_BOOT
    delay(1000);
#endif*/
    tiempoAnterior = millis();

    desplegarInfoArranque();
}

void loop()
{
    tiempoActual = millis();
    if ( (tiempoActual - tiempoAnterior) >= periodoDeseado )
    {
        NoParoManualEmergencia = digitalRead(pinParoManualEmergencia); // Normalmente alto.

        if(NoParoManualEmergencia)
        {
        #if ENCODER_ACTIVADO
            if( !EncoderConectado || errorConexionesArranque)  {
                AlertaDeEmergencia();
            }
            else
        #else
            /*if(errorConexionesArranque)*/
        #endif
            /*{
                aplicarRutinasSeguridad(); //Aquí se siguen leyendo los sensores, en caso de que se reconecten.

                feedbackOnly();
            }
            else*/
            {
                if(!Potenciometros_Conectados || !Potenciometros_EnRangoValido)
                //if(!Potenciometros_Conectados)
                {
                     aplicarRutinasSeguridad(); //Aquí se siguen leyendo los sensores, en caso de que se reconecten.
                     feedbackOnly();
                }
                else
                {
                    feedbackAndControl();
                }
            }
        }
        else {
            ParoManualEmergencia();
        }

    #if INFO_TIME
        long diferencia = tiempoActual - tiempoAnterior;
        Serial.print(",\tT:"); Serial.print(diferencia);
    #endif

        Serial.println(" ");
        tiempoAnterior = tiempoActual;
    }
}


/*! Operación normal del sistema: Leer feedback de los sensores y aplicar control.
 * Si no hay paro de emergencia y todos los componentes están conectados.
 *************************************************/
void feedbackAndControl()
{
    mensajesEmergenciaDesplegados = false;

#if PCF_ACTIVADO
   ExtensorPCF_LeerEscribir();
   verificarModoCarretera();
#endif
    volante_Desinhibir();

    Leer_Joystick();
    Leer_Feedback();
    desplegarInfoJoystick();

    Leer_Botones();
    desplegarInfoBotones();
    verificarModoCarretera();

    // ***************************** //
    ControlarPedales(Joystick_Y, fijarPosicionFreno, ControlPedales_comportamientoDirecto);
    desplegarInfoPedales();

    ControlarVolante();
    desplegarInfoVolante();

    ControlPalanca(ActuadorFreno_Posicion);
    desplegarInfoPalanca(Joystick_Y);
    // ***************************** //

    //verificacionSeguridad_Constante();
    verificacionSeguridad_Periodica();
}

/*! Se ejecuta si hay errores en el arranque.
 * \n No aplica control, sólo lee los sensores y botones y envía los valores por Serial.  */
void feedbackOnly()
{
    Leer_Joystick();
    desplegarInfoJoystick();

    Leer_Feedback();
    desplegarInfoPedales();

    Leer_Botones();
    desplegarInfoBotones();

    desplegarInfoVolante();
}


void verificacionSeguridad_Periodica()
{
    contadorIteraciones++;
    if(contadorIteraciones >= cantIteracionesParaVerificacion)
    {
        Potenciometros_Conectados = VerificarConexionPotenciometros(cantidadPots);
        //aplicarRutinasSeguridad();
        contadorIteraciones = 0;
    }
}

void verificacionSeguridad_Constante()
{

    Potenciometros_EnRangoValido = validarLimites_Potenciometros();
}

void verificarModoCarretera()
{
    if(modoCarreteraActivado == 1)
    {
        ActuadorAcelerador_valorExtendido = ACELERADOR_MAPEO_COMPLETO;
    }
    else
    {
        ActuadorAcelerador_valorExtendido = ACELERADOR_MAPEO_MEDIO;
    }
}


void desplegarInfoArranque()
{
#if FRENO_ACTIVADO //Usar ! para negar la constante no funciona como con una variable normal.
    Serial.println("El freno está activado.");
    Serial.print("Modo operación pedales: ");
    if(ControlPedales_comportamientoDirecto)
    {
        Serial.println("Directo. ");
    }
    else
    {
        Serial.println("Inverso. ");
    }
#else
    Serial.println("**¡EL FRENO NO ESTÁ ACTIVADO!**");
#endif

#if ACELERADOR_ACTIVADO
    Serial.println("El Acelerador está activado.");
#else
    Serial.println("**¡EL ACELERADOR NO ESTÁ ACTIVADO!**");
#endif

#if DEBUG_CONTROL_VOLANTE_UMBRALES
    //Serial.print("JoyIzq_Medio: "); Serial.println(joyIzquierdaMedio);
    //Serial.print("JoyDer_Medio: "); Serial.println(joyDerechaMedio);

    //Serial.print("JoyIzq_2/3: "); Serial.println(joyIzqDosTer);
    //Serial.print("JoyDer_2/3: "); Serial.println(joyDerDosTer);


    Serial.println("Corroborando valores de control por segmentos para Joystick y Actuación del volante");
    Serial.print("porcentControlPuente_Seg1:  ");
    Serial.println(porcentControlPuente_Seg1);//Segmento1
    Serial.print("ControlVolante_IzqSeg1: ");
    Serial.println(ControlVolante_IzqSeg1);
    Serial.print("ControlVolante_DerSeg1");
    Serial.println(ControlVolante_DerSeg1);

    Serial.print("joy_percentSegmento1: ");
    Serial.println(joy_percentSegmento1);
    Serial.print("joyIzq_Segmento1: ");
    Serial.println(joyIzq_Segmento1);
    Serial.print("joyDer_Segmento1: ");
    Serial.println(joyDer_Segmento1);
    delay(2000);
#endif

    Serial.print("**Periodo verificación: "); Serial.println(periodoVerificacion);
    Serial.print("**Cantidad de iteraciones para verificación: "); Serial.println(cantIteracionesParaVerificacion);
}
void desplegarInfoJoystick()
{
#if INFO_JOYSTICK
    Serial.print("J_Y: ");  Serial.print(Joystick_Y);
    Serial.print(",\tJ_X: "); Serial.print(Joystick_X);
#endif

}
void desplegarInfoBotones()
{
#if INFO_BOTONES
    Serial.print(",\tbFB: "); Serial.print(fijarPosicionFreno); //button Fix Brake
    Serial.print(", bPU: "); Serial.print(subirPalanca); // button Palanca Up
    Serial.print(", bPD: "); Serial.print(bajarPalanca);// button Palanca Down
    Serial.print(", bMC: "); Serial.print(modoCarreteraActivado); //button Modo Carretera
#endif
}

void desplegarInfoPedales()
{
#if INFO_ACTUADORES_POS
    // Brake information
    Serial.print(",\tB_p: "); Serial.print(ActuadorFreno_Posicion);
    Serial.print(",   B_t: ");     Serial.print(ActuadorFreno_PosDeseada); //Serial.print(")");

    #if INFO_ACTUADORES_CONTROL
        Serial.print(",   B_e: "); Serial.print(ActuadorFreno_ErrorPosicion); //posDeseada - posActual
        Serial.print(",   B_c: "); Serial.print(ActuadorFreno_Control);
    #endif

    // Gas information
    Serial.print(",\tA_p: "); Serial.print(ActuadorAcelerador_Posicion); //Valor del pot del act2 (Acelerador)
    Serial.print(",   A_t: "); Serial.print(ActuadorAcelerador_PosDeseada); //Serial.print(")");

    #if INFO_ACTUADORES_CONTROL
        Serial.print(",   A_e: "); Serial.print(ActuadorAcelerador_ErrorPosicion);
        Serial.print(",   A_c: "); Serial.print(ActuadorAcelerador_Control); //Valor de control aplicado al actuador de acelerador.
    #endif

#endif
}
void desplegarInfoVolante()
{
    #if INFO_VOLANTE
    Serial.print(",\tCtrl_Vol: "); Serial.print(velocidad_volante);
    //Serial.print(valorControlVolante); //Esta activarla con el modo exponencial.
    #endif
}


void desplegarInfoPalanca(int joystick_Y)
{

}


void puestaACeroEncoder()
{
    #if ENCODER_ACTIVADO
    /* Debido a que en la puesta a cero la posición se interpreta como 360°, además
    el setPoint son 180° así que debe seguirse un procedimiento específico.


    1. Encienda el sistema con la bandera PUESTACERO en 1 (verdadero).

        2. Coloque el volante en el origen deseado.

        3. Gire el volante a la izquierda hasta que el encoder indique 180°.

        4. Vuelva a configurar el encoder a 0°.

        5. Devuelva la bandera PUESTAACERO a 0 (falso).
    */


    //posicion_volante_actual = PosMotorDeg_actual / relacionSprockets;

    //2.
    Serial.println("Coloque el volante en el origen deseado, una vez colocado mueva el joystick hacia enfrente.");
    Leer_JoystickActuadores();
    while(smoothJS_Y < joyForward_minVal + 90) //Mientras el joystick no se mueva hacia enfrente.
    {
      Leer_JoystickActuadores();
      //LeerConvertirEncoder();
      Serial.print("Jy:"); Serial.print(smoothJS_Y);
      Serial.print(", Jx:"); Serial.print(smoothJS_X);

      //ABSposition = LeerEncoder(&EncoderConectado);
      LeerConvertirEncoder(&LEDEncoderDesconectado);
      ControlarVolante();

      Serial.print(". PosActEnc: ");
      Serial.print(PosMotorDeg_actual);
      Serial.println(". Lleve el volante al origen deseado, después mueva el joystick al frente.");
      delay(2);
    }

    //Se ha movido el joystick hacia enfrente.
    Serial.println("Poniendo encoder a cero. Libere el joystick y espere 5s.");

    delay(5000);
    actualizacionExitosa = ponerACero();

    if(actualizacionExitosa)
    {
      Serial.println("Encoder puesto a cero.");

      Serial.println("Libere el joystick, después espere 3s.");
      delay(3000);
      //Debido a que al poner en cero el encoder el programa lo interpreta como 360° (verificar)
      //la ejecución se detendrá hasta que el usuario mueva el joystick por arriba de 600 (hacia enfrente)
      //  5° = 0.439453125
      // 10° = 0.87890625

      //3.
      //"Coloque el encoder entre 175 y 185 grados; manténgalo ahí y mueva el joystick hacia enfrente."
      for(int ii=0; ii< 200; ii++) //200 Arbitrario
      {
        Leer_JoystickActuadores();
        delay(5);
      }

      while(smoothJS_Y < (joyForward_minVal + 90)) //Mientras el joystick no se mueva hacia enfrente.
      {
        Leer_JoystickActuadores();

        Serial.print("Jy:"); Serial.print(smoothJS_Y);
        Serial.print("Jx:"); Serial.print(smoothJS_X);

        LeerConvertirEncoder(&LEDEncoderDesconectado);
        ControlarVolante();

        Serial.print(". PosActualEnc: ");
        Serial.print(PosMotorDeg_actual);

        Serial.print(". Vts: ");        Serial.print(vueltas);
        Serial.println(". Lleve el encoder a ~180 grados; manténgalo ahí y mueva el joystick al frente. WRN: Joystick centrado.");
        //Serial.println()
        //LeerConvertirEncoder(); //No funciona con esta función porque hace el cálculo de vueltas.
        delay(1);
      }

      Serial.println("Seteando el encoder nuevamente en 0.");
      Serial.println("5 segundos...");

      delay(5000);

      actualizacionExitosa = ponerACero();


      if(actualizacionExitosa)
      {
        Serial.println("Encoder puesto a cero. El proceso de calibración ha sido exitoso.");

        Serial.println("Mueva el volante al origen y asegúrese que el encoder indica ~180°.");
        Serial.println("Despues reinicie el sistema con la bandera PUESTACERO en 0.");
        Serial.println("Espere 10s para ver las lecturas del encoder.");
        delay(10000);

        while(1)
        {
          ABSposition_last = LeerEncoder(&EncoderConectado);
          AbsPosLastDeg = ABSposition_last*factorGradosPulsos;

          Serial.print(". Posicion actual encoder: "); Serial.print(AbsPosLastDeg);
          Serial.print(". Vts: ");        Serial.print(vueltas);
          Serial.println(". Reinicie ahora el sistema.");

          //LeerConvertirEncoder(); //No funciona con esta función porque hace el cálculo de vueltas.
          delay(1);
        }
      }
      else
      {
          Serial.println("El encoder tardó demasiado en responder en la segunda puesta a cero.");
          Serial.println("5 segundos...");
          delay(5000);
      }
    }
    else
    {
        Serial.println("El encoder tardó demasiado en responder en la segunda puesta a cero.");
        Serial.println("5 segundos...");
        delay(5000);
    }
#endif
}


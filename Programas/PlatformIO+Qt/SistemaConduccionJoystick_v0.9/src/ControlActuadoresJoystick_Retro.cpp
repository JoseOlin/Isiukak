/*****************************************************************************
La configuración general del sistema puede consultarse en
../../Actuadores pedales y dirección/Diagramas y configuración general

act1: Freno.           0x0D
act2: Acelerador.      0x0A

act3: Volante.         0x04  (0000 0100)


Documentacion cableado
Pines analógicos:
A0: Joystick eje Y. Incremento acelera, decremento frena.
A1: Josytick eje X (Volante)
A2: Pot actuador 1 (Freno)
A3: Pot actuador 2 (Accel)

A4: (Disponible)
A5: INPUT. Para definir si el auto está encendido o no (Cuando el auto se apague se guarda la posición del volante).

Pines digitales:
13: SPI SCK   -> 5 encoder
12: SPI MISO  -> 3 encoder
11: SPI MOSI  <- 7 encoder
10: SPI CS    -> 2 encoder

9: Pin Paro de emergencia manual.
8: Tx hacia los puentes (comunicación serial).
7: Rx hacia los puentes (comunicación serial). *** TO-DO ***: Implementar lectura de status.

6: LED de seguridad. Posible falso en la corriente.
5: (Disponible)
4: (Disponible)
//La razón por la que no se usan estos pines para desplegar LEDs de seguridad
                //es que el PCF ya está  en el joystick y sólo requiere 3 cables (i2c)
                //Sin embargo sería conveniente tener los LEDs de Seguridad en otra placa
                // Completamente visible en el tablero.

3: Referencia para Validación potenciómetros, alto.
2: Referencia para Validación potenciómetros, bajo.

1: Serial
0: Serial

Extensor PCF (Nota: Asegurarse que el PCF tome voltaje de +5V no de las salidas
digitales que se usan para verificar el comportamiento de los potenciómetros.)
Entradas:
    P0: Botón de bloqueo de posición del freno (en caso de que se requiera frenar y acelerar al mismo tiempo).
    P1: Switch de mapeo completo de acelerador (para el modo carretera, también usarla para hacer el volante menos sensible en carretera).
    P2: (Disponible)
    P3: (Disponible)

Salidas: Códigos de Error e información en los LED del controller
    1 (P4): LED de información. Mapeo completo del volante.
    2 (P5): LED de seguridad. Actuadores desconectados.
    3 (P6): LED de seguridad. Joystick desconectado o posible falso.
    4 (P7): LED de seguridad. Encoder desconectado.



LEDs Joystick
        ^
        |
        |
    <------->
        |
        |
        v
L1  L2  L3  L4
******************************************************************************/

#include "Seguridad.hpp"

//*** Variables de programa********************************
int pinJoystickY = A0;
int pinJoystickX = A1;
int pinActFreno  = A2;
int pinActAcel   = A3;

unsigned int pin_encendido = A5;
int pinParoManualEmergencia = 9;

int posibleFalsoCorriente = 0; //Bandera.

//Variables para la medición del periodo del sistema
long tiempoAnterior = 0, tiempoActual = 0;

boolean actualizacionExitosa = false;
//**********************************************************
void puestaACeroEncoder();


void setup()
{
    //Inicializar la comunicación i2c (para usar el extensor PCF).
    /// TODO: Portar a Arduino MEGA !!!
    Wire.begin();

    //Serial.begin(19200);
    Serial.begin(115200);
    Serial.println("Com Serial Iniciada.");

    //smcSerial.begin(19200);
    smcSerial.begin(9600); //Se probo con 19200 y funciona. Investigar si menor velocidad es menos exigente para el micro.

    analogReference(DEFAULT); //the default analog reference of 5 volts (on 5V Arduino boards) or 3.3 volts (on 3.3V Arduino boards).

    //pinMode(A0, INPUT);
    //digitalWrite(A0, LOW); //Deshabilitar la resistencia pull up

    pinMode(pin_encendido, INPUT_PULLUP); //Por defecto en alto
    pinMode(pinParoManualEmergencia, INPUT_PULLUP); //Configurar el pin por defecto en alto.
    pinMode(pinRefPotsAlto, OUTPUT);
    pinMode(pinRefPotsBajo, OUTPUT);

    //La lectura de los potenciómetros se realiza primero, ya que si el encoder se
    //pone a cero, se puede utilizar el joystick para confirmar que el volante ya se ha movido
    //ligeramente a la derecha (Vea INFO de ControlVolante para más detalles.)

    //Verificación de seguridad al arranque. Si alguna no pasa NO activar el sistema.
    errorConexionesArranque = verificacionSeguridadArranque();

    //Para llenar el arreglo que se utiliza para filtrar la señal y evitar el
    //movimiento brusco de los actuadores al arranque.
    for(int ii=0; ii< filterSamples; ii++)
    {
        Leer_JoystickActuadores();
    }

    //ActuadorFreno = TipoFeedback::Encoder;
    ActuadorFreno = TipoFeedback::ResistenciaVariable;


    //***Seleccionar el modo de operación del volante.***********
    #if VOLANTE_ACTIVADO           //Definido en Seguridad.hpp
        //tipoC = MODO_POSICION_LIN;
        //tipoC = MODO_POSICION_LOG;
        //tipoC =  MODO_VELOCIDAD; //Modo de control del volante con retroalimentación del encoder.
        //tipoC = MODO_VELOCIDAD_OPENLOOP; //Modo de control por velocidad sin retroalimentación del encoder.
        tipoC = MODO_OPENLOOP_PORPARTES;
    #endif


    tiempoAnterior = millis();

#if FRENO_ACTIVADO //Usar ! para negar la constante no funciona como con una variable normal.
    Serial.println("El freno está activado.");
#else
    Serial.println("¡EL FRENO NO ESTÁ ACTIVADO!.");
    delay(1500);
#endif
#if ACELERADOR_ACTIVADO
    Serial.println("El Acelerador está activado.");
#else
    Serial.println("¡EL ACELERADOR NO ESTÁ ACTIVADO!.");
    delay(1500);
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

    Serial.print("Periodo verificación: "); Serial.println(periodoVerificacion);
    Serial.print("Cantidad de iteraciones para verificación: "); Serial.println(cantIteracionesParaVerificacion);

    Serial.flush();

    delay(1500);

    #if DEBUG_JOYSTICK
    delay(1000);
    #endif
}


void loop()
{
    //NoParoManualEmergencia = digitalRead(pinParoManualEmergencia); //Normalmente alto.

    //if(EncoderConectado && JoystickConectado && ActuadoresConectados)


    if(NoParoManualEmergencia)
    {
    #if ENCODER_ACTIVADO
        if( !EncoderConectado || !potenciometrosConectados)
        {
            ParoDeEmergencia();
        }
        else
    #else
        if(errorConexionesArranque)
        {
            desplegarPatronErrores();
            //delay(delayParoEmergencia); Se hace el delay dentro de la función, pues
            // se requiere que la mitad del periodo los LEDs estén encendidos y mitad apagados.
        }
        else
        {
            if(!potenciometrosConectados) //Si alguno de los componentes se desconectó.
            {
                ParoDeEmergencia(); //Aquí se siguen leyendo los sensores, en caso de que se reconecten.

                delay(delayParoEmergencia);

            }
            else
	#endif
            {
                tiempoActual = millis();

                Leer_JoystickActuadores();
                mensajesEmergenciaDesplegados = false;

                if( (tiempoActual - tiempoAnterior) >= periodoDeseado )
                {
                    LeerEscribirExtensorPCF(&modoBloqueoFreno, &modoCarreteraActivado, &entradaPCF3, &entradaPCF4,
                                            !LEDJoystickDesconectado, !LEDEncoderDesconectado, !LEDActuadoresDesconectados);
                                            //Se usan las variables _Desconectado porque esas quedan encendidas durante algunos ciclos (6).
                #if DEBUG_EXTENSOR
                    Serial.print(", BlkFreno: "); Serial.print(bloqueoFrenoActivado);
                    Serial.print(", ModoCarr:"); Serial.print(modoCarreteraActivado);
                #endif


                #if ENCODER_ACTIVADO
                    LeerConvertirEncoder(&EncoderDesconectado); //Aquí mismo se valida si el encoder está conectado.
                    //Cuando el auto se estacione y apague, guardar la posición del volante.
                    //guardarVueltas(pin_encendido);
                #endif

                #if DEBUG_JOYSTICK
                    //Serial.print(", Jy:");  Serial.print(smoothJS_Y);
                    //Serial.print(",\tJx:"); Serial.print(smoothJS_X);
                #endif
                    //*****************************//
                    ControlarPedales();
                    //*****************************//

                #if DEBUG_ACTUADORES_POS
                    Serial.print(", F_p(a:"); Serial.print(smoothAct1); //Valor del potenciometro del act1 (Freno)
                    Serial.print(", d:"); Serial.print(freno_posDeseada); //Valor deseado para el pot del freno.
                    Serial.print(")");

                    #if ACELERADOR_ACTIVADO
                        Serial.print(", A_p(a:"); Serial.print(smoothAct2); //Valor del pot del act2 (Acelerador)
                        Serial.print(", d:"); Serial.print(acel_posDeseada); Serial.print(")");
                    #endif
                #endif

                #if DEBUG_ACTUADORES_CONTROL
                    Serial.print(", F_er:"); Serial.print(error_freno); //valor - posDeseada
                    Serial.print(", F_ct:"); Serial.print(controlFreno); //Valor de control aplicado al actuador de freno

                    #if ACELERADOR_ACTIVADO
                        Serial.print(", A_er:"); Serial.print(error_acel);
                        Serial.print(", A_ct:"); Serial.print(controlAcel); //Valor de control aplicado al actuador de acelerador.
                    #endif
                #endif

                #if VOLANTE_ACTIVADO
                    //*****************************//
                    ControlarVolante();
                    //*****************************//
                #endif


                #if DEBUG_TIME
                    Serial.print(", t:");
                    long diferencia = tiempoActual - tiempoAnterior;
                    Serial.println(diferencia);
                #endif

                    contadorIteraciones++;
                    if(contadorIteraciones >= cantIteracionesParaVerificacion) //Definida en las variables de config en Seguridad.hpp.
                    {

                        verificarConexionesYActualizarLEDs();

                        #if DEBUG_JOYSTICK
                        Serial.print(", Jy:");  Serial.print(smoothJS_Y);
                        Serial.print(",\tJx:"); Serial.print(smoothJS_X);
                        #endif
                        //Serial.println("");
                        
                        #if DEBUG_VOLANTE
						Serial.print(",\t Ctrl. volante: ");
						Serial.print(velocidad_volante);
						//Serial.print(valorControlVolante); //Esta activarla con el modo exponencial.
						#endif

                    }
					/// TODO: Revisar si es millis o tiempoActual
                    tiempoAnterior = tiempoActual;
                }
            } //endif(EncoderConectado && potenciometrosConectados)
        }//endif(errorConexionesArranque)
    }//endif(NoParoManualEmergencia)
    else
    {
        ParoManualEmergencia();
    }
}

#if ENCODER_ACTIVADO
void puestaACeroEncoder()
{
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
}
#endif

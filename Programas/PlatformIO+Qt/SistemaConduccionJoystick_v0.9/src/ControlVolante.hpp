#ifndef CONTROLVOLANTE
#define CONTROLVOLANTE

//*********Variables y librerias para control de direccion
/* En esta sección están las variables y funciones para controlar el volante.

*INFO: Hay un problema con la interpretación de la lectura del encoder cuando se da
una vuelta completa. Por ejemplo, si el encoder queda en -5°, la siguiente vez
que inicie lo interpretará como 355° y dará casi una vuelta entera para llevarla a 0°

Una opción es almacenar el valor de las vueltas en la EEPROM, pero debe almacenarse
cada que se apaga el automóvil, y no es tan necesario ya que al final el joystick siempre
queda centrado, por lo que (probablemente) será suficiente con guardar la cantidad
de vueltas en tiempo de ejecución y dar por hecho que al final quedará muy cerca del origen.

Esto sigue representando un problema, ya que como se mencionó, un pequeño desfase negativo
se interpreta como un gran desgase positivo en el reinicio (-5 = 355), lo cual puede
corregirse almacenando el valor de las vueltas pero es recomendable minimizar este almacenamiento.

Hacerlo al apagado del auto implica agregar una señal digital que detecte tal situación.
Hacerlo cada que se detecte una vuelta generaría muchos accesos a la EEPROM ya que el encoder está centrado
en 0° y las transiciones de valores pequeños negativos a valores pequeños positivos son usuales.

Para resolver el problema se tomarán 180° del encoder como la posición inicial.

*/

//#include "Debug.hpp"

#if ENCODER_ACTIVADO
    #include <EEPROM.h> //Para almacenar valores en memoria no volatil.
    #include "LecturaEncoder.hpp" //->//#include "Seguridad.hpp"
#endif
#include "DigitalFilter.hpp"
#include "ControlPedales.hpp" //->//#include "LecturaJoystick.hpp"
                              //->//#include "DriversMotores.hpp"


//*****************************Variables configuración**************************


int controlVolanteMaximo = 3200;
//int controlVolanteMaximo = 2400;


//El volante puede girar una vuelta y 3/4 aproximadamente hacia izquierda y derecha.
//Su centro es en: 0 vueltas, 0°. 360+270 = 630. Sin embargo eso debe ser
//convertido al angulo del encoder.
//Cálculo de la relación entre las vueltas del volante y las vueltas del motor.
int dientesEje = 13;   //El sprocket del volante tiene 13 dientes.
int dientesMotor = 10; //El sprocket del motor tiene 10 dientes.
float relacionSprockets = (float)dientesEje / dientesMotor;

float setPointGrados = 180.0 / relacionSprockets;
//float ajusteGrados180 = 0.0;
/////**TO-DO: Implementar control de velocidad.
// Para limitar el valor máximo de control aplicado y evitar giros bruscos.
// El máximo es 3,200, probar con 3/4 del máximo.

//Rango de giro del volante a izquierda y derecha.
//El máximo aproximado es 1 y 3/4 de vuelta (360 + 270 = 630), pero se redujo ligeramente para evitar
//llevarla al límite.
int gradosVolanteIzq = -610 + setPointGrados;
int gradosVolanteDer = 610 + setPointGrados;
int anguloSeguridadVueltaIzq = 50 ;
int anguloSeguridadVueltaDer = 50;

//Para una vuelta de 90° el giro del volante es de menos de 3/4 de vuelta (algo más de media vuelta),
//así que la mayor parte del rango del joystick puede mapearse a este rango de giro del volante.
int gradosVolanteIzq_VueltaAngRecto = -210  +  setPointGrados;
int gradosVolanteDer_VueltaAngRecto =  210  +  setPointGrados;

//En carretera el giro máximo es de menos de 180°, probablemente sea conveniente un MODO_CARRETERA.
int gradosVolanteIzq_Carretera = -90 + setPointGrados;
int gradosVolanteDer_Carretera =  90 + setPointGrados;


float umbralErrorPosDireccion = 1; //Valor mínimo de error para aplicar control. (Si es menor se aplica control 0)

int umbral_error_encoder = 5; //Valor mínimo de error en la posicion del encoder
//**************************Fin Variables configuración*************************//

//*****************************Variables del programa**************************


float errorPosDireccion = 0;
int8_t vueltas = 0;
//boolean primeraVueltaIzq = true;

//boolean vueltasGuardadas = false; //Para saber si en esta sesion el numero de vueltas ya fue almacenado y no volver a guardar.

enum tiposConduccion {  MODO_POSICION_LINEAL,       //Relación lineal entre la posición del joystick y la posición del volante.
                        MODO_POSICION_LOGARITMICO,       //Relación logarítmica entre posición del joystick y la posición del volante (menos sensible al centro).
                        MODO_VELOCIDAD_CLOSEDLOOP,  //Controla la velocidad de giro en función de la posición del joystick (Relación lineal, con retroalimentación).
                        MODO_OPENLOOP_LINEAL, //Relación lineal entre la posición del joystick y el voltaje aplicado al motor del volante.
                        MODO_OPENLOOP_PORPARTES, //Dos segmentos, Menos sensible al centro, más sensible al extremo.
                        MODO_OPENLOOP_EXPONENCIAL
                     };
tiposConduccion tipoC;

float posVolante_actual;
float posVolante_deseada;
float PosMotorDeg_actual = 0.0; //Posicion del motor en grados
float PosMotorDeg_deseada;
int velocidad_volante = 0;
int valorControlVolante;

boolean EncoderConectado = true;
uint8_t contadorLEDEncoderDesconectado = 0;


uint8_t entradaPCF3;
uint8_t entradaPCF4;


float porcentControlPuente_Seg1 = 0.125;
int ControlVolante_IzqSeg1 = (float)valorMaximoControlPuente * porcentControlPuente_Seg1;
int ControlVolante_DerSeg1 = -ControlVolante_IzqSeg1;

int controlMaximoIzq = 3200;
int controlMaximoDer = -3200;

//Variables de ajuste del comportamiento del mapeo Joystick-ControlVolante.
float ajusteExpCiudad_L = 28.05;   //Sensibilidad media para la ciudad.
float ajusteExpCiudad_R = 29.45;
float ajusteEscalar_Ciudad = 40.0;

float ajusteExpCarretera_L = 19.05;  //Menos sensible al joystick en la carretera .
float ajusteExpCarretera_R = 20.05;
float ajusteEscalar_Carretera = 5;
//*************************Fin Variables del programa**************************//

//**************Prototipos*******************//
int ControlPosicionVolante(float posicionMotorDeseada, float posicionMotorActual, float* errorMotorDireccion, int controlMaximo);
//**************Fin Prototipos*******************//
void InicializarEncoder()
{
#if ENCODER_ACTIVADO
    //**Inicializacion Comunicacion Encoder (SPI)*****************
    pinMode(CS, OUTPUT);//Slave Select
    digitalWrite(CS, HIGH);

    //Serial.println("Antes SPI");
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV32);
    SPI.end();
    //***Fin Inicializacion Comunicacion Encoder (SPI)****************


    //Cargar valor de cantidad de vueltas.
    //EEPROM.write(0, 0);

    //vueltas = EEPROM.read(0); //Leer el byte de la direccion 0 en la EEPROM
    vueltas = 0;  ////**********************************///**********************///*****************
    Serial.print("vts: ");
    Serial.println(vueltas);
    #if PUESTACERO //Definida en Debug.hpp
    puestaACeroEncoder();
    #endif

    //Para evitar que en la primer lectura la diferencia sea grande e interprete eso como una vuelta.
    ABSposition_last = LeerEncoder(&EncoderConectado);
    AbsPosLastDeg = ABSposition_last*factorGradosPulsos;

    if(!EncoderConectado)
        Serial.println("Encoder desconectado");

    LeerConvertirEncoder();
#endif
}

#if ENCODER_ACTIVADO
void LeerConvertirEncoder(uint8_t* EncoderDesconectado)
{
  //Lectura de encoder
  ABSposition = LeerEncoder(&EncoderConectado);
  //AbsPosDeg = ABSposition*factor;

  //if(ABSposition != ABSposition_last)    //if nothing has changed dont wast time sending position
  if(EncoderConectado) //Sólo actualizar la posición del encoder si está conectado, de otra forma mantener la anterior.
  {
    int diferenciaPulsos_Encoder = ABSposition_last - ABSposition;

    //Si hay un salto abrupto en la posicion; ejemplo de 360 a 0° (maximo de 340 a 20°).
    if(  diferenciaPulsos_Encoder >  3640 )//340°=3,868p. 320°=3,640p. Condiciones invertidas para incrementar en sentido horario.
    { //Está girando hacia la izquierda.
      vueltas--;
      //Serial.println("Vlt izq.");
    }
    if(  diferenciaPulsos_Encoder < -3640 ) //Está girando hacia la derecha.
    {
      vueltas++;
      //Serial.println("Vlt der.");
    }


    ABSposition_last = ABSposition;    //set last position to current position
    PosMotorPulsos = (float)ABSposition;
    float PosMotorPulsos_temp = (float)pulsosPorVuelta - PosMotorPulsos; //Ajuste para que al mover
                                        //en sentido horario el valor incremente.

    ////////////////////// ***** Esta línea es la responsable de que la puesta a cero del encoder se interprete como 360°
    PosMotorDeg_actual = PosMotorPulsos_temp*factorGradosPulsos   +    vueltas*360   ;    //
    //PosMotorDeg += ajusteGrados180;

    //PosMotorPulsos = ABSposition;
    //Serial.print("Dif:");
    //Serial.print(diferencia);
  }
  else
  {
      *EncoderDesconectado = true;
      contadorLEDEncoderDesconectado = 6;
  }

}
#endif

void ControlarVolante()
{
    //int velocidad_volante = 0;

#if ENCODER_ACTIVADO
  posVolante_actual = PosMotorDeg_actual / relacionSprockets;
#endif

    if(tipoC == MODO_OPENLOOP_PORPARTES)
    {
        int umbralLecturaIzq = joyDirectionCenter-umbral_lectura_joystick;
        int umbralLecturaDer = joyDirectionCenter+umbral_lectura_joystick;
        if( smoothJS_X < umbralLecturaIzq || smoothJS_X > umbralLecturaDer)
        {
            if( smoothJS_X < umbralLecturaIzq && smoothJS_X >= joyIzq_Segmento1){
                velocidad_volante = map(smoothJS_X,
                                        joyDirectionCenter, joyIzq_Segmento1,
                                        0,              ControlVolante_IzqSeg1);
            }
            else if(smoothJS_X < joyIzq_Segmento1) {
                velocidad_volante = map(smoothJS_X,
                                        joyIzq_Segmento1,       joyMaximoIzquierda,
                                        ControlVolante_IzqSeg1, controlMaximoIzq);
            }
            else if (smoothJS_X > umbralLecturaDer && smoothJS_X <= joyDer_Segmento1){
                velocidad_volante = map(smoothJS_X,
                                        joyDirectionCenter, joyDer_Segmento1,
                                        0,                  ControlVolante_DerSeg1);
            }
            else if(smoothJS_X > joyDer_Segmento1){
                velocidad_volante = map(smoothJS_X,
                                        joyDer_Segmento1,   joyMaximoDerecha,
                                        ControlVolante_DerSeg1, controlMaximoDer);
            }
            //velocidad_volante = map(smoothJS_X, joyMaximoIzquierda, joyMaximoDerecha, 3200, -3200);  //Invertido porque el motor se mueve a la izquierda con joystick a la derecha.

            setMotorSpeed_Protocol(volnAddress, velocidad_volante);
        }
        else
        {
            velocidad_volante = 0;
            setMotorSpeed_Protocol(volnAddress, velocidad_volante);
        }
    }
    else if(tipoC == MODO_OPENLOOP_EXPONENCIAL)
    {
        //int umbralLecturaIzq = joyDirectionCenter-umbral_lectura_joystick;
        //int umbralLecturaDer = joyDirectionCenter+umbral_lectura_joystick;

        double x_Centrado = smoothJS_X - joyDirectionCenter; //Valor de X centrado en 0.
        double x_Escalado;

        //Variables para ajustar la forma de la curva.
        int ajusteExp;
        int signo;
        int ajusteEscalar;

        if( abs(x_Centrado) > umbral_lectura_joystick)
        {
            if( x_Centrado < joyDirectionCenter){ //Girar hacia la izquierda
                signo = -1;
                if(modoCarreteraActivado) {
                    ajusteExp = ajusteExpCarretera_L;
                    ajusteEscalar = ajusteEscalar_Carretera;
                }
                else {//modoCiudadActivado
                    ajusteExp = ajusteExpCiudad_L;
                    ajusteEscalar = ajusteEscalar_Ciudad;
                }
            }
            else if (smoothJS_X > joyDirectionCenter){ //Girar hacia la derecha.
                signo = 1;
                if(modoCarreteraActivado)
                {
                    ajusteExp = ajusteExpCarretera_R;
                    ajusteEscalar = ajusteEscalar_Carretera;
                }
                else { //modoCiudadActivado
                    ajusteExp = ajusteExpCiudad_R;
                    ajusteEscalar = ajusteExpCiudad_R;
                }

            }
            x_Escalado = x_Centrado / ajusteExp;
            valorControlVolante = signo*(exp(signo*(x_Escalado))) * ajusteEscalar;
            valorControlVolante -= signo*ajusteEscalar;//e^0 = 1. Hay que ajustar eso manualmente.

            //Dentro de esta función se acotan los valores de -3200 a 3200.
            setMotorSpeed_Protocol(volnAddress, valorControlVolante);
        }
        else //Joystick centrado.
        {
            valorControlVolante = 0;
            setMotorSpeed_Protocol(volnAddress, valorControlVolante);
        }

    }
    else if(tipoC == MODO_OPENLOOP_LINEAL)
    {
        if(   smoothJS_X < (joyDirectionCenter-umbral_lectura_joystick)
            ||  smoothJS_X > (joyDirectionCenter+umbral_lectura_joystick))
        {
          //if(mapeoCompletoVolante) //mapeoCompletoVolante activo.
          {
            velocidad_volante = map(smoothJS_X, joyMaximoIzquierda, joyMaximoDerecha, 3200, -3200);  //Invertido porque el motor se mueve a la izquierda con joystick a la derecha.
          }
          /*else //mapeoCompletoVolante inactivo.
          {
              velocidad_volante = map(smoothJS_X, joyMaximoIzquierda, joyMaximoDerecha, 1600, -1600);  //Invertido porque el motor se mueve a la izquierda con joystick a la derecha.
          }*/
            setMotorSpeed_Protocol(volnAddress, velocidad_volante);
        } else
        {
            setMotorSpeed_Protocol(volnAddress, 0);
        }
  }
    else if(tipoC == MODO_VELOCIDAD_CLOSEDLOOP)
    {
        //El volante está dentro de los límites.
        if( posVolante_actual > (gradosVolanteIzq + anguloSeguridadVueltaIzq)
        &&  posVolante_actual < (gradosVolanteDer - anguloSeguridadVueltaDer) )
        {
            if(    smoothJS_X < (joyDirectionCenter-umbral_lectura_joystick)
            ||  smoothJS_X > (joyDirectionCenter+umbral_lectura_joystick))
            {
                velocidad_volante = map(smoothJS_X, joyMaximoIzquierda, joyMaximoDerecha, 3200, -3200);  //Invertido porque el motor se mueve a la izquierda con joystick a la derecha.
                setMotorSpeed_Protocol(volnAddress, velocidad_volante);
            }
            else
            {
                setMotorSpeed_Protocol(volnAddress, 0);
            }
        }
        //El volante está casi en el límite
        else if(
            (posVolante_actual > gradosVolanteIzq &&
            posVolante_actual <  gradosVolanteIzq + anguloSeguridadVueltaIzq)
          || (posVolante_actual < gradosVolanteDer &&
            posVolante_actual > gradosVolanteDer-anguloSeguridadVueltaDer))
        {
          velocidad_volante = map(smoothJS_X, joyMaximoIzquierda, joyMaximoDerecha, 1200, -1200);  //Invertido porque el motor se mueve a la izquierda con joystick a la derecha.
          setMotorSpeed_Protocol(volnAddress, velocidad_volante);
        }
        else if(posVolante_actual < gradosVolanteIzq)
        {
          setMotorSpeed_Protocol(volnAddress, -1600);//Regresar a una posición segura con la mitad de la velocidad.
        }
        else if(posVolante_actual > gradosVolanteDer)
        {
          setMotorSpeed_Protocol(volnAddress, 1600);
        }
    }
    else if(tipoC == MODO_POSICION_LINEAL)
    {
        //Para mejorar la controlabilidad hacer mapeo por secciones, para ser más preciso
        //con los primeros 210 grados del volante (lo más usual para vueltas de hasta 90° -esquinas- )

        /*if(smoothJS_Y < 520)
    { //MAPEO
      if(smoothJS_X >= joyIzquierdaMedio && smoothJS_X <= joyDerechaMedio)
      {
        //{----.++++|++++.----}
        posicion_volante_deseada = map(smoothJS_X,  joyIzquierdaMedio,                joyDerechaMedio,
                                                    gradosVolanteIzq_VueltaAngRecto,  gradosVolanteDer_VueltaAngRecto);

      }
      else if(smoothJS_X < joyIzquierdaMedio)
      {
        //{++++.----|----.----}
        posicion_volante_deseada = map(smoothJS_X,  joyMaximoIzquierda,     joyIzquierdaMedio,
                                                    gradosVolanteIzq,       gradosVolanteIzq_VueltaAngRecto);
      }
      else if(smoothJS_X > joyDerechaMedio)
      {
        //{----.----|----.++++}
        posicion_volante_deseada = map(smoothJS_X,  joyDerechaMedio,                  joyMaximoDerecha,
                                                    gradosVolanteDer_VueltaAngRecto,  gradosVolanteDer);
      }
    }
    else if(smoothJS_Y >= 520)
    {
      posicion_volante_deseada = map(smoothJS_X,  joyMaximoIzquierda,                joyMaximoDerecha,
                                                  gradosVolanteIzq_VueltaAngRecto,  gradosVolanteDer_VueltaAngRecto);

    }*/

    if(modoCarreteraActivado) //mapeoCompletoVolante activo.
    {
        /*
        if(mapeoCompletoAcelerador)
        {
            posVolante_deseada = map(smoothJS_X,  joyMaximoIzquierda,                joyMaximoDerecha,
                                            gradosVolanteIzq_VueltaAngRecto,  gradosVolanteDer_VueltaAngRecto);
        }
        else
        {
            posVolante_deseada = map(smoothJS_X,  joyMaximoIzquierda,  joyMaximoDerecha,
                                                    gradosVolanteIzq,  gradosVolanteDer);
        }*/
    }
    else //mapeoCompletoVolante inactivo.
    {
        /*if(mapeoCompletoAcelerador)
        {
            posVolante_deseada = map(smoothJS_X, joyMaximoIzquierda,                     joyMaximoDerecha,
                                            gradosVolanteIzq_Carretera,             gradosVolanteDer_Carretera);
        }
        else{
            posVolante_deseada = map(smoothJS_X,  joyMaximoIzquierda,                joyMaximoDerecha,
                                            gradosVolanteIzq_VueltaAngRecto,  gradosVolanteDer_VueltaAngRecto);
        }*/
    }

    PosMotorDeg_deseada = posVolante_deseada * relacionSprockets;
    int controlMotorDireccion =  ControlPosicionVolante(PosMotorDeg_deseada, PosMotorDeg_actual, &errorPosDireccion, controlVolanteMaximo);


    if(    abs(errorPosDireccion) > umbralErrorPosDireccion    )
    {
      setMotorSpeed_Protocol(volnAddress, controlMotorDireccion);

    #if DEBUG_CONTROL_VOLANTE
      Serial.print(", MDir(err:"); Serial.print(errorPosDireccion);
      Serial.print(", ctl:"); Serial.print(controlMotorDireccion); Serial.print(")");
    #endif
    }
    else
    {
      setMotorSpeed_Protocol(volnAddress, 0);
    }
  }
    else if(tipoC == MODO_POSICION_LOGARITMICO)
    {

    }

    #if DEBUG_POS_VOLANTE
    //Serial.print(",\tPsM(a:"); Serial.print(PosMotorDeg_actual);
    //Serial.print(", d:"); Serial.print(PosMotorDeg_deseada); Serial.print(")");

    Serial.print(",\tVlnt(a:");   Serial.print(posVolante_actual);
    Serial.print(", d:");   Serial.print(posVolante_deseada);              Serial.print(")");

    Serial.print(", vts:");   Serial.print(vueltas);
    //Serial.print(", P:");
    //Serial.print(PosMotorPulsos);     //Position in pulses.
    //Serial.print(", M:");     Serial.print(PosMotorDeg);   //Posición del motor (no del volante) en grados.
    #endif

}



int ControlPosicionVolante(float posicionMotorDeseada, float posicionMotorActual, float* errorMotorDireccion_P, int controlMaximo)
{
  /* Parámetros:
  - float posicionMotorDeseada:
  - float posicionMotorActual:
  - float* errorMotorDireccion:   Se pasa por parámetro porque en el main se necesita
                                  conocer su valor para aplicar o no control a partir de cierto umbral.
  - int controlMaximo:            Para limitar la velocidad maxima del volante y evitar giros bruscos.
                                  El valor máximo del driver de los motores es +-3200.
  */

  //float KP = 10;
  float KP = 20;
  //float KD = 0.1;
  //float KI = 0.3;

  *errorMotorDireccion_P = posicionMotorDeseada - posicionMotorActual;

  int controlMotorDireccion = -((*errorMotorDireccion_P) * (KP));

  //Limitar la velocidad máxima para evitar giros bruscos.
  if(controlMotorDireccion > controlMaximo)
    controlMotorDireccion = controlMaximo;
  else if(controlMotorDireccion < (-controlMaximo) )
    controlMotorDireccion = (-controlMaximo);

  return controlMotorDireccion;
}

void guardarVueltas(int pinEncendido)
{
#if ENCODER_ACTIVADO
  //Variables para definir si el auto está encendido.
  boolean encendido = true;
  encendido = digitalRead(pinEncendido); //***TO-DO***: Instalar un relevador a tierra
                                        //en el pin 9 del arduino; normalmente cerrado.

  if(!encendido && !vueltasGuardadas)
  {
    Serial.println("Apagando");

    //Validar que el pin se mantenga bajo por al menos 3 segundos.
    long startTime = millis();
    boolean guardarVueltas = true;
    while( (millis() - startTime) < 3000 )
    {

      if(digitalRead(pinEncendido) == HIGH )
      {
        guardarVueltas = false;
        break;
      }
    }
    if(guardarVueltas) //Si pasaron 3 segundos y pin_encendido sigue bajo es que se apagó el auto. Almacenar vueltas.
    {
      Serial.print("Saving vueltas: "); Serial.println(vueltas);
      //***TO-DO***: Encender LED de notificacion.

      //Almacenar variable para vueltas.
      EEPROM.write(0, vueltas); //Addr=0, value=vueltas.
      vueltasGuardadas = true;
    }
    else
    {
      Serial.println("Posible falso.");
      //****TO-DO****: Encender LED de advertencia por 5 segundos.
    }
  }
#endif
}

#endif

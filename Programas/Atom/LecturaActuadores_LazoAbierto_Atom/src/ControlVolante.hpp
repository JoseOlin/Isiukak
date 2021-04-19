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


#include <EEPROM.h> //Para almacenar valores en memoria no volatil.

#include "DigitalFilter.hpp"
#include "ControlPedales.hpp"
//#include "LecturaJoystick.hpp"
//#include "DriversMotores.hpp"
#include "LecturaEncoder.hpp"
//#include "Seguridad.hpp"


//*****************************Variables configuración**************************
//#include "Debug.hpp"

//El volante puede girar una vuelta y 3/4 aproximadamente hacia izquierda y derecha.
//Su centro es en: 0 vueltas, 0°. 360+270 = 630. Sin embargo eso debe ser
//convertido al angulo del encoder.
//Cálculo de la relación entre las vueltas del volante y las vueltas del motor.
int dientesEje = 13;   //El sprocket del volante tiene 13 dientes.
int dientesMotor = 10; //El sprocket del motor tiene 10 dientes.
float relacionSprockets = (float)dientesEje / dientesMotor;


float setPointGrados = 180.0 / relacionSprockets;
//float ajusteGrados180 = 0.0;
//////////////////////////////////////**TO-DO: Implementar control de velocidad.
// Para limitar el valor máximo de control aplicado y evitar giros bruscos.
// El máximo es 3,200, probar con 3/4 del máximo.
int controlVolanteMaximo = 3200;
//int controlVolanteMaximo = 2400;

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
//****************************///////////////////////***************************


//*****************************Variables del programa**************************
float errorPosDireccion = 0;
int8_t vueltas = 0;
boolean primeraVueltaIzq = true;

boolean vueltasGuardadas = false; //Para saber si en esta sesion el numero de vueltas ya fue almacenado y no volver a guardar.

enum tiposConduccion {MODO_VELOCIDAD, MODO_POSICION_LIN, MODO_POSICION_LOG};
tiposConduccion tipoC;

float posVolante_actual;
float posVolante_deseada;
float PosMotorDeg_actual = 0.0; //Posicion del motor en grados
float PosMotorDeg_deseada;

boolean EncoderConectado = true;
uint8_t contadorLEDEncoderDesconectado = 0;

uint8_t mapeoCompletoVolante = 0;
uint8_t entradaPCF3;
uint8_t entradaPCF4;
//**************************************************************************************

//Prototipos/
int ControlPosicionVolante(float posicionMotorDeseada, float posicionMotorActual, float* errorMotorDireccion, int controlMaximo);
/////////////

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


void ControlarVolante()
{
  int velocidad_volante = 0;

  posVolante_actual = PosMotorDeg_actual / relacionSprockets;

  ////Controlar el volante.
  if(tipoC == MODO_VELOCIDAD)
  {
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
      setMotorSpeed_Protocol(volnAddress, -1600);
    }
    else if(posVolante_actual > gradosVolanteDer)
    {
      setMotorSpeed_Protocol(volnAddress, 1600);
    }

    #if DEBUG_VOLANTE
    Serial.print(", vel_vln:"); Serial.print(velocidad_volante);
    #endif
  }
  else if(tipoC == MODO_POSICION_LIN)
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

    if(mapeoCompletoVolante) //mapeoCompletoVolante activo.
    {
        if(mapeoCompletoAcelerador)
        {
            posVolante_deseada = map(smoothJS_X,  joyMaximoIzquierda,                joyMaximoDerecha,
                                            gradosVolanteIzq_VueltaAngRecto,  gradosVolanteDer_VueltaAngRecto);
        }
        else
        {
            posVolante_deseada = map(smoothJS_X,  joyMaximoIzquierda,  joyMaximoDerecha,
                                                    gradosVolanteIzq,  gradosVolanteDer);
        }
    }
    else //mapeoCompletoVolante inactivo.
    {
        if(mapeoCompletoAcelerador)
        {
            posVolante_deseada = map(smoothJS_X, joyMaximoIzquierda,                     joyMaximoDerecha,
                                            gradosVolanteIzq_Carretera,             gradosVolanteDer_Carretera);
        }
        else{
            posVolante_deseada = map(smoothJS_X,  joyMaximoIzquierda,                joyMaximoDerecha,
                                            gradosVolanteIzq_VueltaAngRecto,  gradosVolanteDer_VueltaAngRecto);
        }
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
  else if(tipoC == MODO_POSICION_LOG)
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

}

#endif

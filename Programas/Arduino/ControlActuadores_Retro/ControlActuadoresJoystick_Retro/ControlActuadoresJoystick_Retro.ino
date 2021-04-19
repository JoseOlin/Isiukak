/*****************************************************************************
act1: Freno.           0x0D
act2: Acelerador.      0x0A

act3: Volante.         0x04  (0000 0100)


Documentacion cableado
A0: Tap central joystick control. Incremento acelera, decremento frena.
A1: Josytick eje X (Volante)
A2: Pot actuador 1 (Freno)
A3: Pot actuador 2 (Accel)

Pin 8 digital: Tx hacia los puentes

******************************************************************************/

#include "ControlPIDVolante.hpp"


//Rango del joystick (Valores experimentales).
int joyForward_minVal = 507;
int joyForward_maxVal = 1023;

int joyBackward_minVal = 0;
int joyBackward_maxVal = 506; 

int joyDirectionCenter = 518; //Centro del joystick, eje X.

int umbral = 3; //Valor para evitar mover los actuadores con valores muy pequeños en el potenciometro
int umbral_error = 3;

int umbral_error_encoder = 5;



int acel_posDeseada = 0;    
int freno_posDeseada = 0;
int error_acel;
int error_freno;
int controlAcel, controlFreno;
int velocidad_volante = 0;

int frenAddress = 0x0D; //13 = 1101
int acelAddress = 0x0A; //10 = 1010
int volnAddress = 0x04; // 4 = 0100


//*** Variables para el filtrado de las señales analogicas.
#define filterSamples 11  
int joy_Y_SmoothArray[filterSamples]; // Arreglo para almacenar los valores analogicos crudos.
int smoothJS_Y;

int joy_X_SmoothArray[filterSamples];
int smoothJS_X;

int act1SmoothArray[filterSamples]; //Valores crudos de la retroalimentacion del actuador 1.
int smoothAct1;

int act2SmoothArray[filterSamples];
int smoothAct2;





tiposConduccion tipoC;


void setup()
{
  Serial.begin(115200);
  //Serial.begin(19200);
  Serial.println("starting");
  
  smcSerial.begin(9600); //Se probo con 19200 y funciona pero se busca el minimo. 
  //exitSafeStart_Protocol(frenAddress); //Desactivar el exitSafeStart en cada puente.
  
  analogReference(DEFAULT); //the default analog reference of 5 volts (on 5V Arduino boards) or 3.3 volts (on 3.3V Arduino boards).
  
  pinMode(A0, INPUT);
  digitalWrite(A0, LOW); //Deshabilitar la resistencia pull up
  
  
    
  pinMode(pin_encendido, INPUT_PULLUP); //Por defecto en alto
  
  int enc = digitalRead(pin_encendido);
  //Serial.print("enc:"); Serial.println(enc);
  
  
  //**Inicializacion Comunicacion Encoder (SPI)
  pinMode(CS,OUTPUT);//Slave Select
  digitalWrite(CS,HIGH);
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  SPI.end();
  
  //Serial.print("factor:");
  //Serial.println(factor);
  
  //Cargar valor de cantidad de vueltas.
  vueltas = EEPROM.read(0); //Leer el byte de la direccion 0 en la EEPROM
  //Serial.print("V: ");
  //Serial.println(vueltas);
  ABSposition_last = LeerEncoder();
  AbsPosLastDeg = ABSposition_last*factor;
  
  
  Serial.flush();

  delay(2000);
  //*******************************************
  
  //tipoC = MODO_VELOCIDAD; //Modo de control del volante.
  tipoC = MODO_POSICION;
}


void loop()
{
  //Lectura de encoder
  ABSposition = LeerEncoder(); 
  //AbsPosDeg = ABSposition*factor;

  //if(ABSposition != ABSposition_last)    //if nothing has changed dont wast time sending position
  {
    int diferencia = ABSposition_last - ABSposition;
    
    //Si hay un salto abrupto en la posicion; ejemplo de 360 a 0° (maximo de 350 a 10°).
    if(  (diferencia >  3640)  /*&& !boot*/ )//340°=3,868p. 320°=3,640p. Condiciones invertidas para incrementar en sentido horario.
    {  vueltas--;  }
    if(  diferencia < -3640  /*&& !boot */ )
    {  vueltas++;  }

    /*if(boot) 
    {//Al encender el sistema la diferencia entre position y position_last puede ser grande (puesto que no hay last). Validar que no considere eso
     //como una vuelta, sino que cargue el valor de la EEPROM.
    
      
      Serial.print("V: ");
      Serial.println(vueltas);      
      boot = false;
    } */

    ABSposition_last = ABSposition;    //set last position to current position
    PosDeg = (float)ABSposition;
    float PosDeg_temp = numPulsos - PosDeg; //Ajuste para incrementar en sentido horario
    PosDeg = (PosDeg_temp * factor + vueltas*360)-310;    //
    //deg = deg_temp * factor; //Prueba para ajustar el encoder en sentido horario.
    
    Pos = ABSposition;
    //Serial.print("Dif:");
    //Serial.print(diferencia);
    Serial.print("V:");
    Serial.print(vueltas);
    //Serial.print(", P:"); 
    //Serial.print(Pos);     //Position in pulses.
    Serial.print(", D:"); 
    Serial.print(PosDeg);   //Position in degrees.
  }   
  
  encendido = digitalRead(pin_encendido); //Descomentar cuando este instalado, y conectar un cable al switch.
  //encendido = true;

  if(!encendido && !vueltasGuardadas)
  {
    Serial.println("Apagando");
    
    //Validar que el pin se mantenga bajo por al menos 2 segundos.
    long startTime = millis();
    boolean guardarVueltas = true;
    while( (millis() - startTime) < 3000 )
    {
      
      if(digitalRead(pin_encendido) == HIGH )
      {
        guardarVueltas = false;
        break;
      }  
    }
    if(guardarVueltas) //Si pasaron 3 segundos y pin_encendido sigue bajo. Almacenar vueltas.
    {
      Serial.print("Saving vueltas: "); Serial.println(vueltas);
      //***Encender LED de notificacion.
    
      //Almacenar variable para vueltas.
      EEPROM.write(0, vueltas); //Addr=0, value=vueltas.
      vueltasGuardadas = true; 
    }
    else
    {
      Serial.println("Posible falso.");
      //***Encender LED de advertencia.      
    }
  } 
  
  //delay(1); 
  int joystick1_Y = analogRead(A0); //A0 para el Pot de Aceleracion y Freno
  //delay(1);   
  smoothJS_Y = digitalSmooth(joystick1_Y, joy_Y_SmoothArray);
  // this small pause is needed between reading analog pins, otherwise we get the same value twice
     
  int joystick1_X = analogRead(A1); //A1 para el Pot de la direccion.
  //delay(1); 
  smoothJS_X = digitalSmooth(joystick1_X, joy_X_SmoothArray);
  // this small pause is needed between reading analog pins, otherwise we get the same value twice
      
  
  
  int act1_PosRaw = analogRead(A2); //Freno
  //delay(1);  
  smoothAct1 = digitalSmooth(act1_PosRaw, act1SmoothArray);
  // this small pause is needed between reading analog pins, otherwise we get the same value twice
    
  int act2_PosRaw = analogRead(A3); //Acelerador
  //delay(1); 
  smoothAct2 = digitalSmooth(act2_PosRaw, act2SmoothArray);
     
 
  if(smoothJS_Y > (joyForward_minVal + umbral) ) //Se quiere acelerar
  {
    freno_posDeseada = act1_maxVal; //Valor del actuador retraido.
    
    acel_posDeseada = map(smoothJS_Y, joyForward_minVal, joyForward_maxVal, act2_maxVal, act2_minVal);//Mapeo inverso (si el joystick aumenta el valor del actuador disminuye)

  }
  else if(smoothJS_Y < (joyBackward_maxVal - umbral) ) //Se quiere frenar.
  {
    acel_posDeseada = act2_maxVal;//Valor del actuador retraido.
    //                             x                 0                  512             28          1009
    freno_posDeseada = map(smoothJS_Y, joyBackward_minVal, joyBackward_maxVal, act1_minVal, act1_maxVal); //Mapeo directo (si el joystick aumenta el valor del actuador aumenta)
    /*
    512-3 = 509 -> Freno casi totalmente retraido  (~1009)
              0 -> Freno totalmente extendido      (28) 
    */
  }
  else //El joystick esta centrado. Retraer ambos actuadores.
  {
    freno_posDeseada = act1_maxVal; //Retraer completamente el freno.
    acel_posDeseada = act2_maxVal; //Retraer completamente el acelerador.
  }
  
  //Calcular valores de control con retroalimentacion
  error_freno = smoothAct1 - freno_posDeseada; //
  controlFreno = error_freno*Kp;
  
  error_acel = acel_posDeseada - smoothAct2; //
  //error_acel = smoothAct2 - acel_posDeseada;
  controlAcel = -error_acel*Kp;//
  
  

    
  //Serial.print(", Jy:");  Serial.print(smoothJS_Y);

  /*Serial.print(",\tF_po:"); Serial.print(smoothAct1); //Valor del potenciometro del act1 (Freno)
  Serial.print(", F_de:"); Serial.print(freno_posDeseada); //Valor deseado para el pot del freno.
  Serial.print(", F_er:"); Serial.print(error_freno); //valor - posDeseada
  Serial.print(", F_ct:"); Serial.print(controlFreno); //Valor de control aplicado al actuador de freno
    
  /*Serial.print(",\t\tA_po:"); Serial.print(smoothAct2);
  Serial.print(", A_de:"); Serial.print(acel_posDeseada);
  Serial.print(", A_er:"); Serial.print(error_acel);
  Serial.print(", A_ct:"); Serial.print(controlAcel);
  */
  
  Serial.print(", Jx:"); Serial.print(smoothJS_X);

  
  //Controlar el freno.
  if(error_freno > umbral_error || error_freno < -umbral_error)
    setMotorSpeed_Protocol(frenAddress, controlFreno);
  else
    setMotorSpeed_Protocol(frenAddress, 0);
      
  
  //Controlar el acelerador.
  if(error_acel > umbral_error || error_acel < -umbral_error)
    setMotorSpeed_Protocol(acelAddress, controlAcel);
  else
    setMotorSpeed_Protocol(acelAddress, 0);
 
 
 
  ////Controlar el volante.
  if(tipoC == MODO_VELOCIDAD)
  {
    if( smoothJS_X < (joyDirectionCenter-umbral)   ||   smoothJS_X > (joyDirectionCenter+umbral) )
    {
      velocidad_volante = map(smoothJS_X, 0, 1023, 3200, -3200);  //Invertido porque el motor se mueve a la izquierda con joystick a la derecha.
      setMotorSpeed_Protocol(volnAddress, velocidad_volante);      
    }
    else
    {
      setMotorSpeed_Protocol(volnAddress, 0);
    }
    Serial.print(", vln:"); Serial.print(velocidad_volante);
  }
  else if(tipoC == MODO_POSICION)
  {
    
    //El volante puede girar una vuelta y 3/4 aproximadamente hacia izquierda y derecha. Su centro es en: 0 vueltas, 0°. 360+270 = 630. Sin embargo eso debe ser
    //convertido al angulo del encoder.  
    
    //if( smoothJS_X < (joyDirectionCenter-umbral)   ||   smoothJS_X > (joyDirectionCenter+umbral) )
    
    
   
    int dientesEje = 13;   //El sprocket del volante tiene 13 dientes.
    int dientesMotor = 10; //El sprocket del motor tiene 10 dientes. 
    float relacionSprockets = (float)dientesEje / dientesMotor;
    
    
    //float posicion_volante_deseada = map(smoothJS_X, 0, 1023, -610, 610); //En grados.
    float posicion_volante_deseada = map(smoothJS_X, 0, 1023, gradosVolanteIzquierda, gradosVolanteDerecha); //En grados.
    
    float posicion_volante_actual = PosDeg / relacionSprockets; 
    
    float posicion_motor_deseada = posicion_volante_deseada * relacionSprockets;

    
    //velocidad_volante =  ControlPosicionVolante(posicion_motor_deseada, deg);
    int controlMotorDireccion =  ControlPosicionVolante(posicion_motor_deseada, PosDeg, &errorPosDireccion);     
    
      
    if(abs(errorPosDireccion) > umbralErrorPosDireccion) 
    { 
      Serial.print(", PsVd:"); Serial.print(posicion_volante_deseada);
      Serial.print(", PsVa:"); Serial.print(posicion_volante_actual);
      Serial.print(", PsMd:"); Serial.print(posicion_motor_deseada);
      Serial.print(", PsMa:"); Serial.print(PosDeg);
      Serial.print(", errMV:"); Serial.print(errorPosDireccion);
      Serial.print(", ctrlMotorDir:"); Serial.print(controlMotorDireccion);
      setMotorSpeed_Protocol(volnAddress, controlMotorDireccion); 
    }
    else
    {
      setMotorSpeed_Protocol(volnAddress, 0);
    } 
    
  }
  
  Serial.print("\n");
}


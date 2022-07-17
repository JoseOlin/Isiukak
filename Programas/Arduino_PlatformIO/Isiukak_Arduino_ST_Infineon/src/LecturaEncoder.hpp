/*
Lectura de Encoder AMT 203 (Absoluto) por SPI.

Conector:
13 11  9  7  5  3  1
14 12 10  8  6  4  2

Configuración cable:
				Largo - Corto
1  N/A
2  CSB			Blanco - Café.   (Chip Select)
3  MISO			Café claro - Crema (blanco)
4  GND			Blanco - Rosa
5  SCK			Café - Blanco
6  5 V+			Rosa - Blanco
7  MOSI 		Blanco - Naranja
8  B			Blanco - Amarillo
9  N/A
10 A			Blanco - Verde
11 N/A
12 X			Blanco - Azul
13 N/A
14 T_Bit		Naranja - Blanco

Micro: Arduino UNO

17 Diciembre 2013

CSB     10 (SS en Arduino, CSB -Chip Select Bar- en encoder, activo en LOW)
MOSI    11
MISO    12
SCK     13

Codigo de Jamiec (Foro Arduino).
*/
#if ENCODER_ACTIVADO
//#include <SPI.h>
#endif

//#include "Seguridad.hpp"


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



#if ENCODER_ACTIVADO
///*************Variables configuración****************
unsigned int umbralContadorRespuesta = 1000;

///*****************************************************



//#define CS 3 //Chip or Slave select Jamiec
#define CS 10 //Chip or Slave select Nuestro

uint16_t ABSposition = 0;
uint16_t ABSposition_last = 0;
float AbsPosDeg;
float AbsPosLastDeg;

int pulsosPorVuelta = 4096; //2 a la 12.
float factorGradosPulsos = (float)360.0/pulsosPorVuelta; //0.087890625; //360/4096


unsigned int PosMotorPulsos = 0; //Posicion del encoder en pulsos.

uint16_t contadorNoRespuesta = 0;
//boolean conectado = true;

uint8_t temp[2];
#endif


#if ENCODER_ACTIVADO
uint8_t  SPI_T(uint8_t msg)    //Repetive SPI transmit sequence
{
   uint8_t msg_temp = 0;  //vairable to hold received data

   digitalWrite(CS, LOW);     //select spi device
   msg_temp = SPI.transfer(msg);    //send and receive
   digitalWrite(CS, HIGH);    //deselect spi device

   return(msg_temp);      //return received byte
}


uint16_t LeerEncoder(boolean* conectado)
{
  uint8_t received = 0xA5;    //just a temp variable
  ABSposition = 0;    //reset position variable

  SPI.begin();    //Start transmission.
  digitalWrite(CS, LOW); //Habilitar disp SPI.

  SPI_T(0x10);   //issue read command
  received = SPI_T(0x00);    //issue NOP to check if encoder is ready to send

  while(received != 0x10)    //loop while encoder is not ready to send
  {
     received = SPI_T(0x00);    //check again if encoder is still working
     delay(1);    //wait a bit  --Cambiado de 2 a 1, probando.
     contadorNoRespuesta++;
     if(contadorNoRespuesta > umbralContadorRespuesta) //Si tarda más de 1 segundo en responder dar por hecho que está desconectado. Paro de emergencia.
     {
       *conectado = false;
       break;
     }
  }

  contadorNoRespuesta = 0;
  if(received == 0x10)
  {
    *conectado = true;
  }
  temp[0] = SPI_T(0x00);    //Receive MSB
  temp[1] = SPI_T(0x00);    //Receive LSB

  digitalWrite(CS, HIGH);  //just to make sure
  SPI.end();    //end transmition

  temp[0] &= ~0xF0;    //mask out the first 4 bits, 00001111

  ABSposition = temp[0] << 8;    //shift MSB to correct ABSposition in ABSposition message
  ABSposition += temp[1];    // add LSB to ABSposition message to complete message

  return ABSposition;
}


boolean ponerACero()
{
  /*   */

  uint8_t received = 0xA5;    //just a temp variable
  ABSposition = 0;    //reset position variable

  SPI.begin();    //Start transmission.
  digitalWrite(CS,LOW); //Habilitar disp SPI.

  SPI_T(0x70);   //comando para definir la posición actual como cero.
  received = SPI_T(0x00);    //issue NOP to check if encoder made the update

  int contador = 0;
  while (received != 0x80)    //loop while encoder is updating
  {
    received = SPI_T(0x00);    //check again if encoder is still working
    delay(1);    //wait a bit  --Cambiado de 2 a 1, probando.
    contador++;
    if(contador>1000)
      return false;
  }
  return true;
}
#endif

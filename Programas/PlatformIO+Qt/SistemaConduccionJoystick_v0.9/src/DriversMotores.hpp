#ifndef DRIVERSMOTORES
#define DRIVERSMOTORES



//*************** Variables configuración ******************//
int valorMaximoControlPuente = 3200;

//************** Fin Variables configuración ***************//


//****Variables para comunicacion serial.****//
#include <SoftwareSerial.h>

#define rxPin 7 //Implementar lectura de los puentes para conocer temperatura y estatus.
#define txPin 8  // pin8 is asssigned as TX pin of arduino

SoftwareSerial smcSerial = SoftwareSerial (rxPin, txPin);
//******************************************//

int frenAddress = 0x0D; //13 = 1101
int acelAddress = 0x0A; //10 = 1010
int volnAddress = 0x04; // 4 = 0100





//****Metodos para control de puente H.****//
void exitSafeStart_Protocol(byte address)
{
  smcSerial.write(0xAA);
  smcSerial.write(address);
  // Function for exiting from error mode
  //smcSerial.write(0x83);
  smcSerial.write(0x03); //Se pone en 0 el MSB.
}


void setMotorSpeed_Protocol(int address, int speed)  // Function for sending data to motor controller
{
  if(speed < -3200) speed = -3200;
  if(speed >  3200) speed =  3200;

  smcSerial.write(0xAA);
  smcSerial.write(address);
  if (speed < 0)
  {
    //smcSerial.write(0x86);
    smcSerial.write(0x06); //motor reverse command with MSB cleared.
    speed = -speed;//make the value of the speed positive
  }
  else
  {
    //smcSerial.write(0x85);//motor forward command
    smcSerial.write(0x05);
  }
  smcSerial.write(speed & 0x1F); //Primer byte de velocidad.
  smcSerial.write(speed >> 5);   //Segundo byte de velocidad.
}
//******Fin Metodos para control de puente H.****//

#endif

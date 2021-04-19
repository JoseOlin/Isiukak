#ifndef DRIVERSMOTORES_HPP
#define DRIVERSMOTORES_HPP

#include "ComunicacionSerial.hpp"

int frenAddress = 0x0D; //13 = 1101
int acelAddress = 0x0A; //10 = 1010

//*********Metodos para control de puente H.******//
enum Actuadores{Freno, Acelerador, Volante};

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

void moverActuador(Actuadores actuador, int speed, bool comportamientoDirecto)
{
    if(actuador == Actuadores::Freno)
    {
        int address = frenAddress;
        int speedResult = 0;
        if(comportamientoDirecto){
            speedResult = speed;
        } else {
            speedResult = -speed;
        }
        setMotorSpeed_Protocol(address, speedResult);
    }
}
//**************************************************//

#endif // DRIVERSMOTORES_HPP

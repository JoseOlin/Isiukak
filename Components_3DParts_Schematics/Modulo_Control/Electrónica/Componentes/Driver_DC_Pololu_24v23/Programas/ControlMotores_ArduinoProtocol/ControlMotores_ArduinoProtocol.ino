/*Comunicacion con varios puentes 24v23 usando el protocolo Pololu.
*/

#include <SoftwareSerial.h>
//****Variables para comunicacin serial.****//
#define rxPin 7 
#define txPin 8  // pin8 is asssigned as TX pin of arduino

SoftwareSerial smcSerial = SoftwareSerial (rxPin, txPin);
//******************************************//

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

void setup()
{
  Serial.begin(19200);
  
  //**Config para control de puente H.
  smcSerial.begin(19200);
  delay (5);
  exitSafeStart_Protocol(0x1D); //Cambiar direccion segun corresponda
  //exitSafeStart_Protocol(0x1F);
  //sendValue(0xAA); //Para activar Pololu protocol en los puentes.
}

int i,j,k,l,csp = 0;

void loop()
{
  if (Serial.available()>= 4)
  {
    i = Serial.read()-'0';
    j = Serial.read()-'0';
    k = Serial.read()-'0';
    l = Serial.read()-'0';
    
    csp = l + k*10 + j*100 + i*1000;
    
    setMotorSpeed_Protocol(0x1D, csp);
    //setMotorSpeed_Protocol(0x1F, csp);
    
  }
}

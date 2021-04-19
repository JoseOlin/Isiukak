

//****Variables para comunicacin serial.****//
#include <SoftwareSerial.h>

#define rxPin 7 
#define txPin 8  // pin8 is asssigned as TX pin of arduino

SoftwareSerial smcSerial = SoftwareSerial (rxPin, txPin);
//******************************************//



//*** Constantes de control PID de los actuadores lineales.
//int Kp = 20; //Buscar adecuada
int Kp = 25;
int Ki = 1;
float Kd = 0;



/***Considerando que el actuador no se utilizara en todo su rango
se define una constante de mapeo.***/ 
////Encontrar valores con pruebas en ControlActuadores_Joystick_NoRetro

//Freno.
// Extendido 28 - 1009 Retraido.
// Primero considerar carrera completa. Despues considerar carrera de 8 cm en lugar de los 10 posibles (1009/10*8 = 807.2)
int act1_minVal = 28;   // Extendido.
int act1_maxVal = 964; // Retraido.

//Acelerador.
int act2_minVal = 28;
//int act2_minVal = 350;   // Extendido.
//int act2_maxVal = 965;
int act2_maxVal = 350;//El acelerador esta inicialmente ligeramente extendido, para que quede en contacto con el acelerador.



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



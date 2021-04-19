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


int posAct = 0;
//int posAct2 = 0;
int joyPos=0;

int frenAddress = 0x0D; //13 = 1101
int acelAddress = 0x0A; //10 = 1010
int Address = acelAddress;

void setup()
{
   Serial.begin(19200);
   
  //**Config para control de puente H.
  smcSerial.begin(19200);
  delay (5);
  exitSafeStart_Protocol(acelAddress); 
}

void loop()
{
  //Leer valor del joystick
  joyPos = analogRead(A0);
  
  //Si el valor es positivo extender los actuadores
  //512 es el centro aproximado.
  if(joyPos > 519)
  {
    setMotorSpeed_Protocol(Address,3200);
  }
  //Si el valor es negativo contraer los actuadores
  else if(joyPos < 509)
  {
   setMotorSpeed_Protocol(Address,-3200);
  }
  //Detener motor.
  else
  {
    setMotorSpeed_Protocol(Address,0);
  }
  
  
  Serial.print("jyk1_V:");  Serial.print(joyPos);
  
  //Leer potenciometro del actuador y desplegar.
  posAct = analogRead(A3);
  Serial.print(", Act_pos:");    Serial.println(posAct);
  
  ////Leer potenciometro del actuador 2 y desplegar.
  //posAct2 = analogRead(A2); 
  //Serial.print(", Act2"); Serial.println(posAct2);
  delay(5);
  
}

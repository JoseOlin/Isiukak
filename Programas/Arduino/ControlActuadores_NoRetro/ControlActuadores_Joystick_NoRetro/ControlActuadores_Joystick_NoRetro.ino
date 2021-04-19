/*
Programa para encontrar el intervalo adecuado para los actuadores.
act1: Freno.
act2: Acelerador.
*/


//************ Variables para comunicacion Serial **********//
#include <SoftwareSerial.h>
//****Variables para comunicacin serial.****//
#define rxPin 7 
#define txPin 8  // pin8 is asssigned as TX pin of arduino

SoftwareSerial smcSerial = SoftwareSerial (rxPin, txPin);
//*********************************************************//


//*********Metodos para control de puente H.******//
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
//**************************************************//


//*****Variables*****//
//***Valores experimentales del potenciometro del joystick.
int joyForward_minVal = 513;
int joyForward_maxVal = 1023;

int joyBackward_minVal = 0;
int joyBackward_maxVal = 512;  

int umbral = 8; //Valor para evitar mover los actuadores con valores muy pequeños en el potenciometro


//3200/512 = 6.25
int Kp = 7;


int frenAddress = 0x0D; //13 = 1101
int acelAddress = 0x0A; //10 = 1010

int address;
int velocidad;



void setup()
{
  Serial.begin(115200);
  smcSerial.begin(19200);
  //address = frenAddress;
  address = acelAddress;
  exitSafeStart_Protocol(address); 
}

void loop()
{
  int joystick1_Value1 = analogRead(A0);
  int joystickValue2 = analogRead(A1);
  
  int act1_Pos = analogRead(A2); //Actuador freno.
  int act2_Pos = analogRead(A3); //Actuador acelerador.
  
  
  Serial.print("j:"); Serial.print(joystick1_Value1);
  Serial.print(",  a1:"); Serial.print(act1_Pos);
  
  if(joystick1_Value1 > (joyForward_minVal + umbral) ) //Mover el actuador hacia enfrente
  { 
    velocidad=(joystick1_Value1 - joyForward_minVal)*Kp;    
    Serial.print(",  f,"); Serial.print("Vel:"); Serial.println(velocidad);
    setMotorSpeed_Protocol(address, velocidad);
  }
  else if(joystick1_Value1 < (joyForward_minVal - umbral) )//Mover el actuador hacia atras.
  {
    velocidad = (joystick1_Value1 - joyBackward_maxVal)*Kp;
    Serial.print(",  b,"); Serial.print("Vel:");Serial.println(velocidad);
    setMotorSpeed_Protocol(address, velocidad);
  }
  else //No movimiento
  {
    Serial.println(",  Stop");
    
    setMotorSpeed_Protocol(address, 0);
  }
  
  delay(1);
  
}

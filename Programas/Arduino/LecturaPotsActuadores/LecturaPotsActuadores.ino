/* Programa para controlar los actuadores y leer los potenciometros para efectos de encontrar los rangos de utilizacion.

*/

#include <SoftwareSerial.h>

//****Variables para comunicacin serial.****//
#define rxPin 7 
#define txPin 8  // pin8 is asssigned as TX pin of arduino

SoftwareSerial smcSerial = SoftwareSerial (rxPin, txPin);
//******************************************//


//****Metodos para control de puente H.****//
void exitSafeStart()
{
  // Function for exiting from error mode
  smcSerial.write(0x83);
}

void setMotorSpeed(int speed)  // Function for sending data to motor controller
{
  if (speed < 0) {
    smcSerial.write(0x86); //motor reverse command
    speed = -speed;//make the value of the speed positive
  }
  else {
    smcSerial.write(0x85);//motor forward command
  }
  smcSerial.write(speed & 0x1F);
  smcSerial.write(speed >> 5);
}


int posAct1 = 0;
int posAct2 = 0;
int joyPos=0;


void setup()
{
   Serial.begin(115200);
   
  //**Config para control de puente H.
  smcSerial.begin(19200);
  delay (5);
  exitSafeStart();
}

void loop()
{
  //Leer valor del joystick
  joyPos = analogRead(A0);
  
  //Si el valor es positivo extender los actuadores
  //512 es el centro aproximado.
  if(joyPos > 515)
  {
    setMotorSpeed(3200);
  }
  //Si el valor es negativo contraer los actuadores
  else if(joyPos < 509)
  {
   setMotorSpeed(-3200);
  }
  //Detener motor.
  else
  {
    setMotorSpeed(0);
  }
  
  //Leer potenciometro del actuador 1 y desplegar.
  posAct1 = analogRead(A1);
  Serial.print("Act1:");    Serial.print(posAct1);
  
  ////Leer potenciometro del actuador 2 y desplegar.
  //posAct2 = analogRead(A2); 
  //Serial.print(", Act2"); Serial.println(posAct2);
  
}

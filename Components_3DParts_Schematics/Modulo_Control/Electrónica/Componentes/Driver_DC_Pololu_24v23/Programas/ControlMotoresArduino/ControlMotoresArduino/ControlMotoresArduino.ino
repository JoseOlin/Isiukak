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

void setup() 
{
  Serial.begin(19200);
  
  //**Config para control de puente H.
  smcSerial.begin(19200);
  delay (5);
  exitSafeStart();
}

int i,j,k,l,csp = 0;


/* Asegurarse de enviar siempre 4 digigotos, 
aunque la velocidad sea pequeña (0009, por ejemplo, en lugar de 9)
para que se lean 4 digitos.
*/
void loop() 
{
  if (Serial.available()>= 4)
  {
    i = Serial.read()-'0';
    j = Serial.read()-'0';
    k = Serial.read()-'0';
    l = Serial.read()-'0';
    csp = l + k*10 + j*100 + i*1000;
    setMotorSpeed(csp);
  }
}

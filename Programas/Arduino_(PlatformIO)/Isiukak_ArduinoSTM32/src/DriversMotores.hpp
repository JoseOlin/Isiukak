#ifndef DRIVERSMOTORES
#define DRIVERSMOTORES
/* Functions to control Driver DC Pololu 24v23 using the Pololu Protocol.

To use the Pololu protocol, you must transmit 0xAA (170 in decimal) as the first (command)

*/

#include "ComunicacionSerial.hpp"

//*************** Variables configuración ******************//
int valorMaximoControlPuente = 3200;
int ActuatorBrake_Address = 0x03; // 3 = 0111
int ActuatorAccel_Address = 0x0A; //10 = 1010
int ActuatorSteer_Address = 0x04; // 4 = 0100
//************** Fin Variables configuración ***************//


//*************** Variables de Programa ******************//
// Variable IDs. Section 6.4 of User's Guide
#define DRIVER_ERROR_STATUS 0
#define DRIVER_LIMIT_STATUS 3
#define DRIVER_TARGET_SPEED 20
#define DRIVER_INPUT_VOLTAGE 23
#define DRIVER_TEMPERATURE 24

//*************** Fin Variables de Programa ******************//

class MotorDriver
{
    //Pololu 24v23 Motor DC Driver Using Pololu protocol communication.
public:
    MotorDriver();
    MotorDriver(const char prefix[], byte address);
    char prefix[4];


    int getVariable_Protocol(byte address, unsigned char variableID);

    void readStatus();
    void readVin();
    void readTemp();
    void readErrorsFlag();

    int getVin();
    int getTemp();
    int getErrosFlag();

    void displayInfo();


private:
    byte address;
    // Necessary to be ints to validate -1 values.
    //uint16_t Temp;
    //uint16_t Vin;
    //uint16_t Errors_flag;
    int Temp;
    int Vin;
    int Errors_flag;
};

MotorDriver::MotorDriver(const char prefix[], byte address)
{
    this->address = address;
    strcpy(this->prefix, prefix);
}


void MotorDriver::readStatus()
{
    readVin();
    readTemp();
    readErrorsFlag();
}


int MotorDriver::getVariable_Protocol(byte address, unsigned char variableID)
{
    // Read a variable defined by variableID from the Driver.

    smcSerial.write(0xAA); // Using Pololu Protocol Command Byte.
    smcSerial.write(address);

    //smcSerial.write(0xA1); // Get Variable Command Byte
    smcSerial.write(0x21); //  GetVariable Command Byte with MSB cleared.
    smcSerial.write(variableID);
    //delayMicroseconds(10);
    //return readByte() + 256 * readByte();
    // Response Format:
    // Response Byte 1      |   Response Byte 2
    // variable low byte    |   variable high byte

    int lowByte = readByte();
    int highByte = readByte();

    if( (lowByte > -1) && (highByte > -1) )
    {
        //return readByte() + 256 * readByte();
        //return (uint16_t)((256 * highByte) + lowByte) ;
        return (256 * highByte) + lowByte;
    }
    else
    {   return -1;     }
}



void MotorDriver::readVin()
{
    Vin = getVariable_Protocol(address, DRIVER_INPUT_VOLTAGE);
}

int MotorDriver::getVin()
{
    return Vin;
}


void MotorDriver::readTemp()
{
    Temp = getVariable_Protocol(address, DRIVER_TEMPERATURE);
}

int MotorDriver::getTemp()
{
    return Temp;
}

void MotorDriver::readErrorsFlag()
{
    /*The motor can only be driven when this register has a value of 0.
     * (See Section 3.4 for error descriptions.)
    • Bit 0: Safe Start Violation
    • Bit 1: Required Channel Invalid
    • Bit 2: Serial Error
    • Bit 3: Command Timeout
    • Bit 4: Limit/Kill Switch
    • Bit 5: Low VIN
    • Bit 6: High VIN
    • Bit 7: Over Temperature
    • Bit 8: Motor Driver Error
    • Bit 9: ERR Line High
    • Bits 10-15: reserved */
                // 0000 0011 1111 1111 // Only the first 10 bits have info. =1,023

    //uint16_t mask = 1023;
    Errors_flag = getVariable_Protocol(address, DRIVER_ERROR_STATUS);

}

int MotorDriver::getErrosFlag()
{
    return Errors_flag;
}


void MotorDriver::displayInfo()
{
    #if INFO_MOTOR_DRIVERS
        //Serial.print(", B_Vin: ");
        Serial.print(", "); Serial.print(prefix); Serial.print("_Vin: ");
        //Serial.print(getVariable_Protocol(ActuadorBrake_Address, DRIVER_INPUT_VOLTAGE));
        Serial.print(getVin());


        Serial.print(", "); Serial.print(prefix); Serial.print("_Tmp: ");
        Serial.print(getTemp());

        Serial.print(", "); Serial.print(prefix); Serial.print("_Err: ");
        //Serial.print(getVariable_Protocol(ActuadorBrake_Address, DRIVER_ERROR_STATUS));
        Serial.print(getErrosFlag());
    #endif
}

//**** Funciones para control de puente H con Protocolo Pololu.****//
void setMotorSpeed_Protocol(int address, int speed)  // Function for sending data to motor controller
{
  if(speed < -3200){
      speed = -3200; }
  if(speed >  3200) {
      speed =  3200; }

  smcSerial.write(0xAA);
  smcSerial.write(address);
  if (speed < 0) {
    //smcSerial.write(0x86);
    smcSerial.write(0x06); //motor reverse command with MSB cleared.
    speed = -speed;//make the value of the speed positive
  } else {
    //smcSerial.write(0x85);//motor forward command
    smcSerial.write(0x05);
  }
  smcSerial.write(speed & 0x1F); //Primer byte de velocidad.
  smcSerial.write(speed >> 5);   //Segundo byte de velocidad.
}

void exitSafeStart_Protocol(byte address)
{
  smcSerial.write(0xAA);
  smcSerial.write(address);
  // Function for exiting from error mode
  //smcSerial.write(0x83);
  smcSerial.write(0x03); //Se pone en 0 el MSB.
}

//**** Fin Funciones para control de puente H con Protocolo Pololu. ****//



//**** Funciones para control de puente H sin protocolo Pololu. ****//

/*
unsigned int getVariable(unsigned char variableID)
{   // Function to getVariable from Pololu Driver without protocol (not used anymore
    // given that all of the drivers use protocol).
    smcSerial.write(0xA1);
    smcSerial.write(variableID);
    return readByte() + 256 * readByte();
}
*/

//******Fin Funciones para control de puente H sin protocolo Pololu.****//



#endif

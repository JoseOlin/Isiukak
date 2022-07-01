#ifndef COMUNICACIONSERIAL_HPP
#define COMUNICACIONSERIAL_HPP


//************ Variables para comunicacion Serial **********//
//#include <Arduino.h>


#include "Config.hpp"
#include "Microcontroller.hpp"
#include "Debug.hpp"

#define COMM_MONITOR_SPEED 115200
#define COMM_DRIVERS_SPEED 19200
// Se probó con 19200 y 9600.




#if NUCLEO_F40
HardwareSerial smcSerial(smcRxPin, smcTxPin);
//HardwareSerial smcSerial(USART6_rxPin, USART6_txPin); //TODO: Probar si son los pines correctos
// SERIAL_8N1. 8 data bits, No parity bit, 1 stop bit
#endif

#if INFINEON_XMC4700
#include <HardwareSerial.h>
//#include <SoftwareSerial.h>
//HardwareSerial smcSerial(smcRxPin, smcTxPin);
#define smcSerial Serial1
#endif

unsigned long timeOut = 2; // in ms. To use in setTimeOut
unsigned long timeOutSetted;
//****Variables para comunicacin serial.****//

unsigned int DriversReading_Period = 500;
unsigned int IterationsToDriversReading;
unsigned int counterIterationsToDriversReading = 0;


void Drivers_setIterationsToRead(unsigned int systemPeriod)
{
    //assert(DriversReading_Period >= systemPeriod);

    IterationsToDriversReading = DriversReading_Period / systemPeriod;
    Serial.print("**IterationsToDriveReadig: ");
    Serial.print(IterationsToDriversReading);
    Serial.println("**");
}


uint8_t commInit()
{
    uint8_t InitSuccess = true;

    //Serial.begin(COMM_MONITOR_SPEED);
    Serial.begin(115200);
    Serial.println("Comunicación Serial Iniciada.");
    //smcSerial.begin(COMM_DRIVERS_SPEED);
    smcSerial.begin(19200);

    /*smcSerial.setTimeout(timeOut);
    //timeOutSetted = smcSerial.getTimeout();

    if(timeOutSetted > timeOut)
    {
        Serial.print("**ERROR!!!: TimeOut Not setted.**");
        InitSuccess = false;
    }
    */
    return InitSuccess;
}


int readByte()
{
    /* Read a serial byte (returns -1 if nothing received after the timeout expires)
    Be sure to set a small timeout to ensure realtime. This is very important for
    the safety on the Isiukak system. */

    char c;
    if(smcSerial.readBytes(&c, 1) == 0)
    {
        return -1;
    }

    return (byte)c;
}

/*
// Variables para lectura de enteros en el puerto Serial.
const byte numChars = 32;
char receivedChars[numChars];

//const byte numBytes = 32;
//byte receivedBytes[numBytes];


bool newData = false;
int dataNumber = 0;
// ********************************************************* //

void recvWithEndMarker()
{
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;

    //if(Serial.available() > 0 && newData == false)
    while(Serial.available() > 0 && newData == false)
    {
        //Serial.println("Entré a Serial.available()");
        rc = Serial.read();

        if(rc != endMarker)
        {
            receivedChars[ndx] = rc;
            ndx++;
            if(ndx >= numChars)
            {
                ndx = numChars - 1;
            }
        } else { // rc == endMarker
            receivedChars[ndx] = '\0'; //Caracter de fin de cadena
            ndx = 0;
            newData = true;
            //break; // Esto si se usa while en lugar de if.
        }
    }
}

void recvCharsWithStartEndMarkers()
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while(Serial.available() && newData == false) // <<== NEW - get all bytes from buffer
    {
        rc = Serial.read();

        if(recvInProgress == true)
        {
            if(rc != endMarker)
            {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars){
                    ndx = numChars - 1;
                }
            }
            else{ // rc == endMarker
                receivedChars[ndx] = '\0';
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }

        }
        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
*/

/*
void recuperarValorNumerico(int* variablePorAsignar)
{
    if(newData)
    {
        dataNumber = 0;
        dataNumber = atoi(receivedChars);
#if DEBUG_COMUNICACION_NANO
        Serial.print("***RcvChars: ");
        Serial.print(receivedChars);
        //dataNumber = atoi(receivedBytes);
#endif
        *variablePorAsignar = dataNumber;
#if DEBUG_COMUNICACION_NANO
        Serial.print("Dat: ");
        Serial.print(*variablePorAsignar);
#endif
        newData = false;
    }
}

void showNewNumber()
{
    if(newData)
    {
        dataNumber = 0;
        dataNumber = atoi(receivedChars);
        Serial.print("Esto acaba de llegar: ");
        Serial.print(receivedChars);
        Serial.print("Dato numérico: ");
        Serial.print(dataNumber);
        newData = false;
    }
}

*/

#endif // COMUNICACIONSERIAL_HPP

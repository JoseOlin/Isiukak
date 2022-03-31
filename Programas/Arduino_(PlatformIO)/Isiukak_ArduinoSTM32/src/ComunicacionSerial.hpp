#ifndef COMUNICACIONSERIAL_HPP
#define COMUNICACIONSERIAL_HPP


//************ Variables para comunicacion Serial **********//
#include "Config.hpp"
#include "Debug.hpp"


#include <Arduino.h>

//HardwareSerial Serial(PA3, PA2);

#define rxPin D2  // RX pin D2, PA_10
#define txPin D8  // TX pin D8, PA_9
HardwareSerial smcSerial(rxPin, txPin);
int timeOut = 1; // in ms. To use in setTimeOut
//****Variables para comunicacin serial.****//



void commInit()
{
    //Serial.begin(38400);
    Serial.begin(115200);
    Serial.println("Comunicación Serial Iniciada.");
    //smcSerial.begin(19200);
    smcSerial.begin(9600); // Se probó con 19200 y funciona.
    smcSerial.setTimeout(timeOut);
    unsigned long timeOut = smcSerial.getTimeout();
    if(timeOut > 1)
    {
        Serial.print("**ERROR!!!: TimeOut Not setted.**");
    }

}
//SoftwareSerial smcSerial = SoftwareSerial (rxPin, txPin);
//#define smcSerial Serial1


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

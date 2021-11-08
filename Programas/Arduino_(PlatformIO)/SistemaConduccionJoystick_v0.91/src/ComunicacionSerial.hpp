#ifndef COMUNICACIONSERIAL_HPP
#define COMUNICACIONSERIAL_HPP


//************ Variables para comunicacion Serial **********//
#include "Config.hpp"
#include "Debug.hpp"

#include <Arduino.h>
#include <SoftwareSerial.h>


//****Variables para comunicacin serial.****//
#define rxPin 7  //
#define txPin 8  // pin8 is asssigned as TX pin of arduino

SoftwareSerial smcSerial = SoftwareSerial (rxPin, txPin);

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

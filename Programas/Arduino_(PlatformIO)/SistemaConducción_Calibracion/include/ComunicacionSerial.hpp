#ifndef COMUNICACIONSERIAL_HPP
#define COMUNICACIONSERIAL_HPP

//************ Variables para comunicacion Serial **********//
#include <SoftwareSerial.h>

//****Variables para comunicacin serial.****//
#define rxPin 7
#define txPin 8  // pin8 is asssigned as TX pin of arduino

SoftwareSerial smcSerial = SoftwareSerial (rxPin, txPin);


// Variables para lectura de enteros en el puerto Serial.
const byte numChars = 16;
char receivedChars[numChars];
bool newData = false;
int dataNumber = 0;
//*********************************************************//


void recvWithEndMarker()
{
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    while(Serial.available() > 0)
    {
        rc = Serial.read();

        if(rc != endMarker)
        {
            receivedChars[ndx] = rc;
            ndx++;
            if(ndx >= numChars)
            {
                ndx = numChars - 1;
            }
        } else {
            receivedChars[ndx] = '\0'; //Caracter de fin de cadedna
            ndx = 0;
            newData = true;
            break;
        }
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

void recuperarValorNumerico(int* variablePorAsignar)
{
    if(newData)
    {
        dataNumber = 0;
        dataNumber = atoi(receivedChars);
        Serial.print("Dato: ");
        Serial.print(dataNumber);

        *variablePorAsignar = dataNumber;

         newData = false;
    }
}
#endif // COMUNICACIONSERIAL_HPP

#include <Arduino.h>

const byte numChars = 32;
char receivedChars[numChars];

bool newData = false;
int dataNumber = 0;

long currentTime = 0, lastTime = 0, peri
uint8_t periodoDeseado = 20;

int BrakeActuator_Pos;

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

void recoverIntData(int* positionVariable)
{
    if(newData)
    {
        dataNumber = 0;
        dataNumber = atoi(receivedChars);

        *variablePorAsignar = dataNumber;
        newData = false;
    }
}

void setup()
{
    Wire.begin();

    //Serial.begin(19200);
    //Serial.begin(38400);
    Serial.begin(115200);
    Serial.println("Comm init.");
}

void loop()
{ 
	currentTime = millis();
	if( (currentTime - lastTime) >= period )
    {
		recvWithEndMarker();
        recoverIntData(&BrakeActuator_Pos);
        
        Serial.print(", B_pos(cnt: "); Serial.print(ActuadorFreno_Posicion);
        Serial.print(",\t tgt: ");     Serial.print(ActuadorFreno_PosDeseada);
        Serial.print(")");
        
        // Other stuff...
	}
}

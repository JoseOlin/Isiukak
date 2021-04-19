/***
* Programa que controla el voltaje del motor en función del joystick pero con
una función logarítmica que es menos sensible al centro y más sensible en los
extremos.

*/

#include "LecturaJoystick.hpp"
#include "debug.hpp"

void setup()
{
    Serial.begin(115200);
    Serial.println("Init");

    for(int ii=0; ii< filterSamples; ii++)
    {
        Leer_Joystick();
    }

}


void loop()
{
    Leer_Joystick();

    #if DEBUGJOYSTICK
    Serial.print(", Jy:");  Serial.print(smoothJS_Y);
    Serial.print(",\tJx:"); Serial.print(smoothJS_X);
    #endif



}

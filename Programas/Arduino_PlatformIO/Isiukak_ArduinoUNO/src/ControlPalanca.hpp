#ifndef CONTROLPALANCA_HPP
#define CONTROLPALANCA_HPP

//5: Palanca Arriba.
//4: Palanca Abajo.

#include "LecturaFeedback.hpp"

int pinOutput_PalancaSubir = 5;
int pinOutput_PalancaBajar = 4;

//int joystick_Y_PosAbs = joyY_Center - joyY_FrenoCambios; //Cuando la posición del joystick decrece la posición deseada del actuador aumenta.
//int actuadorFreno_PosCambios = map(joystick_Y_PosAbs,  0, (joyY_Center - joyY_MinVal),
//                                            actFreno_valorRetraido, actFreno_valorExtendido);
static int actuadorFreno_PosCambios = 325;



void ControlPalanca(int ActuadorFreno_Posicion)
{

#if PALANCA_ACTIVADA

    if(ActuadorFreno_Posicion > actuadorFreno_PosCambios)
    {

        if(SubirPalanca)
        {
            digitalWrite(pinOutput_PalancaSubir, HIGH);
            digitalWrite(pinOutput_PalancaBajar, LOW);
        }
        else if(BajarPalanca)
        {
            digitalWrite(pinOutput_PalancaSubir, LOW);
            digitalWrite(pinOutput_PalancaBajar, HIGH);
        }
        else if ( (SubirPalanca && BajarPalanca) )
        {
            digitalWrite(pinOutput_PalancaSubir, LOW);
            digitalWrite(pinOutput_PalancaBajar, LOW);
        }
        else
        {
            digitalWrite(pinOutput_PalancaSubir, LOW);
            digitalWrite(pinOutput_PalancaBajar, LOW);
        }
    }
    else
    {
        digitalWrite(pinOutput_PalancaSubir, LOW);
        digitalWrite(pinOutput_PalancaBajar, LOW);
    }
#endif
}

void desplegarInfoPalanca(int ActuadorFreno_Posicion)
{
#if INFO_PALANCA
    if(ActuadorFreno_Posicion > actuadorFreno_PosCambios)
    {
        Serial.print(", Freno Pos. Shift");
    }
#endif
}

#endif // CONTROLPALANCA_HPP

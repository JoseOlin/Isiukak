#ifndef CONTROLPALANCA_HPP
#define CONTROLPALANCA_HPP

//5: Palanca Arriba.
//4: Palanca Abajo.

#include "LecturaFeedback.hpp"

int pinOutput_PalancaSubir = 5;
int pinOutput_PalancaBajar = 4;




void ControlPalanca(int ActuadorFreno_Posicion)
{
    //ActuadorFreno_Posicion
    //joystick_Y =
    //int joystick_Y_PosAbs = joyY_Center - joyY_FrenoCambios; //Cuando la posición del joystick decrece la posición deseada del actuador aumenta.
    //int actuadorFreno_PosCambios = map(joystick_Y_PosAbs,  0, (joyY_Center - joyY_MinVal),
    //                                            actFreno_valorRetraido, actFreno_valorExtendido);

    static int actuadorFreno_PosCambios = 435;
#if PALANCA_ACTIVADA
    //Serial.print("Actuador freno para cambios");
    //Serial.print(actuadorFreno_PosCambios);

    if(ActuadorFreno_Posicion > actuadorFreno_PosCambios)
    {
#if INFO_PALANCA
        Serial.print("Freno Pos. Shift");
#endif
        if(subirPalanca)
        {
#if INFO_PALANCA
            Serial.print("Palanca: Up");
#endif
            digitalWrite(pinOutput_PalancaSubir, HIGH);
            digitalWrite(pinOutput_PalancaBajar, LOW);
        }
        else if(bajarPalanca)
        {
#if INFO_PALANCA
            Serial.print("Palanca: Down");
#endif
            digitalWrite(pinOutput_PalancaSubir, LOW);
            digitalWrite(pinOutput_PalancaBajar, HIGH);
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

#endif // CONTROLPALANCA_HPP

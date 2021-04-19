#ifndef CONTROLPALANCA_HPP
#define CONTROLPALANCA_HPP

//5: Palanca Arriba.
//4: Palanca Abajo.

int pinPalanca_Subir = 5;
int pinPalanca_Bajar = 4;

uint8_t subirPalanca;
uint8_t bajarPalanca;


void ControlPalanca()
{
    if(subirPalanca)
    {
        digitalWrite(pinPalanca_Subir, HIGH);
        digitalWrite(pinPalanca_Bajar, LOW);
    }
    else if(bajarPalanca)
    {
        digitalWrite(pinPalanca_Subir, LOW);
        digitalWrite(pinPalanca_Bajar, HIGH);
    }
    else
    {
        digitalWrite(pinPalanca_Subir, LOW);
        digitalWrite(pinPalanca_Bajar, LOW);
    }
}

#endif // CONTROLPALANCA_HPP

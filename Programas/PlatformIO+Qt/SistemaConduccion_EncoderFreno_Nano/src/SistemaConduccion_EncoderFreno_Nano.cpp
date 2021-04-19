/*
 * 
 https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/

 Lectura sin bloqueo del puerto serial.
 https://forum.arduino.cc/index.php?topic=396450.msg2727726#msg2727726

 Post original dónde si pueden hacerse comentarios.
 https://forum.arduino.cc/index.php?topic=288234.0

 */

#include <Arduino.h>
// Rotary Encoder Inputs
#define CH_A 2 // Cable verde encoder.
#define CH_B 3 // Cable negro encoder.
#define LED_PIN 13



int currentStateCH_A;
int lastStateCH_A;
int counter = 0;
int lastCounter = 0;

unsigned int periodoDeseado = 30; //Hacerlo más lento que el Arduino UNO, para garantizar que no lo sature.
long tiempoAnterior = 0, tiempoActual = 0;


unsigned int periodoVerificacionComunicacion = 8000;
unsigned int umbralVerificacionComunicacion = periodoVerificacionComunicacion / periodoDeseado;
unsigned int contadorVerificacionComunicacion = 0;


bool handshakeArduinoUNO()
{
    if(Serial.available())
    {
        char c = Serial.read();
        if(c == 'U')
        {
            Serial.println("<Nano>");
            digitalWrite(LED_PIN, HIGH);
            return true;
        }
        else{
            digitalWrite(LED_PIN, LOW);
        }
    }
    return false;
}


void updateEncoder(){


    static String currentDirection = "";

    // Read the current state of CLK
    currentStateCH_A = digitalRead(CH_A);

    // If last and current state of CLK are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (currentStateCH_A != lastStateCH_A  && currentStateCH_A == 1)
    {
        // If the DT state is different than the CLK state then
        // the encoder is rotating CCW so decrement
        if (digitalRead(CH_B) != currentStateCH_A)
        {
            counter ++;
            currentDirection = "CCW";
        } else
        {
            // Encoder is rotating CW so increment
            counter --;
            currentDirection = "CW";
        }
        //Serial.print("Direction: ");
        //Serial.print(currentDirection);
        //Serial.print(" | Counter: ");
        //Serial.println(counter);
    }

    // Remember last CLK state
    lastStateCH_A = currentStateCH_A;
}


void setup() {
    // Set encoder pins as inputs
    pinMode(CH_A, INPUT); // (CLK)
    pinMode(CH_B, INPUT); // (DT)
    pinMode(LED_PIN, OUTPUT);

    // Setup Serial Monitor
    //Serial.begin(38400);
    Serial.begin(115200);

    // Read the initial state of CLK
    lastStateCH_A = digitalRead(CH_A);


    // Call updateEncoder() when any high/low changed seen
    // on interrupt 0 (pin 2), or interrupt 1 (pin 3)
    attachInterrupt(0, updateEncoder, CHANGE);
    attachInterrupt(1, updateEncoder, CHANGE);

    //while(handshakeArduinoUNO() == false) {  }


    delay(5000); //Para esperar la rutina de arranque del arduino UNO.

    tiempoAnterior = millis();
}

void enviarConSaltoDeLinea()
{
    Serial.println(counter);
}

void enviarConLimitadores()
{
    Serial.print('<');
    Serial.print(counter);
    Serial.println('>');
}

void loop() {
    //Serial.print(" | Counter: ");
    //Serial.println(counter);
    tiempoActual = millis();
    if( (tiempoActual - tiempoAnterior) >= periodoDeseado )
    {
        if(lastCounter != counter)
        {
            enviarConSaltoDeLinea();
            lastCounter = counter;
        }

        /*if(contadorVerificacionComunicacion >= umbralVerificacionComunicacion)
        {
          handshakeArduinoUNO();
          contadorVerificacionComunicacion = 0;
        }
        contadorVerificacionComunicacion++;
        */
    
        tiempoAnterior = tiempoActual;
    }
}

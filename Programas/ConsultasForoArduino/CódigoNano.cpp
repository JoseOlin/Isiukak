#include <Arduino.h>
// Rotary Encoder Inputs
#define CH_A 2 // Cable verde encoder.
#define CH_B 3 // Cable negro encoder.

int counter = 0, lastCounter = 0;

int currentStateCH_A;
int lastStateCH_A;
String currentDirection = "";

long lastTime = 0, currentTime = 0;

unsigned int period = 25; 

void updateEncoder(){
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
    }
    // Remember last CLK state
    lastStateCH_A = currentStateCH_A;
}


void setup() {
    // Set encoder pins as inputs
    pinMode(CH_A, INPUT); // (CLK)
    pinMode(CH_B, INPUT); // (DT)

    // Setup Serial Monitor
    //Serial.begin(38400);
    Serial.begin(115200);

    // Read the initial state of CLK
    lastStateCH_A = digitalRead(CH_A);


    // Call updateEncoder() when any high/low changed seen
    // on interrupt 0 (pin 2), or interrupt 1 (pin 3)
    attachInterrupt(0, updateEncoder, CHANGE);
    attachInterrupt(1, updateEncoder, CHANGE);


    lastTime = millis();
}

void loop() {
    //Serial.print(" | Counter: ");
    //Serial.println(counter);
    currentTime = millis();
    if( (currentTime - lastTime) >= period )
    {
        if(lastCounter != counter)
        {
            Serial.println(counter);
            lastCounter = counter;
        }

        lastTime = currentTime;
    }
}

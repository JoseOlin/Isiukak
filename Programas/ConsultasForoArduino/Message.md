https://forum.arduino.cc/index.php?topic=117597.0





Hi, people, I'm getting a similar problem.

I'm triying to control a brake pedal with a linear actuator. I have the next configuration.

One arduino Nano is reading an incremental encoder (from the linear actuator) by interruptions an sending the value of the counter to an Arduino UNO, every 25 ms.


The arduino UNO reads the value with the [code]recvWithEndMarker()[/code] function, proposed by @Robin2 at this great post https://forum.arduino.cc/index.php?topic=396450.msg2727726#msg2727726, every 20 ms (I tried with both arduinos at 20 ms, but the problem persist)


When the counter is one or two digits there is no problem, the communication behaves stable, but when the counter is 3 digits long sometimes the UNO receives only two digits, as you can see in the next sample (crt for current position, tgt for target position).

[code]
B_pos(crt: 89,	 tgt: 123),	 B_err:34
B_pos(crt: 90,	 tgt: 123),	 B_err:33
B_pos(crt: 92,	 tgt: 123),	 B_err:31
B_pos(crt: 93,	 tgt: 123),	 B_err:30
B_pos(crt: 93,	 tgt: 123),	 B_err:30
B_pos(crt: 94,	 tgt: 123),	 B_err:29
B_pos(crt: 95,	 tgt: 123),	 B_err:28
B_pos(crt: 97,	 tgt: 123),	 B_err:26
B_pos(crt: 98,	 tgt: 123),	 B_err:25
B_pos(crt: 98,	 tgt: 123),	 B_err:25
B_pos(crt: 99,	 tgt: 123),	 B_err:24
B_pos(crt: 100,	 tgt: 123),	 B_err:23
B_pos(crt: 10,	 tgt: 123),	 B_err:113
B_pos(crt: 102,	 tgt: 123),	 B_err:21
B_pos(crt: 102,	 tgt: 123),	 B_err:21
B_pos(crt: 10,	 tgt: 123),	 B_err:113
B_pos(crt: 106,	 tgt: 123),	 B_err:17
B_pos(crt: 10,	 tgt: 123),	 B_err:113
B_pos(crt: 111,	 tgt: 123),	 B_err:12
B_pos(crt: 111,	 tgt: 123),	 B_err:12
B_pos(crt: 11,	 tgt: 123),	 B_err:112
B_pos(crt: 115,	 tgt: 123),	 B_err:8
B_pos(crt: 118,	 tgt: 123),	 B_err:5
B_pos(crt: 119,	 tgt: 123),	 B_err:4
B_pos(crt: 119,	 tgt: 123),	 B_err:4
B_pos(crt: 12,	 tgt: 123),	 B_err:111
B_pos(crt: 12,	 tgt: 123),	 B_err:111
B_pos(crt: 12,	 tgt: 110),	 B_err:98
B_pos(crt: 126,	 tgt: 92),	 B_err:-34
B_pos(crt: 126,	 tgt: 67),	 B_err:-59
B_pos(crt: 12,	 tgt: 43),	 B_err:31
B_pos(crt: 128,	 tgt: 24),	 B_err:-104
B_pos(crt: 128,	 tgt: 12),	 B_err:-116
B_pos(crt: 125,	 tgt: 0),	 B_err:-125
B_pos(crt: 125,	 tgt: 0),	 B_err:-125
B_pos(crt: 12,	 tgt: 0),	 B_err:-12
B_pos(crt: 115,	 tgt: 0),	 B_err:-115
B_pos(crt: 112,	 tgt: 0),	 B_err:-112
B_pos(crt: 108,	 tgt: 0),	 B_err:-108
B_pos(crt: 108,	 tgt: 0),	 B_err:-108
B_pos(crt: 10,	 tgt: 0),	 B_err:-10
B_pos(crt: 98,	 tgt: 0),	 B_err:-98
B_pos(crt: 96,	 tgt: 0),	 B_err:-96
B_pos(crt: 93,	 tgt: 12),	 B_err:-81
B_pos(crt: 93,	 tgt: 12),	 B_err:-81
B_pos(crt: 89,	 tgt: 12),	 B_err:-77
B_pos(crt: 85,	 tgt: 12),	 B_err:-73
B_pos(crt: 82,	 tgt: 0),	 B_err:-82
B_pos(crt: 78,	 tgt: 0),	 B_err:-78
[/code]


When  this happen the error value gets high and the actuator start to oscillate.

Both Arduinos are working at 115200 bauds, both with hardware serial. I try at 38400 first but the same behavior appears.

Arduino Nano Code.
[code]#include <Arduino.h>
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
[/code]


Simplified Arduino UNO Code
[code]

[/code]
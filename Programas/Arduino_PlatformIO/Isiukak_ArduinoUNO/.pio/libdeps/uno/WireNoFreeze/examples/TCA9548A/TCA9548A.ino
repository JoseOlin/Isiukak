//
// Example Sketch to demonstrate usefulness of the WireNoFreeze/WSWire
// library
//
// - You just need an Arduino with I2C pins
// - (You may optionally connect the TCA9548A multiplexer if you have one)
// - Flash the sketch and see that it outputs stuff periodically
// - Connect the SCL to GND and see that a different error code is displayed
// - Flash the sketch with #include <Wire.h> instead
// - connect the SCL pin to GND and realize that the sketch hangs


// change this to #include <Wire.h> to use the official Wire library
#include <WireNoFreeze.h>

#define TCAADDR 0x70

uint8_t tcaselect(uint8_t i) {
  if (i > 7) return 0xFF;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  return Wire.endTransmission();
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  for (uint8_t i = 0; i < 8; i++) {
    Serial.print("Selecting I2C multiplexer port nr. ");
    Serial.println(i);
    uint8_t error = tcaselect(i);
    if (error) {
      Serial.print("I2C error while selecting port. Code ");
      Serial.println(error, HEX);
    }
    delay(1e3);
  }
}

/* Prueba el funcionamiento de un potenciometro.


*/

/*
El centro teorico seria
*/

int potVal = 0;
int potPin = A0;

void setup() {
  Serial.begin(115200);
}
void loop() {
  potVal = analogRead(potPin);    // read the value from the sensor
  Serial.println(potVal);
  
  delay(1);        // delay in between reads for stability
}

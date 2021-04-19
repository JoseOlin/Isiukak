int pinRefBajo = 2;
int pinRefAlto = 3;

void setup()
{
  Serial.begin(115200);
  
  pinMode(pinRefBajo, OUTPUT);
  pinMode(pinRefAlto, OUTPUT);
  delay(1);
  digitalWrite(pinRefBajo, LOW);
  digitalWrite(pinRefAlto, HIGH);
  delay(5);
}

void loop()
{

  
   int joyYvalue = analogRead(A0);
   delay(5);
   int joyXvalue = analogRead(A1);

   Serial.print("joyVal_Y:"); Serial.print(joyYvalue);   
   Serial.print(",\tjoyVal_X:"); Serial.println(joyXvalue);
   delay(100);
}

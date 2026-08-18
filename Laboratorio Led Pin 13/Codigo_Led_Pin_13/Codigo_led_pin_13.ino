void setup()
{
  pinMode(13, OUTPUT);  // configura el Pin 13 como salida de voltaje
}

void loop()
{
  digitalWrite(13, HIGH);  // envia una señal de voltaje alto al pin 13
  delay(5000); // Espera por 5000 millisecond(s)
  digitalWrite(13, LOW);
  delay(1000); // Espera por 1000 millisecond(s)
}

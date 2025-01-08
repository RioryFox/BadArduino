void setup()
{
  Serial.begin(9600); // Основной последовательный порт
  Serial1.begin(115000);
}

void loop()
{
  if (Serial1.available() > 0)
  {
    Serial1.println("key115000");
    Serial.println("key115000");
  }
  else if (1)
  {
    delay(750);
  }
  else if (Serial.available() > 0)
  {
    Serial1.println("key9600");
    Serial.println("key9600");
  }
  else 
  {
    Serial1.println("key-None");
    Serial.println("key-None");
  }
  Serial.flush();
  Serial1.flush();
  delay(500);
}


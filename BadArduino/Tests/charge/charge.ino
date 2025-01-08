const int pin2 = 2;
const int pin4 = 6;
bool pc_connection = false; 

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  pinMode(pin2, OUTPUT);
  pinMode(pin4, OUTPUT);
  delay(500);
}

void loop()
{
  if (Serial.available() > 0 and !pc_connection)
  {
    pc_connection = true;
    digitalWrite(pin2, 250);
    digitalWrite(pin4, 250);
    Serial.flush();
  }

  if (!pc_connection && millis() % 50 < 25)
  {
    Serial.println("start");
    digitalWrite(pin4, LOW);
  }

  delay(10);
}


// Simple serial test
//
void setup()  
{
  delay(1000);
  Serial.begin(19200);
  Serial.flush();
}

void loop()  
{
  Serial.print("\rHello>");
  while (Serial.available()) 
  { 
    char inByte = Serial.read(); 
    Serial.println(inByte);
  }
}



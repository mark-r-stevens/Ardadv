
// Test a single ultrasonic sensor
//
const uint8_t tp = 23;
const uint8_t ep = 22;

void setup()
{

  Serial.begin(115200);
  Serial.flush();

    pinMode(tp, OUTPUT);
    pinMode(ep, INPUT);

}

void loop() 
{
    digitalWrite(tp, LOW);
    delayMicroseconds(2);
    digitalWrite(tp, HIGH);
    delayMicroseconds(10);
    digitalWrite(tp, LOW);
    const float distance = pulseIn(ep, HIGH);
  
    ::Serial.print(millis());
  ::Serial.print(" ");
  ::Serial.println(distance, DEC);
  ::Serial.flush();

  ::delay(100);

}

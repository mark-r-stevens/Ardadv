
#include <AFMotor.h>

AF_DCMotor motor(1, MOTOR12_8KHZ);

void setup()
{  
   Serial.begin(9600);           
   Serial.println("Stepper test!");
  
}
void loop()
{  
   Serial.println("speed 100");
   motor.setSpeed(200);	
   motor.run(FORWARD);
   delay(5000);
   Serial.println("speed 0");
   motor.run(RELEASE);
   delay(1000);
}

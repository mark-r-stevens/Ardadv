/*
  10-5-10
  Pete Dokter
  SparkFun Electronics
  
  This is an example sketch for Arduino that shows very basically how to control an Ardumoto
  motor driver shield with a 5V Arduino controller board (3.3V may work, but it's out of spec
  for the L298 H-bridge logic, so no promises). If you're plugging the Ardumoto into an
  Arduino Duemilanove or similar, all the connections are done for you and you can just rewrite
  the examples in this code to your liking.
  
  Changed to reflect a new board revision...
*/


//int pwm_a = 10;  //PWM control for motor outputs 1 and 2 is on digital pin 10
int pwm_a = 3;  //PWM control for motor outputs 1 and 2 is on digital pin 3
int pwm_b = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
int dir_a = 12;  //direction control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 13;  //direction control for motor outputs 3 and 4 is on digital pin 13


void setup()
{
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);
  
  analogWrite(pwm_a, 100);  //set both motors to run at (100/255 = 39)% duty cycle (slow)
  analogWrite(pwm_b, 100);
  
}

void loop()
{
  digitalWrite(dir_a, LOW);  //Set motor direction, 1 low, 2 high
  digitalWrite(dir_b, LOW);  //Set motor direction, 3 high, 4 low
  
  delay(1000);
  
  analogWrite(pwm_a, 255);  //set both motors to run at 100% duty cycle (fast)
  analogWrite(pwm_b, 255);
  
  delay(1000);
  
  digitalWrite(dir_a, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite(dir_b, HIGH);  //Reverse motor direction, 3 low, 4 high
  
  delay(1000);
  
  analogWrite(pwm_a, 100);  //set both motors to run at (100/255 = 39)% duty cycle
  analogWrite(pwm_b, 100);
  
  delay(1000);
}


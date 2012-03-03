/*############### VIRTUABOTIX BASIC ACCELEROMETER CODE #########################
This code is meant to serve as the most basic example of how to read out
from the X Y and Z axis as raw sensor readings.

            ######################################################
 TO PIN A0  #                                                    # To 5 Volts
       ######                                                    ######
       #    #     X Axis                              5 Volt     #    #
       ######                                                    ######
 TO PIN A1  #                                                    #
       ######                                                    ######
       #    #     Y Axis                              3.3 Volt   #    #
       ######                                                    ######
 TO PIN A2  #                                                    # To Ground
       ######                                                    ######
       #    #     Z Axis                              Ground     #    #
       ######                                                    ######
 TO PIN 4   #                                                    #
       ######                                                    ######
       #    #     Sleep                 GS (Sensitivity Select)  #    #
       ######                                                    ######
            #                                                    #
       ######                                                    ######
       #    #     0G                             ST (Self Test)  #    #
       ######                                                    ######
            #                                                    #
            ######################################################
    
 * Find more free code, and great products at http://www.virtuabotix.com/
 * ------------------------------------------------------------------------------
 * $Author: Mr. Joe $
 * $Date: 2011-11-5 $
 * $Revision: 0     $
 * ------------------------------------------------------------------------------
################################################################################*/

int sleepPin= 4; //Turning sleep high turns on the Accelerometer
int xpin= A0;
int ypin = A1;
int zpin = A2;

void setup()
{
  Serial.begin(9600);
  
  pinMode(sleepPin,OUTPUT);
  digitalWrite(sleepPin, HIGH);//turns off sleep mode and activates device
  
  pinMode(xpin, INPUT);//input mode
  digitalWrite(xpin, HIGH);//turn on pull up resistor
  
  pinMode(ypin, INPUT);//input mode
  digitalWrite(ypin, HIGH);//turn on pull up resistor
  
  pinMode(zpin, INPUT);//input mode
  digitalWrite(zpin, HIGH);//turn on pull up resistor
}

void loop()
{
delay(2000); //Delay for readability
Serial.print("X Reading: "); 
Serial.println(analogRead(xpin), DEC);
Serial.print("Y Reading: "); 
Serial.println(analogRead(ypin), DEC);
Serial.print("Z Reading: "); 
Serial.println(analogRead(zpin), DEC);
}

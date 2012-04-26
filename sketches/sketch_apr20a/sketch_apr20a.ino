// Copyright (C) 2012 Mark R. Stevens
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// The servo library
//
#include  "Servo.h"  

// The servos
//
Servo pan;  
Servo tilt;  

// The pins
//
const int pingPin = 7;
const int panPin  = 8;
const int tiltPin = 9;

// Setup the pins for the pin sensor and the pan tilt
//
void setup() 
{  
  Serial.begin(9600);  
  Serial.flush();
  pan.attach(panPin);  
  tilt.attach(tiltPin);  
}  

// Pulse the ping pin with a low / high / low to trigger
// the distance calculation
//
void pulse()
{
  delay(100);
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
}

// Send a low / high / low pulse to the ping sensor and
// read out the distance (then convert from time to a 
// distance measurement)
//
float dist()
{
  pulse();
  pinMode(pingPin, INPUT);
  return pulseIn(pingPin, HIGH) / 29.0 / 2.0;
}

// Average over several samples in a row
//
float avgdist()
{
  float sum = 0;
  for (int i = 0; i < 10; ++i)
  {
    sum += dist();
  }
  return sum / 10;
}

// Loop 
//
void loop() 
{  
  
  // Used to scan up and down in a lawnmower pattern
  //
  int adjust = 1;
    
  // Figure out a good starting point
  //
  const int xstart =   0;  
  const int xstop  = 180;    
  const int ystart =  40;  
  const int ystop  = 100;
  
  // Make sure previous serial info is flushed
  //
  Serial.flush();
  
  // Go to the starting position
  //
  pan.write(xstart);
  tilt.write(ystart);
  delay(5000);
  
  // Sample the requested area of the view sphere
  //
  for (int x = xstart, y = ystart; x < xstop; ++x)
  {
    pan.write(x);
    for (bool done = false; ! done; y += adjust)
    {
      
      // Move to that location
      //
      tilt.write(y); 
      
      // Estimate the distance
      //
      const float d = avgdist();
      
      // Log
      //
      Serial.print(x);  
      Serial.print(", ");  
      Serial.print(y);  
      Serial.print(",");  
      Serial.print(d, DEC);  
      Serial.println();  
      
      // Adjust the lawnmower pattern if we are at an end
      //
      if (y >= ystop)
      {
        adjust = -1;
        done = true;
      }
      else if (y <= ystart)
      {
        adjust = +1;
        done = true;
      }
    } 
  }
}

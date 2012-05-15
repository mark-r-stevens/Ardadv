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

// The Arduino include
//
#include "Arduino.h"

// The Gyroscope
//
#include <sensors/Gyroscope/Gyroscope.h>
ardadv::sensors::gyroscope::Gyroscope gyroscope;

// The servo pins
//
const int panPin  = 8;
const int tiltPin = 9;

// The servo library
//
#include  <vendor/Servo.h>
Servo pan;
Servo tilt;

// Initialize the Gyroscope pins to be output. Initialize the button to
// be input. This is a one time call on startup.
//
void setup() 
{                

  // Setup the serial connection to see output
  //
  Serial.begin(9600);
  Serial.flush();

  // Initialize the Gyroscope
  //
  typedef ardadv::sensors::gyroscope::Gyroscope Gyroscope;
  gyroscope.setup(Gyroscope::INTA(7), Gyroscope::INTB(6), Gyroscope::CS(10));

  // Set up the servo
  //
  pan.attach(9);
  tilt.attach(8);

}

// This is called repeatedly in an event loop. The loop checks
// for the button press event. When it is pressed, the next light
// in the sequence is turned on (and the others are turned off).
//
void loop() 
{

  // Used to turn the servo back and forth
  //
  int adjust = 1;
  int angle  = 0;

  // Default location
  //
  angle = 0;
  tilt.write(90);
  pan.write(angle);
  ::delay(100);

  // Sample the requested area of the view sphere
  //
  while (true)
  {

    // Update the state
    //
    gyroscope.update();

    // Log debugging output
    //
    ::Serial.print(millis());
    ::Serial.print(",");
    ::Serial.print(angle);
    ::Serial.print(",");
    ::Serial.println(gyroscope.z(), DEC);
    ::Serial.flush();

    // Adjust the pattern if we are at an end
    //
    if (angle >= 175)
    {
      adjust = -1;
    }
    else if (angle <= 5)
    {
      adjust = 1;
    }

    // Update the angle
    //
    angle += adjust;

    // Set the pan
    //
    pan.write(angle);

    // Add a small delay
    //
    ::delay(10);
  }
}



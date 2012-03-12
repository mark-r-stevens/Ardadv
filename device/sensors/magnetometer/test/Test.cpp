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

// The Magnetometer
//
#include <sensors/Magnetometer/Magnetometer.h>
ardadv::sensors::Magnetometer::Magnetometer magnetometer;

// Initialize the Magnetometer pins to be output. Initialize the button to
// be input. This is a one time call on startup.
//
void setup() 
{                

  // Setup the serial connection to see output
  //
  Serial.begin(9600);
  Serial.flush();

  // Initialize the Magnetometer
  //
  typedef ardadv::sensors::Magnetometer::Magnetometer Magnetometer;
  magnetometer.setup(Magnetometer::DRDY(9),
                     Magnetometer::RESET(8));
}

// This is called repeatedly in an event loop. The loop checks
// for the button press event. When it is pressed, the next light
// in the sequence is turned on (and the others are turned off).
//
void loop() 
{

  // Update the state
  //
  magnetometer.update();

  // Log debugging output
  //
  if (magnetometer.isValid())
  {
    ::Serial.print(" Start ");
    ::Serial.print(millis());
    ::Serial.print(" ");
    ::Serial.print(magnetometer.x());
    ::Serial.print(" ");
    ::Serial.print(magnetometer.y());
    ::Serial.print(" ");
    ::Serial.print(magnetometer.z());
    ::Serial.print(" Stop ");
    ::Serial.flush();
  }

  // Add a small delay
  //
  ::delay(100);

}



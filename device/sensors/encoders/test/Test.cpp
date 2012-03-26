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

// The Range sensor
//
#include <sensors/encoders/Encoders.h>
ardadv::sensors::encoders::Encoders encoders;

// Initialize the pins.
//
void setup() 
{                

  // Setup the serial connection to see output
  //
  Serial.begin(9600);
  Serial.flush();

  // Initialize the Magnetometer
  //
  typedef ardadv::sensors::encoders::Encoders Encoders;
  encoders.setup(Encoders::Reader(19));
}

// This is called repeatedly in an event loop.
//
void loop() 
{

  // Update the state
  //
  const float distance = encoders.distance();

  // Log debugging output
  //
  ::Serial.print(millis());
  ::Serial.print(" ");
  ::Serial.println(distance, DEC);
  ::Serial.flush();

  // Add a small delay
  //
  ::delay(100);

}



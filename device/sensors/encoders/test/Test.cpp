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
#include <Arduino.h>

// The platform in manual control
//
#include <platform/dfrobot/manual/Manual.h>
ardadv::platform::dfrobot::manual::Manual manual;

// The wheel encoders
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

  // Initialize the encoders
  //
  encoders.setup();

}

// Log encoders
//
void logger()
{
  ::Serial.print(millis());
  ::Serial.print(" ");
  ::Serial.print(encoders.left(), DEC);
  ::Serial.print(" ");
  ::Serial.println(encoders.right(), DEC);
  ::Serial.flush();
}

// This is called repeatedly in an event loop.
//
void loop() 
{

  // Left wheel
  //
  manual.left(150); ::delay(1000);
  manual.left(0);   ::delay(2000);
  logger();

  // Right wheel
  //
  manual.right(200); ::delay(1000);
  manual.right(0);   ::delay(2000);
  logger();
}



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

// The accelerometer
//
#include <sensors/accelerometer/Accelerometer.h>
ardadv::sensors::accelerometer::Accelerometer accelerometer;

// Initialize the accelerometer pins to be output. Initialize the button to
// be input. This is a one time call on startup.
//
void setup() 
{                

  // Setup the serial connection to see output
  //
  Serial.begin(9600);
  Serial.flush();

  // Initialize the accelerometer
  //
  typedef ardadv::sensors::accelerometer::Accelerometer Accelerometer;
  accelerometer.setup(Accelerometer::X(A5),
                      Accelerometer::Y(A4),
                      Accelerometer::Z(A3),
                      Accelerometer::SL(5),
                      Accelerometer::GS(4));
}

// This is called repeatedly in an event loop. The loop checks
// for the button press event. When it is pressed, the next light
// in the sequence is turned on (and the others are turned off).
//
void loop() 
{

  // Update the state
  //
  accelerometer.update();

  // Log debugging output
  //
  Serial.print("Start ");
  Serial.print(millis());
  Serial.print(" ");
  Serial.print(accelerometer.x());
  Serial.print(" ");
  Serial.print(accelerometer.y());
  Serial.print(" ");
  Serial.print(accelerometer.z());
  Serial.println(" Stop ");

  // Add a small delay
  //
  delay(10);

}



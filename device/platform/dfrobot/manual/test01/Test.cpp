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

// Initialize the Motor pins to be output.  This is a one time call on startup.
//
void setup() 
{                

  // Setup the serial connection to see output
  //
  Serial.begin(9600);
  Serial.flush();

  // set the speed to 200/255
  //
  manual.setup(100);

}

// This is called repeatedly in an event loop. The loop checks
// runs the motor forward and then backwards and then stops.
//
void loop() 
{

  // turn it on going forward
  //
  manual.forward();
  delay(1000);

  // the other way
  //
  manual.backward();
  delay(1000);

  // rest
  //
  manual.stop();
  delay(2000);

}



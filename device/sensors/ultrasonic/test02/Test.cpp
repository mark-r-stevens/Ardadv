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
#include <sensors/ultrasonic/Ultrasonic.h>
ardadv::sensors::ultrasonic::Ultrasonic ultrasonic1;
ardadv::sensors::ultrasonic::Ultrasonic ultrasonic2;
ardadv::sensors::ultrasonic::Ultrasonic ultrasonic3;

// Initialize the sensor pins to be input.
//
void setup() 
{                

  // Setup the serial connection to see output
  //
  ::Serial.begin(115200);
  ::Serial.flush();

  // Initialize the range sensors
  //
  typedef ardadv::sensors::ultrasonic::Ultrasonic Ultrasonic;
  ultrasonic1.setup(Ultrasonic::Trigger(23), Ultrasonic::Echo(22));
  ultrasonic2.setup(Ultrasonic::Trigger(25), Ultrasonic::Echo(24));
  ultrasonic3.setup(Ultrasonic::Trigger(27), Ultrasonic::Echo(26));
}

// This is called repeatedly in an event loop.
//
void loop() 
{

  // Update the state
  //
  const float distance1 = ultrasonic1.distance();
  const float distance2 = ultrasonic2.distance();
  const float distance3 = ultrasonic2.distance();

  // Log debugging output
  //
  ::Serial.print(millis());
  ::Serial.print(" ");
  ::Serial.print(distance1, DEC);
  ::Serial.print(" ");
  ::Serial.print(distance2, DEC);
  ::Serial.print(" ");
  ::Serial.println(distance3, DEC);
  ::Serial.flush();

  // Add a small delay
  //
  ::delay(100);

}



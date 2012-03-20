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

  Serial.print("tick");

  manual.forward();      // turn it on going forward
  delay(1000);

  Serial.print("tock");
  manual.backward();     // the other way
  delay(1000);

  Serial.print("tack");
  manual.stop();      // stopped
  delay(1000);

  return;

  // Ask for a command
  //
  Serial.print("command> ");

  // Read the command
  //
  char command[50];
  for (int i = 0; i < 25; ++i)
  {
    while (Serial.available() <= 0)
    {
      ::delay(1);
    }
    command[i] = Serial.read();
    Serial.write(command[i]);
    if (command[i] == '>')
    {
      command[i + 1] = '\0';
      break;
    }
  }

  // Based on the command issue the motor command
  //
  Serial.print("comparing (");
  Serial.print(command);
  Serial.println(")");
  if (::strcmp(command, "<direction=forward>") == 0)
  {
    Serial.println("manual.forward()");
    manual.forward();
  }
  else if (::strcmp(command, "<direction=stop>") == 0)
  {
    Serial.println("manual.stop()");
    manual.stop();
  }
  Serial.println(command);

  //Serial.print("tock");
  //manual.backward();
  //delay(1000);

  //Serial.print("tack");
  //manual.stop();
  //delay(1000);

}



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
#include <vendor/Messenger.h>

// Instantiate Messenger object with the message function and the
// default separator (the space character)
//
Messenger messenger;

// Create the callback function
//
void messageReady()
{

  // Show message contents
  //
  int counter = 0;

  // Loop through all the available elements of the message
  //
  while (messenger.available())
  {
    // Set the pin as determined by the message
    //
    const int value = messenger.readInt();

    // Write
    //
    Serial.print("message[");
    Serial.print(counter++);
    Serial.print("=");
    Serial.println(value);

  }
}

// Initialize the Motor pins to be output.  This is a one time call on startup.
//
void setup() 
{                

  // Setup the serial connection to see output
  //
  Serial.begin(115200);
  Serial.flush();

  // Setup messenger
  //
  messenger.attach(messageReady);

}

// This is called repeatedly in an event loop. The loop checks
// for messages and prints them.
//
void loop() 
{

  // The following line is the most effective way of
  // feeding the serial data to Messenger
  //
  while (Serial.available())
  {
    messenger.process(Serial.read());
  }

}

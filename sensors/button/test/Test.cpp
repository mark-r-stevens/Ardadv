// Demonstration of using LED and pushbuttons on an Arduino UNO
//
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

// The button include
//
#include <sensors/button/Button.h>

// Define the Pins for the LED lights
//
#define LedPinR 10
#define LedPinG 11
#define LedPinY 12

// Define the Pin for the button
//
#define ButtonPin 2

// The count of the number of button presses
//
int count = 0;

// Used to detect the pressed event
//
ardadv::sensors::button::Button button;

// Initialize the Led pins to be output. Initialize the button to
// be input. Set the red led on. This is a one time call on startup.
//
void setup() 
{                

  // Setup the serial connection to see output
  //
  Serial.begin(9600);
  Serial.flush();

  // Sepcify pin usage
  //
  pinMode(LedPinR, OUTPUT);     
  pinMode(LedPinG, OUTPUT);     
  pinMode(LedPinY, OUTPUT);

  // Initialize the button
  //
  button.setPin(ButtonPin);

  // Turn the red led on
  //
  digitalWrite(LedPinR, HIGH);
}

// This is called repeatedly in an event loop. The loop checks
// for the button press event. When it is pressed, the next light
// in the sequence is turned on (and the others are turned off).
//
void loop() 
{

  // If the button was pressed, turn on the next light 
  // in the sequence (wrap back around)
  //
  if (button.check() == ardadv::sensors::button::Button::Pressed)
  {
    digitalWrite(  count % 3 + LedPinR, LOW);
    digitalWrite(++count % 3 + LedPinR, HIGH);
    Serial.print("Event triggered. Count=");
    Serial.println(count);
    Serial.flush();
    delay(100);
  }  

}



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

#include <sensors/button/Button.h>

#include "Arduino.h"

namespace ardadv
{
  namespace sensors
  {
    namespace button
    {
      Button::Button() : mState(ButtonUp), mPin(-1)
      {

      }
      void Button::setPin(int pin)
      {

        // Store the pin
        //
        mPin = pin;

        // Set it as input
        //
        pinMode(mPin,  INPUT);
      }
      Button::Event Button::check()
      {
        // Will be true if the button was pressed
        //
        bool trigger = false;

        // Check if the button is pressed
        //
        if (digitalRead(mPin) == HIGH)
        {
          if (mState == ButtonUp)
          {
            mState = ButtonDown;
            Serial.println("Button::check() pressed");
            Serial.flush();
            return Pressed;
          }
        }
        else
        {
          if (mState == ButtonDown)
          {
            mState = ButtonUp;
            Serial.println("Button::check() released");
            Serial.flush();
            return Released;
          }
        }

        // Done
        //
        return None;

      }
    }
  }
}


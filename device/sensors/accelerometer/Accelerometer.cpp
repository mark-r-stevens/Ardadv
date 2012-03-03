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

#include <sensors/accelerometer/Accelerometer.h>

#include "Arduino.h"

namespace ardadv
{
  namespace sensors
  {
    namespace accelerometer
    {
      Accelerometer::Accelerometer()
      : mPinX(-1)
      , mPinY(-1)
      , mPinZ(-1)
      , mPinSleep(-1)
      {
      }
      void Accelerometer::setup(const X& x, const Y& y, const Z& z, const S& s)
      {

        // Store the pins
        //
        mPinX     = x;
        mPinY     = y;
        mPinZ     = z;
        mPinSleep = s;

        // Set the sleep pin to high activating the device
        //
        ::pinMode(mPinSleep,OUTPUT);
        ::digitalWrite(mPinSleep, HIGH);

        // Activate the x pin
        //
        ::pinMode(mPinX, INPUT);
        ::digitalWrite(mPinX, HIGH);

        // Activate the y pin
        //
        ::pinMode(mPinY, INPUT);
        ::digitalWrite(mPinY, HIGH);

        // Activate the z pin
        //
        ::pinMode(mPinZ, INPUT);
        ::digitalWrite(mPinZ, HIGH);


      }
      void Accelerometer::update()
      {
        mValueX = analogRead(mPinX);
        mValueY = analogRead(mPinY);
        mValueZ = analogRead(mPinZ);
      }
    }
  }
}


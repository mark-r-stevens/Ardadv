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
      namespace
      {
        inline float sqr(float x)
        {
          return x * x;
        }
      }
      Accelerometer::Accelerometer()
      : mPinX(-1)
      , mPinY(-1)
      , mPinZ(-1)
      {
      }
      void Accelerometer::setup(const X& x, const Y& y, const Z& z, const S& s)
      {

        // Store the pins
        //
        mPinX = x;
        mPinY = y;
        mPinZ = z;

        // Set the sleep pin to high activating the device
        //
        ::pinMode(s, OUTPUT);
        ::digitalWrite(s, HIGH);

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

        // The calibration offsets
        //
        const float CalibratedX = 650.0f;
        const float CalibratedY = 659.0f;
        const float CalibratedZ = 642.0f;

        // Get the raw values
        //
        const float AdcRx = analogRead(mPinX) - CalibratedX;
        const float AdcRy = analogRead(mPinY) - CalibratedY;
        const float AdcRz = analogRead(mPinZ) - CalibratedZ;

        // See http://www.starlino.com/imu_guide.html

        // According to http://www.freescale.com/files/sensors/doc/data_sheet/MMA7361L.pdf
        // the MMA7361 is factory corrected for zerog offset and sensitivity

        // Vector magnitude
        //
        const float mag = ::sqrt(sqr(AdcRx) + sqr(AdcRy) + sqr(AdcRz));

        // Make a unit vector
        //
        mValueX = AdcRx / mag;
        mValueY = AdcRy / mag;
        mValueZ = AdcRz / mag;
      }
    }
  }
}


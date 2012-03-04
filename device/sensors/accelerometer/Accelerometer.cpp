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
        inline int mapMMA7361V(int value)
        {
          return map(value, 0, 1024, 0, 5000);
        }
        inline int mapMMA7361G(int value)
        {
          return map(value, 0, 1024, -800, 1600);
        }
      }
      Accelerometer::Accelerometer()
      : mPinX(-1)
      , mPinY(-1)
      , mPinZ(-1)
      , mValueX(0.0f)
      , mValueY(0.0f)
      , mValueZ(0.0f)
      , mOffset(0)
      {
      }
      void Accelerometer::setup(const X& x, const Y& y, const Z& z, const SL& sl, const GS& gs)
      {

        // Store the pins
        //
        mPinX = x;
        mPinY = y;
        mPinZ = z;

        // Set the sleep pin to high activating the device
        //
        ::pinMode(sl, OUTPUT);
        ::digitalWrite(sl, HIGH);

        // Set the precision for 6g mode
        //
        ::pinMode(gs, OUTPUT);
        ::digitalWrite(gs, LOW);

        // Activate the x/y/z pins
        //
        ::pinMode(mPinX, INPUT);
        ::pinMode(mPinY, INPUT);
        ::pinMode(mPinZ, INPUT);

        // Wait and then calibrate
        //
        calibrate();
      }
      void Accelerometer::calibrate()
      {

        // Wait to ensure device is powered and set
        //
        ::delay(100);

        // How many measurements to use in calibration
        const int count = 1000;

        // Grab a 1000 measurements and average
        //
        float   sum  = 0;
        for (int i = 0; i < count;i++)
        {
          sum += mapMMA7361G(analogRead(mPinX));
          sum += mapMMA7361G(analogRead(mPinY));
        }
        mOffset = sum / (count * 2);
      }
      void Accelerometer::update()
      {

        // Get the raw values
        //
        const int AdcRx = analogRead(mPinX);
        const int AdcRy = analogRead(mPinY);
        const int AdcRz = analogRead(mPinZ);

        // Remap to G
        //
        const float Gx = mapMMA7361G(AdcRx) - mOffset;
        const float Gy = mapMMA7361G(AdcRy) - mOffset;
        const float Gz = mapMMA7361G(AdcRz) - mOffset;

        // See http://www.starlino.com/imu_guide.html

        // See http://code.google.com/p/mma7361-library/

        // See http://www.freescale.com/files/sensors/doc/data_sheet/MMA7361L.pdf

        // Vector magnitude
        //
        const float mag = ::sqrt(sqr(Gx) + sqr(Gy) + sqr(Gz));

        // Make a unit vector
        //
        mValueX = Gx / mag;
        mValueY = Gy / mag;
        mValueZ = Gz / mag;
      }
    }
  }
}


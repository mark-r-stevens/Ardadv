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

#include <sensors/Magnetometer/Magnetometer.h>

#include "Arduino.h"

namespace ardadv
{
  namespace sensors
  {
    namespace Magnetometer
    {
      namespace
      {
        inline float computeHeading(float x, float y, float z)
        {
          float heading = 0;
          if ((x == 0) && (y < 0))
          {
            heading = M_PI / 2.0;
          }
          if ((x == 0) && (y > 0))
          {
            heading = 3.0 * M_PI / 2.0;
          }
          if (x < 0)
          {
            heading = M_PI - ::atan(y / x);
          }
          if ((x > 0) && (y < 0))
          {
            heading = -::atan(y / x);
          }
          if ((x > 0) && (y > 0))
          {
            heading = 2.0 * M_PI - ::atan(y / x);
          }
          return int(degrees(heading));
        }
      }
      Magnetometer::Magnetometer()
      : mPinSclk(-1)
      , mPinMiso(-1)
      , mPinMosi(-1)
      , mPinSsnot(-1)
      , mPinDrdy(-1)
      , mPinReset(-1)
      , mValueX(0.0f)
      , mValueY(0.0f)
      , mValueZ(0.0f)
      , mHeading(0.0f)
      {
      }
      void Magnetometer::setup(const SCLK&  sclk,
                               const MISO&  miso,
                               const MOSI&  mosi,
                               const SSNOT& ssnot,
                               const DRDY&  drdy,
                               const RESET& reset)
      {

        // Set the output pin mode
        //
        ::pinMode(ssnot, OUTPUT);
        ::pinMode(reset, OUTPUT);
        ::pinMode(mosi,  OUTPUT);
        ::pinMode(sclk,  OUTPUT);

        // Set the input pin mode
        //
        ::pinMode(miso, INPUT);
        ::pinMode(drdy, INPUT);

        // ssnot is brought low (step 0 below)
        //
        ::digitalWrite(ssnot, LOW);

        // Store
        //
        mPinSclk  = sclk;
        mPinMiso  = miso;
        mPinMosi  = mosi;
        mPinSsnot = ssnot;
        mPinDrdy  = drdy;
        mPinReset = reset;

      }
      void Magnetometer::sendBit(int bit)
      {
        // send the bit on the RISING edge of the clock

        ::digitalWrite(mPinMosi, bit);
        ::delay(2);
        ::digitalWrite(mPinSclk, HIGH);
        ::delay(2);
        ::digitalWrite(mPinSclk, LOW);
        ::delay(2);
      }
      long Magnetometer::receiveBit()
      {
        // receive the data on the FALLING edge of the clock

        ::digitalWrite(mPinSclk, HIGH);
        ::delay(2);
        const long bit = ::digitalRead(mPinMiso);
        ::delay(2);
        ::digitalWrite(mPinSclk, LOW);
        ::delay(2);

        return bit;
      }
      float Magnetometer::readAxis(int axis)
      {
        // send eight bits, wait until the data is ready then receive 16 bits

        // pulse the reset

        ::digitalWrite(mPinReset, LOW);
        ::delay(2);
        ::digitalWrite(mPinReset, HIGH);
        ::delay(2);
        ::digitalWrite(mPinReset, LOW);
        ::delay(2);

        // send the command byte

        // set the time to read the magnetic sensors (ASIC period) as /2048

        sendBit(LOW);
        sendBit(HIGH);
        sendBit(HIGH);
        sendBit(LOW);
        sendBit(LOW);
        sendBit(LOW);

        // the last two bits select the axis

        if (axis == 0)  // x axis
        {
          sendBit(LOW);
          sendBit(HIGH);
        }
        else if (axis == 1)  // y axis
        {
          sendBit(HIGH);
          sendBit(LOW);
        }
        else  // z axis
        {
          sendBit(HIGH);
          sendBit(HIGH);
        }

        // wait until the DRDY line is high

        while (::digitalRead(mPinDrdy) == LOW)
        {
        }

        long total = 0;

        // receive result
        // the leftmost bit mark the number as positive or negative

        const long sign = receiveBit();

        // the remaining bits are converted to an integer

        for (int i = 14; i >= 0; i = i - 1)
        {
          total = total | (receiveBit() << i);
        }

        if (sign == 1)
        {
          total = total - 32768;
        }

        // set and return the appropriate variable
        //
        return total;
      }
      void Magnetometer::update()
      {

        // Basic operation will follow these steps. Refer to the timing
        // diagrams on the following page.
        //
        // 1. SSNOT is brought low.
        //
        // 2. Pulse RESET high (return to low state). You must RESET the
        //    MicroMag3 before every measurement.
        //
        // 3. Data is clocked in on the MOSI line. Once eight bits are read
        //    in, the MicroMag3 will execute the command.
        //
        // 4. The MicroMag3 will make the measurement. A measurement consists
        //    of forward biasing the sensor and making a period count; then
        //    reverse biasing the sensor and counting again; and finally,
        //    taking the difference between the two bias directions.
        //
        // 5. At the end of the measurement, the DRDY line is set to high
        //    indicating that the data is ready. In response to the next
        //    16 SCLK pulses, data is shifted out on the MISO line.
        //
        // If you need to make another measurement, go to Step 2. You can
        // send another command after the reset. In this case, keep SSNOT
        // low. If you will not be using the MicroMag3, set SSNOT to high to
        // disable the SPI port.

        // Get the raw values
        //
        mValueX = readAxis(0);
        mValueY = readAxis(1);
        mValueZ = readAxis(2);

        // Compute the heading from the different axis
        //
        mHeading = computeHeading(mValueX, mValueY, mValueZ);
      }
    }
  }
}


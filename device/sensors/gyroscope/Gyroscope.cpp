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

// Code derived from:
//    http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Sensors/Gyros/3-Axis/L3G4200D_Example.zip
//    by: Jim Lindblom
//    SparkFun Electronics

#include <sensors/gyroscope/Gyroscope.h>

#include <Arduino.h>

#include <vendor/Spi.h>

#include <math.h>

/*************************
    L3G4200D Registers
*************************/
#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define REFERENCE 0x25
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D
#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG 0x2F
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_TSH_XH 0x32
#define INT1_TSH_XL 0x33
#define INT1_TSH_YH 0x34
#define INT1_TSH_YL 0x35
#define INT1_TSH_ZH 0x36
#define INT1_TSH_ZL 0x37
#define INT1_DURATION 0x38

namespace ardadv
{
  namespace sensors
  {
    namespace gyroscope
    {
      namespace
      {
        template<uint8_t T> inline int
          readRegister(const common::Pin<T>& cs, uint8_t address)
        {
          // This tells the L3G4200D we're reading;
          address |= 0x80;
          cs.digitalWrite(LOW);
          SPI.transfer(address);
          const int toRead = SPI.transfer(0x00);
          cs.digitalWrite(HIGH);
          return toRead;
        }
        template<uint8_t T> inline void
          writeRegister(const common::Pin<T>& cs, uint8_t address, uint8_t data)
        {
          // This to tell the L3G4200D we're writing
          address &= 0x7F;
          cs.digitalWrite(LOW);
          SPI.transfer(address);
          SPI.transfer(data);
          cs.digitalWrite(HIGH);
        }
        template<uint8_t T> inline bool
          setupL3G4200D(const common::Pin<T>& cs, uint8_t fullScale)
        {
          // Let's first check that we're communicating properly
          // The WHO_AM_I register should read 0xD3
          //
          if (readRegister(cs, WHO_AM_I)!=0xD3)
          {
            return false;
          }

          // Enable x, y, z and turn off power down:
          //
          writeRegister(cs, CTRL_REG1, 0b00001111);

          // If you'd like to adjust/use the HPF, you can edit the line below
          // to configure CTRL_REG2:
          //
          writeRegister(cs, CTRL_REG2, 0b00000000);

          // Configure CTRL_REG3 to generate data ready interrupt on INT2
          // No interrupts used on INT1, if you'd like to configure INT1
          // or INT2 otherwise, consult the datasheet:
          //
          writeRegister(cs, CTRL_REG3, 0b00001000);

          // CTRL_REG4 controls the full-scale range, among other things:
          //
          fullScale &= 0x03;
          writeRegister(cs, CTRL_REG4, fullScale<<4);

          // CTRL_REG5 controls high-pass filtering of outputs, use it
          // if you'd like:
          //
          writeRegister(cs, CTRL_REG5, 0b00000000);

          // Done
          //
          return true;
        }
        inline float normalize(int v)
        {
          static const float sensitivity = 17.50f / 1000.0f;
          return static_cast<float>(v) * sensitivity;
        }
      }
      Gyroscope::Gyroscope()
      : mValueX(0)
      , mValueY(0)
      , mValueZ(0)
      , mValid(false)
      {
      }
      bool Gyroscope::setup(const DRDY& drdy, const RESET& reset, const CS& cs)
      {

        // Start the SPI library
        //
        SPI.setDataMode(SPI_MODE3);
        SPI.setClockDivider(SPI_CLOCK_DIV8);
        SPI.setBitOrder(MSBFIRST);

        // Initialize pins
        //
        mReset.reset(reset, INPUT);
        mDataReady.reset(drdy, INPUT);
        mChipSelect.reset(cs, OUTPUT);

        // Wait for the chip to warm up
        //
        mChipSelect.digitalWrite(HIGH);
        ::delay(100);

        // Configure L3G4200 to the full scale range
        // 0: 250 dps
        // 1: 500 dps
        // 2: 2000 dps
        //
        const bool rtn = setupL3G4200D(mChipSelect, 1);

        // Calibrate
        //
        calibrate();

        // Done
        //
        return rtn;
      }
      void Gyroscope::pulseReset() const
      {
        mReset.digitalWrite(HIGH);
        ::delayMicroseconds(1);
        mReset.digitalWrite(LOW);
      }
      void Gyroscope::calibrate()
      {
        mOffsetX = 0;
        mOffsetY = 0;
        mOffsetZ = 0;
        float mSumX = 0;
        float mSumY = 0;
        float mSumZ = 0;
        for (int i = 0; i < 50; ++i)
        {
          update();
          mSumX += mValueX;
          mSumY += mValueY;
          mSumZ += mValueZ;
        }
        mOffsetX = mSumX / 50;
        mOffsetY = mSumY / 50;
        mOffsetZ = mSumZ / 50;
      }
      void Gyroscope::update()
      {

        // Set valid
        //
        mValid = false;

        // Setup the SPI parameters
        //
        SPI.setDataMode(SPI_MODE3);
        SPI.setClockDivider(SPI_CLOCK_DIV8);
        SPI.setBitOrder(MSBFIRST);

        // Select the device
        //
        mChipSelect.digitalWrite(LOW);
        ::delayMicroseconds(1);

        // Ping the chip
        //
        pulseReset();

        // Wait until an interrupt is received saying the data is ready
        //
        const unsigned long t = micros();
        while (! mDataReady.digitalRead())
        {
          if (micros() - t > 100)
          {
            return;
          }
        }

        // Intermediate values
        //
        int x = 0;
        int y = 0;
        int z = 0;

        // This will update x, y, and z with new values
        //
        x  = (readRegister(mChipSelect, 0x29) & 0xFF) << 8;
        x |= (readRegister(mChipSelect, 0x28) & 0xFF);

        y  = (readRegister(mChipSelect, 0x2B) & 0xFF) << 8;
        y |= (readRegister(mChipSelect, 0x2A) & 0xFF);

        z  = (readRegister(mChipSelect, 0x2D) & 0xFF) << 8;
        z |= (readRegister(mChipSelect, 0x2C) & 0xFF);

        // We now need to normalize the values. First account
        // for at rest returns. The bias here was estimated
        // by just recording values over time and computing the
        // average.
        //
        mValueX = normalize(x - mOffsetX);
        mValueY = normalize(y - mOffsetY);
        mValueZ = normalize(z - mOffsetZ);

        // The data is valid
        //
        mValid = true;

      }
    }
  }
}


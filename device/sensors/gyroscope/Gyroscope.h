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

#ifndef ardadv_sensors_gyroscope_Gyroscope_h
#define ardadv_sensors_gyroscope_Gyroscope_h

#include <sensors/common/Pin.h>

namespace ardadv
{
  namespace sensors
  {
    namespace gyroscope
    {

      //! @class Gyroscope
      //!
      //! @brief Measure the state of the attached Gyroscope and compute
      //!        heading and tilt.
      //!
      //! Coding information mainly followed from instructions at:
      //!    http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Sensors/Gyros/3-Axis/L3G4200D_Example.zip
      //!    by: Jim Lindblom
      //!    SparkFun Electronics
      //!    date: 4/18/11
      //!    license: CC-SA 3.0 - Use this code however you'd like, all we ask
      //!             for is attribution. And let us know if you've improved
      //!             anything!
      //!
      //! From the datasheet
      //!
      //! The L3G4200D is a low-power three-axis angular rate sensor.
      //!
      //! It includes a sensing element and an IC interface capable of
      //! providing the measured angular rate to the external world through a
      //! digital interface (I2C/SPI).
      //!
      //! The sensing element is manufactured using a dedicated micro-machining
      //! process developed by STMicroelectronics to produce inertial sensors
      //! and actuators on silicon wafers.
      //!
      //! The IC interface is manufactured using a CMOS process that allows a
      //! high level of integration to design a dedicated circuit which is
      //! trimmed to better match the sensing element characteristics.
      //!
      //! The L3G4200D has a full scale of ±250/±500/ ±2000 dps and is capable
      //! of measuring rates with a user-selectable bandwidth.
      //!
      //! The L3G4200D is available in a plastic land grid array (LGA) package
      //! and can operate within a temperature range of -40 ¡C to +85 ¡C.
      //!
      class Gyroscope
      {
      public:

        //! @brief Pin definitions (using SCI interface)
        //!
        typedef common::Pin<0>  RESET;
        typedef common::Pin<1>  DRDY;
        typedef common::Pin<2>  CS;

        //! @brief Constructor
        //!
        Gyroscope();

        //! @brief Set the internal pin values
        //!
        //! @param[in] drdy  Interrupt for data read
        //! @param[in] reset Reset the chip
        //! @param[in] CS    Chip select to read data
        //!
        //! @return true if setup successfully
        //!
        bool setup(const DRDY& drdy, const RESET& reset, const CS& cs);

        //! @brief Update the state
        //!
        void update();

        //! @brief Access the raw data
        //!
        //! @return the position
        //!
        inline float x() const
        {
          return mValueX;
        }

        //! @brief Access the raw data
        //!
        //! @return the position
        //!
        inline float y() const
        {
          return mValueY;
        }

        //! @brief Access the raw data
        //!
        //! @return the position
        //!
        inline float z() const
        {
          return mValueZ;
        }

        //! @brief Mark if the reading is valid or not
        //!
        //! @return true if valid
        //!
        inline bool isValid() const
        {
          return mValid;
        }

        //! @brief Return the part number
        //!
        //! @return the part number
        //!
        static inline const char* PartNumber()
        {
          return "L3G4200D";
        }

        //! @brief Return the vendor
        //!
        //! @return the vendor
        //!
        static inline const char* Vendor()
        {
          return "STMicroelectronics";
        }

      protected:

        //! @brief Pulse the reset
        //!
        void pulseReset() const;

        //! @brief Calibrate while sitting still to find the
        //!        offset
        //!
        void calibrate();

      private:

        //! @brief The pins
        //!
        RESET mReset;
        DRDY  mDataReady;
        CS    mChipSelect;

        //! @brief The pin values
        //!
        float mValueX;
        float mValueY;
        float mValueZ;

        //! @brief The offsets
        //!
        float mOffsetX;
        float mOffsetY;
        float mOffsetZ;

        //! @brief Indicate if valid
        //!
        bool mValid;
      };
    }
  }
}
#endif


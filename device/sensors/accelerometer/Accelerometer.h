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

#ifndef ardadv_sensors_accelerometer_Accelerometer_h
#define ardadv_sensors_accelerometer_Accelerometer_h

#include <sensors/common/Pin.h>

namespace ardadv
{
  namespace sensors
  {
    namespace accelerometer
    {

      //! @class Accelerometer
      //!
      //! @brief Measure the state of the attached accelerometer
      //!
      class Accelerometer
      {
      public:

        //! @brief Used to reduce ambiguity in pin assignment
        //!
        typedef common::Pin X;
        typedef common::Pin Y;
        typedef common::Pin Z;
        typedef common::Pin SL;
        typedef common::Pin GS;

        //! @brief Constructor
        //!
        Accelerometer();

        //! @brief Set the internal pin
        //!
        //! @param[in] x The pin number for x
        //! @param[in] y The pin number for y
        //! @param[in] z The pin number for z
        //! @param[in] s The pin number for sleep (turned high to activate)
        //! @param[in] p The pin number for g-selection (turned high to use 6g)
        //!
        void setup(const X& x, const Y& y, const Z& z, const SL& s, const GS& p);

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

        //! @brief Return the part number
        //!
        //! @return the part number
        //!
        static inline const char* PartNumber()
        {
          return "MMA7361";
        }

        //! @brief Return the vendor
        //!
        //! @return the vendor
        //!
        static inline const char* Vendor()
        {
          return "Virtuabotix";
        }

      protected:

        //! @brief Calibrate the offsets by observing the device sitting still
        //!        for a second
        //!
        void calibrate();

      private:

        //! @brief The pins
        //!
        common::Pin mPinX;
        common::Pin mPinY;
        common::Pin mPinZ;

        //! @brief The pin values
        //!
        float mValueX;
        float mValueY;
        float mValueZ;

        //! @brief The calibrated offset
        //!
        int mOffset;

      };
    }
  }
}
#endif


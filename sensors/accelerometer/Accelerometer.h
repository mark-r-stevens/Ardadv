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
        typedef common::Pin S;

        //! @brief Constructor
        //!
        Accelerometer();

        //! @brief Set the internal pin
        //!
        //! @param[in] x The pin number for x
        //! @param[in] y The pin number for y
        //! @param[in] z The pin number for z
        //! @param[in] s The pin number for sleep (turned high to activate)
        //!
        void setup(const X& x, const Y& y, const Z& z, const S& s);

        //! @brief Update the state
        //!
        void update();

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

      private:

        //! @brief The pins
        //!
        common::Pin mPinX;
        common::Pin mPinY;
        common::Pin mPinZ;
        common::Pin mPinSleep;

        //! @brief The pin values
        //!
        float mValueX;
        float mValueY;
        float mValueZ;
      };
    }
  }
}
#endif


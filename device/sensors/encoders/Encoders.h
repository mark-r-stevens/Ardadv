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

// Library for SEN0038 wheel encoders
//

#ifndef ardadv_sensors_encoders_Encoders_h
#define ardadv_sensors_encoders_Encoders_h

#include <sensors/common/Pin.h>

namespace ardadv
{
  namespace sensors
  {
    namespace encoders
    {

      //! @class Encoders
      //!
      //! @brief Measure number of revolutions of an encoder
      //!
      //! With ideas from:
      //!     http://www.dfrobot.com/forum/index.php?topic=354.0
      //!     Lauren from DFRobot
      //!
      //! And
      //!     http://www.pololu.com/docs/0J20/2.a
      //!
      class Encoders
      {
      public:

        //! @brief Constructor
        //!
        Encoders();

        //! @brief Used to reduce ambiguity in pin assignment
        //!
        static const uint8_t LeftWheelEncoder  = 50;
        static const uint8_t RightWheelEncoder = 51;

        //! @brief Setup the interrupt callbacks
        //!
        void setup();

        //! @brief Compute the left distance traveled
        //!
        //! @param[in] Return the distance in meters
        //!
        float left();

        //! @brief Compute the right distance traveled
        //!
        //! @param[in] Return the distance in meters
        //!
        float right();

        //! @brief Return the part number
        //!
        //! @return the part number
        //!
        static inline const char* PartNumber()
        {
          return "SEN0038";
        }

        //! @brief Return the vendor
        //!
        //! @return the vendor
        //!
        static inline const char* Vendor()
        {
          return "DFROBOT";
        }

      private:

      };
    }
  }
}
#endif

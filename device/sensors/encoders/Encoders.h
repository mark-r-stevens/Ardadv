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
      class Encoders
      {
      public:

        //! @brief Constructor
        //!
        Encoders();

        //! @brief Used to reduce ambiguity in pin assignment
        //!
        typedef common::Pin<0> Reader;

        //! @brief Setup the pins
        //!
        //! @param[in] iReader Pin to read the encoder
        //!
        void setup(const Reader& iReader);

        //! @brief Compute the distance
        //!
        //! @param[in] Return the distance in meters
        //!
        float distance();

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

        //! @brief The interrupt number associated with the pin
        //!
        uint8_t mInterrupt;

        //! @brief The integration
        //!
        int mIntegration;
      };
    }
  }
}
#endif

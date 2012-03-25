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

// Library forHY-SRF05 Ultrasonic Sensing Module.
//

#ifndef ardadv_sensors_ultrasonic_Ultrasonic_h
#define ardadv_sensors_ultrasonic_Ultrasonic_h

#include <sensors/common/Pin.h>

namespace ardadv
{
  namespace sensors
  {
    namespace ultrasonic
    {

      //! @class Ultrasonic
      //!
      //! @brief Measure flight time of the sensor and convert that to meters.
      //!
      //! With ideas from:
      //!     Created by ITead studio.  Alex, Apr 20, 2010.
      //!     iteadstudio.com.          cnobile 2011-09-17
      //!     virtuabotix.              Joseph Dattilo, 2012-02-28
      //!
      class Ultrasonic
      {
      public:

        //! @brief Constructor
        //!
        Ultrasonic();

        //! @brief Used to reduce ambiguity in pin assignment
        //!
        typedef common::Pin<0> Trigger;
        typedef common::Pin<1> Echo;

        //! @brief Setup the pins
        //!
        //! @param[in] iTrigger Pin to send the pulse
        //! @param[in] iEcho    Pin to read the echo
        //!
        void setup(const Trigger& iTrigger, const Echo& iEcho);

        //! @brief Compute the distance
        //!
        //! @param[in] Return the distance in meters
        //!
        float distance() const;

      private:

        //! @brief The trigger pin
        //!
        Trigger mTrigger;

        //! @brief The echo pin
        //!
        Echo mEcho;

      };
    }
  }
}
#endif

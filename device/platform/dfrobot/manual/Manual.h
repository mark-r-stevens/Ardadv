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

#ifndef ardadv_platform_dfrobot_manual_Manual_h
#define ardadv_platform_dfrobot_manual_Manual_h

#include <sensors/common/Pin.h>

#include <actuators/motor/Motor.h>

namespace ardadv
{
  namespace platform
  {
    namespace dfrobot
    {
      namespace manual
      {

        //! @class manual
        //!
        //! @brief Enable manual control of the df robot platform
        //!
        class Manual
        {
        public:

          //! @brief Constructor
          //!
          Manual();

          //! @brief Set speed of the left motors
          //!
          //! @param[in] speed The new  speed
          //!
          //! @note positive means forward, negative backward, 0 stop
          //!
          void left(int speed = 100);

          //! @brief Set speed of the right motors
          //!
          //! @param[in] speed The new speed
          //!
          //! @return true if setup successfully
          //!
          //! @note positive means forward, negative backward, 0 stop
          //!
          void right(int speed = 100);

          //! @brief Access the left speed
          //!
          //! @return The left speed
          //!
          inline int leftSpeed() const
          {
            return mLeftSpeed;
          }

          //! @brief Access the right speed
          //!
          //! @return The right speed
          //!
          inline int rightSpeed() const
          {
            return mRightSpeed;
          }

          }
          //! @brief Return the part number
          //!
          //! @return the part number
          //!
          static inline const char* PartNumber()
          {
            return "ROB0025";
          }

          //! @brief Return the vendor
          //!
          //! @return the vendor
          //!
          static inline const char* Vendor()
          {
            return "DF Robot";
          }


        private:

          //! @brief The four motors
          //!
          actuators::motor::Motor mFrontLeft;
          actuators::motor::Motor mFrontRight;
          actuators::motor::Motor mRearLeft;
          actuators::motor::Motor mRearRight;

          //! @brief The left and right speeds
          //!
          int mLeftSpeed;
          int mRightSpeed;
        };
      }
    }
  }
}
#endif


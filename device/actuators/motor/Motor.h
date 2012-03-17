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

#ifndef ardadv_actuators_Motor_Motor_h
#define ardadv_actuators_Motor_Motor_h

#include <sensors/common/Pin.h>

#include <vendor/AFMotor.h>

namespace ardadv
{
  namespace actuators
  {
    namespace motor
    {

      //! @class Motor
      //!
      //! @brief Control the dc motors to move the df robot.
      //!
      //!
      class Motor
      {
      public:

        //! @brief Constructor
        //!
        //! @param[in] motornum The motor number
        //! @param[in] freq     The frequency
        //!
        Motor(uint8_t motornum, uint8_t freq =  MOTOR34_8KHZ);

        //! @brief Set the internal pin
        //!
        //! @param[in] speed The default motor speed
        //!
        //! @return true if setup successfully
        //!
        bool setup(uint8_t speed = 100);

        //! @brief Move the motor forward
        //!
        void forward();

        //! @brief Move the motor backward
        //!
        void backward();

        //! @brief Stop the motor
        //!
        void stop();

        //! @brief Return the part number
        //!
        //! @return the part number
        //!
        static inline const char* PartNumber()
        {
          return "81";
        }

        //! @brief Return the vendor
        //!
        //! @return the vendor
        //!
        static inline const char* Vendor()
        {
          return "AdaFruit";
        }


      private:

        //! @brief The motor controller
        //!
        AF_DCMotor mMotor;

     };
    }
  }
}
#endif


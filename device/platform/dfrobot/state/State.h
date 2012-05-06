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

#ifndef ardadv_platform_dfrobot_state_State_h
#define ardadv_platform_dfrobot_state_State_h

namespace ardadv
{
  namespace platform
  {
    namespace dfrobot
    {
      namespace state
      {

        //! @class state
        //!
        //! @brief Represent the three degree of freedom robot state
        //!
        class State
        {
        public:

          //! @brief Constructor
          //!
          State();

          //! @brief Add the wheel encoder values
          //!
          //! @param[in] left   The left wheel displacement
          //! @param[in] right  The right wheel displacement
          //!
          //! @note Positive means forward, negative backward, 0 stop. The
          //!       units are expected to be in meters
          //!
          void encoders(float left, float right);

          //! @brief Access the state
          //!
          //! @return The position
          //!
          inline float x() const
          {
            return mX;
          }

          //! @brief Access the state
          //!
          //! @return The position
          //!
          inline float y() const
          {
            return mY;
          }

          //! @brief Access the state
          //!
          //! @return The orientation
          //!
          inline float theta() const
          {
            return mTheta;
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

          //! @brief The current state
          //!
          float mX;

          //! @brief The current state
          //!
          float mY;

          //! @brief The current state
          //!
          float mTheta;
        };
      }
    }
  }
}
#endif


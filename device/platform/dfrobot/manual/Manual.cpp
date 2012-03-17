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

#include <platform/dfrobot/manual/Manual.h>

#include <Arduino.h>

namespace ardadv
{
  namespace platform
  {
    namespace dfrobot
    {
      namespace manual
      {
        Manual::Manual()
        : mFrontLeft (1, MOTOR12_64KHZ)
        , mFrontRight(2, MOTOR12_64KHZ)
        , mRearLeft  (3, MOTOR34_1KHZ)
        //, mRearRight (4, MOTOR34_1KHZ)
        {
        }
        bool Manual::setup(uint8_t speed)
        {
          mFrontLeft.setup(speed);
          mFrontRight.setup(speed);
          //mRearLeft.setup(speed);
          //mRearRight.setup(speed);
          return true;
        }
        void Manual::forward()
        {
          mFrontLeft.forward();
          mFrontRight.forward();
          mRearLeft.forward();
          //mRearRight.forward();
        }
        void Manual::backward()
        {
          mFrontLeft.backward();
          mFrontRight.backward();
          RmearLeft.backward();
          //mRearRight.backward();
        }
        void Manual::stop()
        {
          mFrontLeft.stop();
          mFrontRight.stop();
          mRearLeft.stop();
          //mRearRight.stop();
        }
      }
    }
  }
}


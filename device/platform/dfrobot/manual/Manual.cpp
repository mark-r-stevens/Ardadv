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
        : mFrontLeft (1, MOTOR12_8KHZ)
        , mFrontRight(2, MOTOR12_8KHZ)
        , mRearLeft  (3, MOTOR34_1KHZ)
        , mRearRight (4, MOTOR34_1KHZ)
        , mRightSpeed(0)
        , mLeftSpeed(0)
        {
        }
        void Manual::left(int speed)
        {

          // Do nothing if no change
          //
          if (speed == mLeftSpeed)
          {
            return;
          }

          // Move the motors
          //
          if (speed > 0)
          {
            mFrontLeft.forward(speed);
            mRearLeft.forward(speed);
          }
          else if (speed < 0)
          {
            mFrontLeft.backward(-speed);
            mRearLeft.backward(-speed);
          }
          else
          {
            mFrontLeft.stop();
            mRearLeft.stop();
          }

          // Store the new speed
          //
          mLeftSpeed = speed;
        }
        void Manual::right(int speed)
        {
          // Do nothing if no change
          //
          if (speed == mRightSpeed)
          {
            return;
          }

          // Move the motors
          //
          if (speed > 0)
          {
            mFrontRight.forward(speed);
            mRearRight.forward(speed);
          }
          else if (speed < 0)
          {
            mFrontRight.backward(-speed);
            mRearRight.backward(-speed);
          }
          else
          {
            mFrontRight.stop();
            mRearRight.stop();
          }

          // Store the new speed
          //
          mRightSpeed = speed;
        }
      }
    }
  }
}


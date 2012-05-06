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

#include <platform/dfrobot/state/State.h>

#include <Arduino.h>

#include <math.h>

namespace ardadv
{
  namespace platform
  {
    namespace dfrobot
    {
      namespace state
      {
        State::State() : mX(0.0f), mY(0.0f), mTheta(0.0f)
        {
        }
        void State::encoders(float Sl, float Sr)
        {

          // The wheel baseline
          //
          static const float baseline = 0.1524;

          // Predict the location based on the encoders
          //
          const float s = (Sr + Sl) / 2.0f;
          mTheta = (Sr - Sl) / baseline + mTheta;
          mX = s * ::cos(mTheta) + mX;
          mY = s * ::sin(mTheta) + mY;

        }
      }
    }
  }
}


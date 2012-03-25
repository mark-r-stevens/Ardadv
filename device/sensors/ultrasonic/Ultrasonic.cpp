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

#include <sensors/ultrasonic/Ultrasonic.h>

namespace ardadv
{
  namespace sensors
  {
    namespace ultrasonic
    {
      Ultrasonic::Ultrasonic()
      {
      }
      void Ultrasonic::setup(const Trigger& iTrigger, const Echo& iEcho)
      {
        mTrigger.reset(iTrigger,   OUTPUT);
        mEcho.reset(iEcho, INPUT);
      }
      float Ultrasonic::distance() const
      {

        // Pulse the trigger pin
        //
        mTrigger.digitalWrite(LOW);
        ::delayMicroseconds(2);
        mTrigger.digitalWrite(HIGH);
        ::delayMicroseconds(10);

        // Read out the value from the echo pin
        //
        const unsigned long int pulse = ::pulseIn(mEcho, HIGH);

        // Convert the unit-less quantity to meters
        //
       return pulse * 100.0f / 27.6233f / 2.0f;
      }
    }
  }
}

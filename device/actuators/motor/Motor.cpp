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

#include <actuators/Motor/Motor.h>

#include <Arduino.h>

#include <vendor/AFMotor.h>


namespace ardadv
{
  namespace actuators
  {
    namespace Motor
    {
      Motor::Motor(uint8_t num, uint8_t freq) : mMotor(num, freq)
      {
      }
      bool Motor::setup(uint8_t speed)
      {
        mMotor.setSpeed(speed);
        return true;
      }
      void Motor::forward()
      {
        mMotor.run(FORWARD);
      }
      void Motor::backward()
      {
        mMotor.run(BACKWARD);
      }
      void Motor::stop()
      {
        mMotor.run(RELEASE);
      }
   }
  }
}


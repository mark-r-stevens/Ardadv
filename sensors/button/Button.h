// Demonstration of using LED and pushbuttons on an Arduino UNO
//
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

#ifndef ardadv_sensors_button_Button_h
#define ardadv_sensors_button_Button_h

namespace ardadv
{
  namespace sensors
  {
    namespace button
    {

      //! @class Button
      //!
      //! @brief Store the internal state of a push button and
      //!        check for press and release trigger events
      //!
      class Button
      {
      public:

        //! @brief Constructor
        //!
        Button();

        //! @brief Set the internal pin
        //!
        //! @param[in] pin The pin number
        //!
        void setPin(int pin);

        //! @brief The event state
        //!
        enum Event {Pressed=0, Released=1, None=2};

        //! @brief Update the state
        //!
        //! @return The event
        //!
        Event check();

      private:

        //! @brief Used to detect the pressed event
        //!
        enum ButtonState {ButtonDown=0, ButtonUp=1};

        //! @brief The state
        //!
        ButtonState mState;

        //! @brief The pin
        //!
        int mPin;

      };
    }
  }
}
#endif


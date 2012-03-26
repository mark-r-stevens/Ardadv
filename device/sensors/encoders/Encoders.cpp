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

#include <sensors/encoders/Encoders.h>

namespace ardadv
{
  namespace sensors
  {
    namespace encoders
    {
      namespace
      {
        int coder[6] = {0,0,0,0,0,0};
        void interrupt0()
        {
          coder[0] += 1;
        }
        void interrupt1()
        {
          coder[1] += 1;
        }
        void interrupt2()
        {
          coder[2] += 1;
        }
        void interrupt3()
        {
          coder[3] += 1;
        }
        void interrupt4()
        {
          coder[4] += 1;
        }
        void interrupt5()
        {
          coder[5] += 1;
        }
      }
      Encoders::Encoders()
      : mInterrupt(0)
      , mIntegration(0)
      {
      }
      void Encoders::setup(const Reader& iReader)
      {

        // There must be an easier way to do this. Interrupts are defined
        // as numeric numbers (0 to 5). Those interrupts map to specific
        // pins on the board. The linkage between the pin number and the
        // interrupt is explicitly defined. For this class, the user
        // inputs the pin where the encoder is hooked up. It can be one
        // of 5 possibilities. Therefore, here we map those pins to
        // the explicit interrupt numbers.
        //

        // The pin maps to an interrupt
        //
        switch (static_cast<int>(iReader))
        {
          case 2:
            mInterrupt = 0;
            ::attachInterrupt(mInterrupt, interrupt0, CHANGE);
            break;
          case 3:
            mInterrupt = 1;
            ::attachInterrupt(mInterrupt, interrupt1, CHANGE);
            break;
          case 21:
            mInterrupt = 2;
            ::attachInterrupt(mInterrupt, interrupt2, CHANGE);
            break;
          case 20:
            mInterrupt = 3;
            ::attachInterrupt(mInterrupt, interrupt3, CHANGE);
            break;
          case 19:
            mInterrupt = 4;
            ::attachInterrupt(mInterrupt, interrupt4, CHANGE);
            break;
          case 18:
          default:
            mInterrupt = 5;
            ::attachInterrupt(mInterrupt, interrupt5, CHANGE);
            break;
        }
      }
      float Encoders::distance()
      {

        // Grab the count
        //
        mIntegration = coder[mInterrupt];

        // Reset
        //
        coder[mInterrupt] = 0;

        // Normalize by the wheel base
        //

        // Return the distance traveled
        //
        return mIntegration;
      }
    }
  }
}

#ifdef NOT



#define LEFT 0
#define RIGHT 1




long coder[2] = {
                 0,0};
int lastSpeed[2] = {
                    0,0};








void setup(){

  Serial.begin(9600);                            //init the Serial port to print the data
  attachInterrupt(LEFT, LwheelSpeed, CHANGE);    //init the interrupt mode for the digital pin 2
  attachInterrupt(RIGHT, RwheelSpeed, CHANGE);   //init the interrupt mode for the digital pin 3

}




void loop(){

  static unsigned long timer = 0;                //print manager timer

  if(millis() - timer > 100){
    Serial.print("Coder value: ");
    Serial.print(coder[LEFT]);
    Serial.print("[Left Wheel] ");
    Serial.print(coder[RIGHT]);
    Serial.println("[Right Wheel]");

    lastSpeed[LEFT] = coder[LEFT];   //record the latest speed value
    lastSpeed[RIGHT] = coder[RIGHT];
    coder[LEFT] = 0;                 //clear the data buffer
    coder[RIGHT] = 0;
    timer = millis();
  }

}








void LwheelSpeed()
{
  coder[LEFT] ++;  //count the left wheel encoder interrupts
}








void RwheelSpeed()
{
  coder[RIGHT] ++; //count the right wheel encoder interrupts
}
#endif

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

// The Arduino include
//
#include <Arduino.h>

// The platform in manual control
//
#include <platform/dfrobot/manual/Manual.h>
ardadv::platform::dfrobot::manual::Manual manual;

// The location of the robot
//
#include <platform/dfrobot/state/State.h>
ardadv::platform::dfrobot::state::State state;

// The Range sensors
//
#include <sensors/ultrasonic/Ultrasonic.h>
ardadv::sensors::ultrasonic::Ultrasonic ultrasonic;

// The wheel encoders
//
#include <sensors/encoders/Encoders.h>
ardadv::sensors::encoders::Encoders encoders;

// The platform in manual control
//
#include <vendor/CmdMessenger.h>

// Instantiate Messenger object with the message function and the
// default separator (the space character)
//
static const char fieldSeparator = ',';
static const char commandSeparator = ';';
CmdMessenger messenger(Serial, fieldSeparator, commandSeparator);

// We can define up to a default of 50 cmds total, including both directions
// (send + recieve)\ and including also the first 4 default command codes for
// the generic error handling. If you run out of message slots, then just
// increase the value of MAXCALLBACKS in CmdMessenger.h
//
// Commands we send from the Arduino to be received on the PC
//
enum
{
  kCOMM_ERROR    = 000, // Arduino report serial port comm error back to the PC
  kACK           = 001, // Arduino acknowledges cmd was received
  kARDUINO_READY = 002, // PC check if arduino is ready
  kERR           = 003, // Arduino reports badly formatted cmd
  kSTATUS        = 005, // The return measurements
  kSEND_CMDS_END,       // Must not delete this line
};
void ready()
{
  messenger.sendCmd(kACK, "Arduino ready");
}
void unknown()
{
  messenger.sendCmd(kERR, "Unknown command");
}

// Initialize the Motor pins, encoders, and ultrasonic sensor to be output.
//
void setup() 
{                

  // Setup the serial connection to see output
  //
  ::Serial.begin(115200);
  ::Serial.flush();

  // Initialize the range sensors
  //
  typedef ardadv::sensors::ultrasonic::Ultrasonic Ultrasonic;
  ultrasonic.setup(Ultrasonic::Trigger(25), Ultrasonic::Echo(24));

  // Initialize the encoders
  //
  encoders.setup();

  // Make output more readable while debugging in Arduino Serial Monitor
  //
  messenger.print_LF_CR();

  // Attach default / generic callback methods
  //
  messenger.attach(kARDUINO_READY, ready);
  messenger.attach(unknown);

}

void report()
{
  // Get the range sensor estimates
  //
  const float d = ultrasonic.distance();

  // Get the encoders
  //
  float leftEncoder  = encoders.left();
  float rightEncoder = encoders.right();

  // Adjust for forward or backward motion
  //
  if (manual.leftSpeed() < 0)
  {
    leftEncoder *= -1.0f;
  }
  if (manual.rightSpeed() < 0)
  {
    rightEncoder *= -1.0f;
  }

  // Update the state
  //
  state.encoders(leftEncoder, rightEncoder);

  // Get the state
  //
  const float x = state.x();
  const float y = state.y();
  const float theta = state.theta();

  // Log the result to output for visualization via CAS
  //
  ::Serial.print("5,");
  ::Serial.print(leftEncoder,DEC);      ::Serial.print(",");
  ::Serial.print(rightEncoder,DEC);     ::Serial.print(",");
  ::Serial.print(x,DEC);                ::Serial.print(",");
  ::Serial.print(y,DEC);                ::Serial.print(",");
  ::Serial.print(theta,DEC);            ::Serial.print(",");
  ::Serial.print(d,DEC);                ::Serial.println(";");
  ::Serial.flush();

}

// This is called repeatedly in an event loop. The loop moves the robot and
// reports out the overall state
//
void loop()
{

  // Wait a few
  //
  manual.left(0);
  manual.right(0);
  ::delay(5000);

  // Run forward
  //
  manual.left(150);
  manual.right(150);
  for (int i = 0; i < 40; ++i)
  {
    report();
    ::delay(100);
  }

  // Wait a few
  //
  manual.left(0);
  manual.right(0);
  ::delay(5000);

  // Go Backwards
  //
  manual.left(-150);
  manual.right(-150);
  for (int i = 0; i < 40; ++i)
  {
    report();
    ::delay(100);
  }

}

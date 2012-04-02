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

// The Range sensors
//
#include <sensors/ultrasonic/Ultrasonic.h>
ardadv::sensors::ultrasonic::Ultrasonic ultrasonic1;
ardadv::sensors::ultrasonic::Ultrasonic ultrasonic2;
ardadv::sensors::ultrasonic::Ultrasonic ultrasonic3;

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
  kMOTOR         = 004, // Set Motor speeds to left/right motors
  kSTATUS        = 005, // The return measurements
  kSEND_CMDS_END,       // Must not delete this line
};

// Message data is any ASCII bytes (0-255 value). But can't contain the field
// separator, command separator chars you decide (eg ',' and ';')
//
void available()
{
  while (messenger.available())
  {

    // Read
    //
    const int left  = messenger.readInt();
    const int right = messenger.readInt();

    // command
    //
    manual.left(left);
    manual.right(right);
  }
}
void ready()
{
  messenger.sendCmd(kACK, "Arduino ready");
}
void unknown()
{
  messenger.sendCmd(kERR, "Unknown command");
}

// Initialize the Motor pins to be output.  This is a one time call on startup.
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
  ultrasonic1.setup(Ultrasonic::Trigger(23), Ultrasonic::Echo(22));
  ultrasonic2.setup(Ultrasonic::Trigger(25), Ultrasonic::Echo(24));
  ultrasonic3.setup(Ultrasonic::Trigger(27), Ultrasonic::Echo(26));

  // Make output more readable while debugging in Arduino Serial Monitor
  //
  messenger.print_LF_CR();

  // Initialize the encoders
  //
  encoders.setup();

  // Attach default / generic callback methods
  //
  messenger.attach(kARDUINO_READY, ready);
  messenger.attach(unknown);
  messenger.attach(kMOTOR, available);

}

// This is called repeatedly in an event loop. The loop checks
// for messages and prints them.
//
void loop() 
{

  // Get speed commands and act on them
  //
  messenger.feedinSerialData();

  // Get the range sensor estimates
  //
  const float distance1 = ultrasonic1.distance();
  const float distance2 = ultrasonic2.distance();
  const float distance3 = ultrasonic2.distance();

  // Get the control speeds
  //
  const float leftSpeed  = manual.leftSpeed();
  const float rightSpeed = manual.rightSpeed();

  // Get the encoders
  //
  const float leftEncoder  = encoders.left();
  const float rightEncoder = encoders.right();

  // Log the result to output for visualization via CAS
  //
  ::Serial.print("5,<Start>,");
  ::Serial.print(leftSpeed);      ::Serial.print(",");
  ::Serial.print(rightSpeed);     ::Serial.print(",");
  ::Serial.print(leftEncoder);    ::Serial.print(",");
  ::Serial.print(rightEncoder);   ::Serial.print(",");
  ::Serial.print(distance1);      ::Serial.print(",");
  ::Serial.print(distance2);      ::Serial.print(",");
  ::Serial.print(distance3);
  ::Serial.println(",<Stop>;");
  ::Serial.flush();

  // Slow things down
  //
  ::delay(100);
}

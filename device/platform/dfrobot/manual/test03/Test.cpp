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
  kSEND_CMDS_END,       // Must not delete this line
};


// Message data is any ASCII bytes (0-255 value). But can't contain the field
// separator, command separator chars you decide (eg ',' and ';')
//
void available()
{
  messenger.sendCmd(kACK, "available");
  while (messenger.available())
  {
    char buf[350] = { '\0' };
    messenger.copyString(buf, 350);
    if(buf[0])
    {
      messenger.sendCmd(kACK, buf);
    }
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
  Serial.begin(9600);
  Serial.flush();

  // Make output more readable whilst debugging in Arduino Serial Monitor
  //
  messenger.print_LF_CR();

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
  messenger.feedinSerialData();
}

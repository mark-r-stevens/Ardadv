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

#include <dfrobot/MainWindow.h>

#include <QtGui/QApplication>
#include <QSettings>

#include <iostream>

int main(int argc, char *argv[])
{

  // Qt initialization
  //
  QApplication app(argc, argv);

  // Set up the default settings
  //
  QCoreApplication::setOrganizationName("RTS");
  QCoreApplication::setOrganizationDomain("redticksoftware.com");
  QCoreApplication::setApplicationName("AccViewer");

  // construct the window
  //
  ardadv::dfrobot::MainWindow iMainWindow;

  // Check arguments
  //
  if (argc != 3)
  {
    std::cerr << "Usage: DfRobot device baud" << std::endl;
    std::cerr << "\tdevice The serial port (e.g., /dev/cu.usbmodem621)" << std::endl;
    std::cerr << "\tbaud   The requested data rate (e.g., 115200)" << std::endl;
    return 0;
  }

  // Connect to the serial port
  //
  iMainWindow.open(argv[1], ::atoi(argv[2]));

  // Show the main window on the screen
  //
  iMainWindow.show();

  // Enter the event loop
  //
  return app.exec();
}

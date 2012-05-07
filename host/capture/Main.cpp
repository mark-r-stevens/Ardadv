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

#include <common/ArduinoSerial.h>

#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{

  // Check arguments
  //
  if (argc != 3)
  {
    std::cerr << "Usage: Capture device baud" << std::endl;
    std::cerr << "\tdevice The serial port (e.g., /dev/cu.usbmodem621)" << std::endl;
    std::cerr << "\tbaud   The requested data rate (e.g., 115200)" << std::endl;
    std::cerr << std::endl;
    std::cerr << "\tXbee: /dev/cu.usbserial-A800fcAr" << std::endl;
    std::cerr << "\tUSB : /dev/cu.usbmodem621" << std::endl;
    return 0;
  }

  // The serial reader
  //
  int fid = serialport_init(argv[1], ::atoi(argv[2]));

  // Open the file for export
  //
  std::ofstream ofs("Capture.txt");

  // Read and write characters
  //
  // The data read
  //
  char data[4096];

  // Keep running
  //
  while (true)
  {
    if (serialport_read_until(fid, data, ';') >= 0)
    {
      ofs << data;
      std::cout << data << std::endl;
    }
  }

  // Done
  //
  return 0;
}

# Copyright (C) 2012 Mark R. Stevens
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

## Serial upload port
#
set(ManualTest_PORT /dev/cu.usbmodem621)      
   
## Arduino Target board
#
set(ManualTest_SRCS  Test.cpp)  
set(ManualTest_LIBS  Motor Manual Vendor)
set(ManualTest_BOARD uno)              
set(ManualTest_NO_AUTOLIBS True)

##  Target generation
#
generate_arduino_firmware(ManualTest)


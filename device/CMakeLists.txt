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

## CMake module search path
#
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules) 

## Arduino Toolchain
#
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchains/Arduino.cmake)

## Minimum cmake required
#
cmake_minimum_required(VERSION 2.8)

## The default project
#
project(ArdAdvDevice C CXX)

## Require the Arduino development environment
#
find_package(Arduino 1.0 REQUIRED)
if(NOT ARDUINO_FOUND)
  message(FATAL_ERROR "Arduino not found")
endif()

## Make sure the top level directory is set up in the include path
#
include_directories(.)

## Add the subdirectory
#
add_subdirectory(sensors)


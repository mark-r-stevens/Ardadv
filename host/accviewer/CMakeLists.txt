# CMakeLists.txt for building the code for Adventures in Arduino
#
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

## Setup for Qt
#
include(${QT_USE_FILE})

## Make sure qt is in the header path
#
include_directories(${QT_INCLUDES})
include_directories(${OPENGL_INCLUDE_DIR})

## The qt files
#
QT4_WRAP_CPP(ACCVIEWER_MOC_HDRS
  Serial.h
)

## Add the executable
#
add_executable(AccViewer
  Main.cpp
  ${ACCVIEWER_MOC_HDRS}
  ${ACCVIEWER_RCC_SRCS}
)

## Add the link libraries
#
target_link_libraries(AccViewer
  ${QT_LIBRARIES}
)

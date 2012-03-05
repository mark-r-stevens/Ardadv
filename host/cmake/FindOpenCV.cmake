###########################################################
#                  Find OpenCV Library
# See http://sourceforge.net/projects/opencvlibrary/
#----------------------------------------------------------
#
## 1: Setup:
# The following variables are optionally searched for defaults
#  OpenCV_DIR:            Base directory of OpenCv tree to use.
#
## 2: Variable
# The following are set after configuration is done: 
#  
#  OpenCV_FOUND
#  OpenCV_LIBS
#  OpenCV_INCLUDE_DIR
#  OpenCV_VERSION (OpenCV_VERSION_MAJOR, OpenCV_VERSION_MINOR, OpenCV_VERSION_PATCH)
#
#
# Deprecated variable are used to maintain backward compatibility with
# the script of Jan Woetzel (2006/09): www.mip.informatik.uni-kiel.de/~jw
#  OpenCV_INCLUDE_DIRS
#  OpenCV_LIBRARIES
#  OpenCV_LINK_DIRECTORIES
# 
## 3: Version
#
# 2010/04/07 Benoit Rat, Correct a bug when OpenCVConfig.cmake is not found.
# 2010/03/24 Benoit Rat, Add compatibility for when OpenCVConfig.cmake is not found.
# 2010/03/22 Benoit Rat, Creation of the script.
#
#
# tested with:
# - OpenCV 2.1:  MinGW, MSVC2008
# - OpenCV 2.0:  MinGW, MSVC2008, GCC4
#
#
## 4: Licence:
#
# LGPL 2.1 : GNU Lesser General Public License Usage
# Alternatively, this file may be used under the terms of the GNU Lesser

# General Public License version 2.1 as published by the Free Software
# Foundation and appearing in the file LICENSE.LGPL included in the
# packaging of this file.  Please review the following information to
# ensure the GNU Lesser General Public License version 2.1 requirements
# will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
# 
#----------------------------------------------------------

## Find the config file
#
FIND_PATH(OPENCV_CONFIG
    NAMES OpenCVConfig.cmake
    HINTS /usr/local/share/OpenCV/
)
message ("OPENCV_CONFIG=${OPENCV_CONFIG}")


## When its possible to use the Config script use it.
#
if(EXISTS "${OPENCV_CONFIG}/OpenCVConfig.cmake")
      include("${OPENCV_CONFIG}/OpenCVConfig.cmake")
      set(CVLIB_SUFFIX "${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH}")
      set (OpenCV_FOUND TRUE)
endif()
##====================================================


##====================================================
## Backward compatibility
##----------------------------------------------------
if(OpenCV_FOUND)
option(OpenCV_BACKWARD_COMPA "Add some variable to make this script compatible with the other version of FindOpenCV.cmake" false)
if(OpenCV_BACKWARD_COMPA)
        find_path(OpenCV_INCLUDE_DIRS "cv.h" PATHS "${OpenCV_DIR}" PATH_SUFFIXES "include" "include/opencv" DOC "Include directory") 
        find_path(OpenCV_INCLUDE_DIR "cv.h" PATHS "${OpenCV_DIR}" PATH_SUFFIXES "include" "include/opencv" DOC "Include directory")
        set(OpenCV_LIBRARIES "${OpenCV_LIBS}" CACHE STRING "" FORCE)
endif(OpenCV_BACKWARD_COMPA)
endif(OpenCV_FOUND)
##====================================================

##====================================================
## Print message
##----------------------------------------------------
IF (OpenCV_FOUND)
   IF (NOT OpenCV_FIND_QUIETLY)
      MESSAGE(STATUS "Found OpenCV: ${OpenCV_DIR}/share/OpenCV/OpenCVConfig.cmake")
   ENDIF (NOT OpenCV_FIND_QUIETLY)
ELSE (OpenCV_FOUND)
   IF (OpenCV_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find OpenCV")
   ENDIF (OpenCV_FIND_REQUIRED)
ENDIF (OpenCV_FOUND)
##====================================================


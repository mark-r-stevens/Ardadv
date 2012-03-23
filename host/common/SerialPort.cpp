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

#include <common/SerialPort.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <errno.h>

namespace ardadv
{
  namespace common
  {

    // adrport.c - Serial Port Handler
    // Copyright MMI, MMII by Sisusypro Incorporated

    // Permission is hereby granted to freely copy,
    // modify, utilize and distribute this example in
    // whatever manner you desire without restriction.

    int OpenAdrPort(const char* sPortName)
    {
      int fd = open(sPortName, O_RDWR | O_NOCTTY);// | O_NDELAY);
      if (fd < 0)
      {
        printf("in OpenAdrPort port#=%s\n", sPortName);
        printf("open error %d %s\n", errno, strerror(errno));
      }
      else
      {
        struct termios my_termios;
        tcgetattr(fd, &my_termios);

        tcflush(fd, TCIFLUSH);

        my_termios.c_cflag = B9600 | CS8 |CREAD | CLOCAL | HUPCL;

        cfsetospeed(&my_termios, B9600);
        tcsetattr(fd, TCSANOW, &my_termios);

      }
      return fd;
    }

    int WriteAdrPort(int fd, const char* psOutput)
    {
      int iOut;
      if (fd < 1)
      {
        printf(" port is not open\n");
        return -1;
      } // end if
      iOut = write(fd, psOutput, strlen(psOutput));
      if (iOut < 0)
      {
        printf("write error %d %s\n", errno, strerror(errno));
      }
      else
      {
        printf("wrote %d chars: %s\n", iOut, psOutput);
      } // end if
      return iOut;
    } // end WriteAdrPort

    int ReadAdrPort(int fd, char* psResponse, int iMax)
    {
      int iIn;
      if (fd < 1)
      {
        printf("in ReadAdrPort iMax=%d\n", iMax);
        printf(" port is not open\n");
        return -1;
      }
      strncpy (psResponse, "N/A", iMax<4?iMax:4);
      iIn = read(fd, psResponse, iMax-1);
      if (iIn < 0)
      {
        if (errno == EAGAIN)
        {
          return 0; // assume that command generated no response
        }
        else
        {
          printf("read error %d %s\n", errno, strerror(errno));
        }
      }
      else
      {
        psResponse[iIn<iMax?iIn:iMax] = '\0';
        //printf("read %d chars: %s\n", iIn, psResponse);
      }

      return iIn;
    } // end ReadAdrPort

    void CloseAdrPort(int fd)
    {
      // you may want to restore the saved port attributes
      if (fd > 0)
      {
        close(fd);
      } // end if
    } // end CloseAdrPort

  }
}


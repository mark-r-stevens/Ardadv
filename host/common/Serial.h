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

#ifndef ardadv_common_Serial_h
#define ardadv_common_Serial_h

#include <QThread>

#include <common/ArduinoSerial.h>

#include <iostream>

namespace ardadv
{
  namespace common
  {

    //! @class Serial
    //!
    //! @brief Capture accelerometer serial traffic
    //!
    class Serial : public QThread
    {
      Q_OBJECT
    public:

      //! @brief Constructor
      //!
      //! @param[in] parent the parent widget
      //!
      inline Serial() : fd(-1)
      {
      }

      //! @brief The serial port to open
      //!
      //! @return true if port opened properly
      //!
      inline bool open(const std::string& iPort)
      {

        // Open the port
        //
        fd = serialport_init(iPort.c_str(), 115200);
        if (fd < 0)
        {
          return false;
        }

        // Done
        //
        return true;
      }

      //! @brief Start running
      //!
      inline void run()
      {

        // The data read
        //
        char data[4096];

        // Keep running
        //
        while (true)
        {
          if (serialport_read_until(fd, data, ';') >= 0)
          {
            const QString send = data;
            emit recv(send);
          }
        }
      }

    public slots:

      //! @brief Called when new data is available on the terminal
      //!
      //! @param[in] str The string read
      //
      void send(const QString& str)
      {
        serialport_write(fd, str.toStdString().c_str());
      }

    signals:

      //! @brief Emitted when new data is available on the terminal
      //!
      //! @param[in] str The string read
      //
      void recv(const QString& str);

    private:

      //! @brief Raw descriptor
      //!
      int fd;

    };
  }
}

#endif

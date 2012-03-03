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

#ifndef ardadv_accviewer_Serial_h
#define ardadv_accviewer_Serial_h

#include <QThread>

namespace ardadv
{
  namespace accviewer
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
      inline Serial()
      {
      }

      //! @brief The serial port to open
      //!
      //! @return true if port opened properly
      //!
      inline bool open()
      {
       return true;
      }

      //! @brief Start running
      //!
      inline void run()
      {
      }

    signals:

      //! @brief Emitted when new data is available on the terminal
      //!
      //! @param[in] str The string read
      //
      void line(const QString& str);

    private:

    };
  }
}

#endif
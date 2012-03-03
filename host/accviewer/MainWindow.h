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

#ifndef ardadv_accviewer_MainWindow_h
#define ardadv_accviewer_MainWindow_h

#include <QMainWindow>

namespace ardadv
{
  namespace accviewer
  {

    //! @class MainWindow
    //!
    //! @brief A simple gui to visualize serial data from an accelerometer
    //!
    class MainWindow : public QMainWindow
    {
      Q_OBJECT

    public:

      //! @brief Constructor
      //!
      //! Set up the main window and associated children widgets
      //!
      MainWindow();

    protected:

    private:

    };
  }
}

#endif

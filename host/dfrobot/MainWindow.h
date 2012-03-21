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

#ifndef ardadv_dfrobot_MainWindow_h
#define ardadv_dfrobot_MainWindow_h

#include <QDialog>
#include <QStringList>

namespace ardadv
{
  namespace common
  {
    class Serial;
  }
  namespace dfrobot
  {
    class CameraWidget;
    class ControlsWidget;

    //! @class MainWindow
    //!
    //! @brief A simple gui to control the dfrobot
    //!
    class MainWindow : public QDialog
    {
      Q_OBJECT

    public:

      //! @brief Constructor
      //!
      //! Set up the main window and associated children widgets
      //!
      MainWindow();

    public slots:

      //! @brief Called when new data is available on the terminal
      //!
      //! @param[in] str The string read
      //
      void line(const QString& str);

    private:

      //! @brief The widgets
      //!
      CameraWidget*    mCameraWidget;
      ControlsWidget*  mControlsWidget;

      //! @brief The listener for serial data
      //!
      common::Serial* mSerial;

      //! @brief The currently being parsed string
      //!
      QStringList mList;
    };
  }
}

#endif

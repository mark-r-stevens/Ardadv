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

#include <QtGui>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QMainWindow>
#include <QTextEdit>
#include <QStringList>

#include <dfrobot/MainWindow.h>
#include <dfrobot/CameraWidget.h>
#include <dfrobot/ControlsWidget.h>

#include <common/Serial.h>

#include <fstream>
#include <iostream>

namespace ardadv
{
  namespace dfrobot
  {
    MainWindow::MainWindow()
    {

      // Allocate the widgets
      //
      mCameraWidget   = new CameraWidget(this);
      mControlsWidget = new ControlsWidget(this);

      // The layout
      //
      QGridLayout *layout = new QGridLayout;
      layout->addWidget(mCameraWidget,   0, 0);
      layout->addWidget(mControlsWidget, 0, 1);
      setLayout(layout);

      // Connect the controls
      //
      connect(this, SIGNAL(enableRobotControl()), mControlsWidget, SLOT(enableRobotControl()));
      connect(this, SIGNAL(disableRobotControl()), mControlsWidget, SLOT(disableRobotControl()));

      // Create the serial reader
      //
      mSerial = new common::Serial;
      connect(mSerial,
              SIGNAL(line(const QString&)),
              this,
              SLOT(line(const QString&)));

      // Set the window title
      //
      setWindowTitle(tr("DF Robot Controller"));

      // Start the serial line running
      //
      mSerial->open("/dev/cu.usbmodem621");
      //mSerial->start();
    }
    void MainWindow::keyPressEvent(QKeyEvent* event)
    {
      if (event->key() == Qt::Key_Meta)
      {
        emit enableRobotControl();
      }
      else
      {
        QDialog::keyPressEvent(event);
      }
    }
    void MainWindow::keyReleaseEvent(QKeyEvent* event)
    {
      if (event->key() == Qt::Key_Meta)
      {
        emit disableRobotControl();
      }
      else
      {
        QDialog::keyReleaseEvent(event);
      }
    }
    void MainWindow::line(const QString& str)
    {

      //std::cout << "str=(" << str.toStdString() << std::endl;

      // Add the string to the list
      //
      mList.append(str.split(' '));

      // If there is no stop in the list, we are done
      //
      if (mList.indexOf("Stop") == -1)
      {
        return;
      }

      // Try to parse what we can
      //
      while (mList.size() > 7)
      {

        // Strip off everything until a start
        //
        while (mList.size() > 0 && (mList.first() != "Start"))
        {
          mList.pop_front();
        }

        // See if there is enough left
        //
        if (mList.size() < 7)
        {
          return;
        }

        // Get the tokens
        //
        const QString v0 = mList.takeFirst();
        const int     v1 = mList.takeFirst().toInt();
        float   v2 = mList.takeFirst().toFloat();
        float   v3 = mList.takeFirst().toFloat();
        float   v4 = mList.takeFirst().toFloat();
        const QString v5 = mList.takeFirst();

        // Check
        //
        if (v0 != "Start")
        {
          return;
        }
        if (v5 != "Stop")
        {
          return;
        }

        // Normalize
        //
        const float mag = ::sqrt(v2*v2 + v3*v3 + v4*v4);
        v2 /= mag;
        v3 /= mag;
        v4 /= mag;

        // Compute the heading
        //
        const float heading = ::atan2(v3,v2) * 180.0 / 3.14159;

        // Update the display
        //
        std::cout << "heading (" << heading << ")" << std::endl;
        mCameraWidget->setHeading(heading);
      }
    }
  }
}

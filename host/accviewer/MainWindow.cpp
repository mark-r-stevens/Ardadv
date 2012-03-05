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

#include <accviewer/MainWindow.h>
#include <accviewer/CameraWidget.h>
#include <accviewer/RawDataWidget.h>
#include <accviewer/AxisWidget.h>
#include <accviewer/Serial.h>

#include <fstream>
#include <iostream>

namespace ardadv
{
  namespace accviewer
  {
    MainWindow::MainWindow()
    {

      // The layout
      //
      QGridLayout *layout = new QGridLayout;

      // Set the central widget
      //
      mCameraWidget  = new CameraWidget(this);
      mRawDataWidget = new RawDataWidget(this);
      mAxisWidget    = new AxisWidget(this);

      // Add the raw data widget
      //
      layout->addWidget(mCameraWidget,  0, 0);
      layout->addWidget(mAxisWidget,    0, 1);
      layout->addWidget(mRawDataWidget, 1, 0, 1, 2);

      // Store the layout
      //
      setLayout(layout);

      // Create the serial reader
      //
      mSerial = new Serial;
      connect(mSerial,
              SIGNAL(line(const QString&)),
              this,
              SLOT(line(const QString&)));

      // Set the window title
      //
      setWindowTitle(tr("Accelerometer Viewer"));

      // Start the serial line running
      //
      mSerial->open("/dev/cu.usbmodem621");
      mSerial->start();
    }
    void MainWindow::line(const QString& str)
    {

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
        const float   v2 = mList.takeFirst().toFloat();
        const float   v3 = mList.takeFirst().toFloat();
        const float   v4 = mList.takeFirst().toFloat();
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

        // Update the display
        //
        mRawDataWidget->add(v2, v3, v4);
        mAxisWidget->add(v2, v3, v4);
      }
    }
  }
}

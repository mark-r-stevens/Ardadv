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
      //mCameraWidget   = new CameraWidget(this);
      mControlsWidget = new ControlsWidget(this);

      // The layout
      //
      QGridLayout *layout = new QGridLayout;
      //layout->addWidget(mCameraWidget,   0, 0);
      layout->addWidget(mControlsWidget, 0, 1);
      setLayout(layout);

      // Connect the controls
      //
      connect(this, SIGNAL(enableRobotControl()), mControlsWidget, SLOT(enableRobotControl()));
      connect(this, SIGNAL(disableRobotControl()), mControlsWidget, SLOT(disableRobotControl()));

      // Create the serial reader/writer
      //
      mSerial = new common::Serial;
      connect(mSerial,
              SIGNAL(recv(const QString&)),
              this,
              SLOT(recv(const QString&)));

      // Connect the output
      //
      connect(mControlsWidget,
              SIGNAL(changeRobotSpeed(const QString&)),
              mSerial,
              SLOT(send(const QString&)));

      // Set the window title
      //
      setWindowTitle(tr("DF Robot Controller"));

    }
    bool MainWindow::open(const std::string& port, int baud)
    {
      mSerial->open(port, baud);
      mSerial->start();
      return true;
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
    void MainWindow::recv(const QString& str)
    {

      // Log file of valid robot messages
      //
      static std::ofstream ofs("Data.csv");

      // Add the string to the list
      //
      mList.append(str.split(','));

      // If there is no stop in the list, we are done
      //
      if (mList.indexOf("<Stop>;") == -1)
      {
        return;
      }

      // Try to parse what we can
      //
      while (mList.size() > 10)
      {

        // Strip off everything until a start
        //
        while (mList.size() > 0 && (mList.first() != "<Start>"))
        {
          std::cout << "no start" << std::endl;
          mList.pop_front();
        }

        // See if there is enough left
        //
        if (mList.size() < 10)
        {
          std::cout << "too few things(" << mList.size() << ")" << std::endl;
          return;
        }

        // Get the tokens
        //
        const QString start  = mList.takeFirst();           // 0
        float   leftSpeed    = mList.takeFirst().toFloat(); // 1
        float   rightSpeed   = mList.takeFirst().toFloat(); // 2
        float   leftEncoder  = mList.takeFirst().toFloat(); // 3
        float   rightEncoder = mList.takeFirst().toFloat(); // 4
        float   distance1    = mList.takeFirst().toFloat(); // 5
        float   distance2    = mList.takeFirst().toFloat(); // 6
        float   distance3    = mList.takeFirst().toFloat(); // 7
        const QString stop   = mList.takeFirst();           // 8

        std::cout << "tokens=(" << start.toStdString() << ", " << stop.toStdString() << ")" << std::endl;

        // Check
        //
        if (start != "<Start>")
        {
          return;
        }
        if (stop != "<Stop>;")
        {
          return;
        }
        std::cout << "Parsing" << std::endl;

        // Output the values
        //
        ofs << leftSpeed    << ",";
        ofs << rightSpeed   << ",";
        ofs << leftEncoder  << ",";
        ofs << rightEncoder << ",";
        ofs << distance1    << ",";
        ofs << distance2    << ",";
        ofs << distance3    << std::endl;
      }
    }
  }
}

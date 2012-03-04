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

#include <accviewer/MainWindow.h>
#include <accviewer/CentralWidget.h>
#include <accviewer/Serial.h>

#include <ofstream>

namespace ardadv
{
  namespace accviewer
  {
    MainWindow::MainWindow()
    {

      // Set the central widget
      //
      mCentralWidget = new CentralWidget(this);
      setCentralWidget(mCentralWidget);

      // Create the controls docking area
      //
      QDockWidget *qDockWidget = new QDockWidget(tr("Raw input"), this);
      qDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
      mTextEdit = new QTextEdit(qDockWidget);
      qDockWidget->setWidget(mTextEdit);
      addDockWidget(Qt::BottomDockWidgetArea, qDockWidget);

      // Create the serial reader
      //
      mSerial = new Serial;
      connect(mSerial,
              SIGNAL(line(const QString&)),
              this,
              SLOT(line(const QString&)));

      // Create the status bar
      //
      statusBar()->showMessage(tr("Ready"));

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
      QTextCursor cursor(mTextEdit->textCursor());
      cursor.insertText(str);
      static std::ofstream out("Values");
      out << str.toStdString() << std::endl;
    }
  }
}

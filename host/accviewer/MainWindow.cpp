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

#include <accviewer/MainWindow.h>

namespace ardadv
{
  namespace accviewer
  {
    MainWindow::MainWindow()
    {

      // Grab keyboard events
      //
      setFocusPolicy(Qt::StrongFocus);

      // Create the controls docking area
      //
      QDockWidget *qDockWidget = new QDockWidget(tr("Raw input"), this);
      qDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
      //mControls = new Controls(qDockWidget);
      //qDockWidget->setWidget(mControls);
      qDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
      addDockWidget(Qt::BottomDockWidgetArea, qDockWidget);

      // Set the central widget
      //
      //mCentralWidget = new CentralWidget;
      //setCentralWidget(mCentralWidget);

      // Create the file menu
      //
      QAction* qAction = new QAction(tr("&Quit"), this);
      qAction->setShortcuts(QKeySequence::Quit);
      qAction->setStatusTip(tr("Quit the application"));
      connect(qAction, SIGNAL(triggered()), this, SLOT(close()));
      QMenu *qMenu = menuBar()->addMenu(tr("&File"));
      qMenu->addAction(qAction);

      // Create the status bar
      //
      statusBar()->showMessage(tr("Ready"));

      // Unified title and toolbar
      //
      setUnifiedTitleAndToolBarOnMac(true);

      // Set the window title
      //
      setWindowTitle(tr("Accelerometer Viewer"));

    }
  }
}

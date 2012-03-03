// Copyright (C) 2011 Systems Technology Research, LLC.
//  http://www.systemstechnologyresearch.com
//
//  Usage of this software is governed by the license.txt file
//  accompanying the distribution. By downloading, copying, installing
//  or using the software you agree to this license.
//
//  You may copy and distribute the Software in unmodified form
//  provided that the entire package, including - but not restricted
//  to - copyright, trademark notices and disclaimers, as released by
//  the initial developer of the Software, is distributed. You may
//  make modifications to the Software and distribute your
//  modifications, in a form that is separate from the Software, such
//  as patches.
//
//  In no event shall the initial developers or copyright holders be
//  liable for any damages whatsoever, including - but not restricted
//  to - lost revenue or profits or other direct, indirect, special,
//  incidental or consequential damages, even if they have been
//  advised of the possibility of such damages, except to the extent
//  invariable law, if any, provides otherwise.
//
//  The Software and this license document are provided AS IS with NO
//  WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN,
//  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

#include <util/viewer/MainWindow.h>

#include <QtGui/QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{

  // Qt initialization
  //
  QApplication app(argc, argv);

  // Set up the default settings
  //
  QCoreApplication::setOrganizationName("STR");
  QCoreApplication::setOrganizationDomain("systemstechnologyresearch.com");
  QCoreApplication::setApplicationName("Viewer");

  // construct the video player class
  //
  str::util::viewer::MainWindow iMainWindow;

  // Show the main window on the screen
  //
  iMainWindow.show();

  // Enter the event loop
  //
  return app.exec();
}

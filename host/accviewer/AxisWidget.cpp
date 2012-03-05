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

#include <accviewer/AxisWidget.h>

namespace ardadv
{
  namespace accviewer
  {
    AxisWidget::AxisWidget(QWidget *parent) : QGLWidget(parent)
    {
    }
    void AxisWidget::add(float x, float y, float z)
    {
      Rx = x;
      Ry = y;
      Rz = z;
      glDraw();
    }
    void AxisWidget::initializeGL()
    {

      // Set the clear color
      //
      ::glClearColor(1, 1, 1, 1);

      // Disable a bunch of tests that will slow things down
      //
      ::glEnable(GL_DEPTH_TEST);
      ::glDisable(GL_CULL_FACE);
      ::glDisable(GL_LIGHTING);

    }
    void AxisWidget::paintGL()
    {

      // Clear the screen
      //
      ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Set the viewport
      //
      ::glViewport(0, 0, width(), height());

      // Set the projection matrix
      //
      ::glMatrixMode (GL_PROJECTION);
      ::glLoadIdentity();
      ::glOrtho(-1, 1, -1, 1, -1, 1);

      // Set the modelview matrix
      //
      ::glMatrixMode(GL_MODELVIEW);
      ::glLoadIdentity();
      ::glRotatef(45, 1, 0, 0);
      ::glRotatef(45, 0, 1, 0);

      // Draw +x
      //
      ::glColor3f(1,0,0);
      ::glBegin(GL_LINES);
      ::glVertex3f(0, 0, 0);
      ::glVertex3f(1, 0, 0);
      ::glEnd();

      // Draw +y
      //
      ::glColor3f(0,1,0);
      ::glBegin(GL_LINES);
      ::glVertex3f(0, 0, 0);
      ::glVertex3f(0, 1, 0);
      ::glEnd();

      // Draw +z
      //
      ::glColor3f(0,0,1);
      ::glBegin(GL_LINES);
      ::glVertex3f(0, 0, 0);
      ::glVertex3f(0, 0, 1);
      ::glEnd();

      // Draw -x
      //
      ::glColor3f(1,0,0);
      ::glLineStipple(1, 0x3F07);
      ::glEnable(GL_LINE_STIPPLE);
      ::glBegin(GL_LINES);
      ::glVertex3f( 0, 0, 0);
      ::glVertex3f(-1, 0, 0);
      ::glEnd();

      // Draw -y
      //
      ::glColor3f(0,1,0);
      ::glBegin(GL_LINES);
      ::glVertex3f(0,  0, 0);
      ::glVertex3f(0, -1, 0);
      ::glEnd();

      // Draw -z
      //
      ::glColor3f(0,0,1);
      ::glBegin(GL_LINES);
      ::glVertex3f(0, 0,  0);
      ::glVertex3f(0, 0, -1);
      ::glEnd();
      ::glDisable(GL_LINE_STIPPLE);

      // Draw R
      //
      ::glColor3f(0,0,0);
      ::glBegin(GL_LINES);
      ::glVertex3f(0, 0, 0);
      ::glVertex3f(Rx, Ry, Rz);
      ::glEnd();

    }
  }
}

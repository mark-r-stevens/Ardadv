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

#include <dfrobot/ControlsWidget.h>

#include <iostream>

namespace ardadv
{
  namespace dfrobot
  {
    ControlsWidget::ControlsWidget(QWidget *parent)
    : QGLWidget(parent)
    , mMouseX(0)
    , mMouseY(0)
    , mEnabled(false)
    {
      setMouseTracking(true);
    }
    void ControlsWidget::mouseMoveEvent(QMouseEvent * event)
    {

      // The position in normalized pixels
      //
      const float x = event->x() / static_cast<float>(width());
      const float y = 1.0 - event->y() / static_cast<float>(height());

      // rescale to -1 to 1
      //
      process(2 * x - 1, 2 * y - 1);

    }
    void ControlsWidget::process(float iMouseX, float iMouseY)
    {

      // Store the new mouse location
      //
      mMouseX = iMouseX;
      mMouseY = iMouseY;

      // Format into a string for transmission
      //
      const QString message = QString("M %1 %2\n").arg(static_cast<int>(iMouseX * 200)).arg(static_cast<int>(iMouseY * 200));

      // Send the message
      //
      if (mEnabled)
      {
        emit changeRobotSpeed(message);
      }

      // Redraw
      //
      glDraw();
    }
    void ControlsWidget::initializeGL()
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
    void ControlsWidget::enableRobotControl()
    {
      mEnabled = true;
      process(mMouseX, mMouseY);
    }
    void ControlsWidget::disableRobotControl()
    {
      const QString message = "M 0 0\n";
      emit changeRobotSpeed(message);
      mEnabled = false;
      glDraw();
    }
    void ControlsWidget::paintGL()
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

      // Draw the grid
      //
      drawGrid();

      // Draw the mouse event
      //
      drawMouse();

    }
    void ControlsWidget::drawGrid() const
    {

      // Vertical lines
      //
      ::glLineStipple(1, 0xAAAA);
      ::glEnable(GL_LINE_STIPPLE);
      :: glColor3f(0.25f, 0.25f, 0.25f);
      ::glLineWidth(1);
      ::glBegin(GL_LINES);
      for (float x = -1; x <= 1; x += 0.1)
      {
        ::glVertex2f(x, -1);
        ::glVertex2f(x,  1);
        ::glVertex2f(-1, x);
        ::glVertex2f(+1, x);
      }
      ::glEnd();

      // Draw the dark center lines
      //
      ::glDisable(GL_LINE_STIPPLE);
      :: glColor3f(0, 0, 0);
      ::glBegin(GL_LINES);
      ::glLineWidth(3);
      ::glVertex2f(0, -1);
      ::glVertex2f(0,  1);
      ::glVertex2f(-1, 0);
      ::glVertex2f(+1, 0);
      ::glEnd();

    }
    void ControlsWidget::drawMouse() const
    {
      ::glColor3f(1,0,0);
      ::glPointSize(5);
      ::glBegin(GL_POINTS);
      if (mEnabled)
      {
        ::glVertex2f(mMouseX, mMouseY);
      }
      else
      {
        ::glVertex2f(0, 0);
      }
      ::glEnd();
    }
  }
}

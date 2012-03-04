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

#include <accviewer/RawDataWidget.h>

#include <iostream>

namespace ardadv
{
  namespace accviewer
  {
    RawDataWidget::RawDataWidget(QWidget *parent) : QGLWidget(parent)
    {
    }
    void RawDataWidget::add(float x, float y, float z)
    {
      std::cout << "RawDataWidget::add(" << x << "," << y << "," << z << ")" << std::endl;
      Rx.push_back(x);
      Ry.push_back(y);
      Rz.push_back(z);
      while (Rx.size() > 1000)
      {
        Rx.pop_front();
        Ry.pop_front();
        Rz.pop_front();
      }
      glDraw();
    }
    void RawDataWidget::initializeGL()
    {

      // Set the clear color
      //
      ::glClearColor(1, 1, 1, 1);

      // Disable a bunch of tests that will slow things down
      //
      ::glDisable(GL_DEPTH_TEST);
      ::glDisable(GL_CULL_FACE);
      ::glDisable(GL_LIGHTING);

    }
    void RawDataWidget::paintGL()
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
      ::glOrtho(0, width(), 0, height(), -1, 1);

      // Set the modelview matrix
      //
      ::glMatrixMode(GL_MODELVIEW);
      ::glLoadIdentity();

      // Account for scale into the window
      //
      const float s1 = height() / 4;
      const float s2 = height() / 2;

      // Draw x
      //
      ::glColor3f(1,0,0);
      std::list<float>::const_iterator curr = Rx.begin();
      std::list<float>::const_iterator end  = Rx.end();
      ::glBegin(GL_LINE_STRIP);
      for (int t = 0; curr != end; ++curr, ++t)
      {
        const float val = *curr;
        ::glVertex2i(t, val * s2 + s1);
      }
      ::glEnd();

      // Draw y
      //
      ::glColor3f(0,1,0);
      curr = Ry.begin();
      end  = Ry.end();
      ::glBegin(GL_LINE_STRIP);
      for (int t = 0; curr != end; ++curr, ++t)
      {
        const float val = *curr;
        ::glVertex2i(t, val * s2 + s1);
      }
      ::glEnd();

      // Draw z
      //
      ::glColor3f(0,0,1);
      curr = Rz.begin();
      end  = Rz.end();
      ::glBegin(GL_LINE_STRIP);
      for (int t = 0; curr != end; ++curr, ++t)
      {
        const float val = *curr;
        ::glVertex2i(t, val * s2 + s1);
      }
      ::glEnd();

    }
  }
}

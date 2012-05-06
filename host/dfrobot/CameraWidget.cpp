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

#include <dfrobot/CameraWidget.h>

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace ardadv
{
  namespace dfrobot
  {
    CameraWidget::CameraWidget(QWidget *parent)
    : QGLWidget(parent)
    , mHeading(0)
    {

      // Set up the capture device
      //
      camera = new Camera(this);

      // connect
      //
      connect(camera, SIGNAL(send(QImage)), this, SLOT(recv(QImage)));

      // Start the thread running
      //
      camera->start();

    }
    CameraWidget::~CameraWidget()
    {
    }
    void CameraWidget::recv(QImage qimg)
    {

      // Convert the image to opengl format
      //
      glImage = QGLWidget::convertToGLFormat(qimg);

      // Setup the texture in memory
      //
      ::glBindTexture(GL_TEXTURE_2D, mTextureId);
      ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      ::glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     glImage.width(),
                     glImage.height(),
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     NULL);
      ::glTexSubImage2D(GL_TEXTURE_2D,
                        0,
                        0,
                        0,
                        glImage.width(),
                        glImage.height(),
                        GL_RGBA,
                        GL_UNSIGNED_BYTE,
                        (GLvoid*)glImage.bits());

      // Redraw the screen
      //
      glDraw();

    }
    void CameraWidget::initializeGL()
    {

      // Set the clear color
      //
      ::glClearColor(0, 0, 0.5, 1.0);

      // Disable a bunch of tests that will slow things down
      //
      ::glDisable(GL_DEPTH_TEST);
      ::glDisable(GL_CULL_FACE);
      ::glDisable(GL_LIGHTING);

      // Initialize the texture
      //
      ::glEnable(GL_TEXTURE_2D);
      ::glGenTextures(1, &mTextureId);
      ::glBindTexture(GL_TEXTURE_2D, mTextureId);
      ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      ::glDisable(GL_TEXTURE_2D);

    }
    void CameraWidget::paintGL()
    {

      // Clear the screen
      //
      ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // If the image is empty, we are done
      //
      if (glImage.isNull())
      {
        return;
      }

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
      const float wRatio = static_cast<float>(width()) / glImage.width();
      const float hRatio = static_cast<float>(height()) / glImage.height();
      ::glScalef(wRatio, hRatio, 1);

      // Draw the image as a textured quad
      //
      ::glColor3f(1,1,1);
      ::glEnable(GL_TEXTURE_2D);
      ::glBindTexture(GL_TEXTURE_2D, mTextureId);
      ::glBegin(GL_QUADS);
      {
        ::glTexCoord2i(0, 0); ::glVertex2i(              0, 0);
        ::glTexCoord2i(0, 1); ::glVertex2i(              0, glImage.height());
        ::glTexCoord2i(1, 1); ::glVertex2i(glImage.width(), glImage.height());
        ::glTexCoord2i(1, 0); ::glVertex2i(glImage.width(), 0);
      }
      ::glEnd();
      ::glDisable(GL_TEXTURE_2D);

      // Draw a circle
      //
      ::glColor3f(1,1,1);
      ::glBegin(GL_LINE_LOOP);
      for (int i = 0; i < 360; i += 10)
      {
        const float ang = i * 3.14159 / 180.0;
        const float x = 30 * ::cos(ang) + glImage.width() - 30;
        const float y = 30 * ::sin(ang) + glImage.height() - 30;
        ::glVertex2f(x,y);
      }
      ::glEnd();

      // Mark up
      //
      renderText(width() - 27, 10, "N");
      renderText(width() -  8, 30, "E");
      renderText(width() - 42, 30, "W");
      renderText(width() - 27, 45, "S");

      // Draw the compass arrow
      //
      ::glColor3f(1,0,0);
      ::glBegin(GL_LINES);
      const float ang = mHeading * 3.14159 / 180.0;
      const float x1 = glImage.width() - 30;
      const float y1 = glImage.height() - 30;
      const float x2 = 30 * ::cos(ang) + x1;
      const float y2 = 30 * ::sin(ang) + y1;
      ::glVertex2f(x1,y1);
      ::glVertex2f(x2,y2);
      ::glEnd();

    }
  }
}

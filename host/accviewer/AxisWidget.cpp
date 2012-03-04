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

#include <iostream>

#define EPSILON 0.000001

#define CROSS(dest, v1, v2){                 \
    dest[0] = v1[1] * v2[2] - v1[2] * v2[1]; \
    dest[1] = v1[2] * v2[0] - v1[0] * v2[2]; \
    dest[2] = v1[0] * v2[1] - v1[1] * v2[0];}

#define DOT(v1, v2) (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2])

#define SUB(dest, v1, v2){       \
    dest[0] = v1[0] - v2[0]; \
    dest[1] = v1[1] - v2[1]; \
    dest[2] = v1[2] - v2[2];}

namespace ardadv
{
  namespace accviewer
  {
    namespace
    {
      /*
       * A function for creating a rotation matrix that rotates a vector called
       * "from" into another vector called "to".
       * Input : from[3], to[3] which both must be *normalized* non-zero vectors
       * Output: mtx[3][3] -- a 3x3 matrix in colum-major form
       * Authors: Tomas Mšller, John Hughes
       *          "Efficiently Building a Matrix to Rotate One Vector to Another"
       *          Journal of Graphics Tools, 4(4):1-4, 1999
       */
      void fromToRotation(float from[3], float to[3], float mtx[3][3])
      {
        float v[3];
        float e, h, f;

        CROSS(v, from, to);
        e = DOT(from, to);
        f = (e < 0)? -e:e;
        if (f > 1.0 - EPSILON)     /* "from" and "to"-vector almost parallel */
        {
          float u[3], v[3]; /* temporary storage vectors */
          float x[3];       /* vector most nearly orthogonal to "from" */
          float c1, c2, c3; /* coefficients for later use */
          int i, j;

          x[0] = (from[0] > 0.0)? from[0] : -from[0];
          x[1] = (from[1] > 0.0)? from[1] : -from[1];
          x[2] = (from[2] > 0.0)? from[2] : -from[2];

          if (x[0] < x[1])
          {
            if (x[0] < x[2])
            {
              x[0] = 1.0; x[1] = x[2] = 0.0;
            }
            else
            {
              x[2] = 1.0; x[0] = x[1] = 0.0;
            }
          }
          else
          {
            if (x[1] < x[2])
            {
              x[1] = 1.0; x[0] = x[2] = 0.0;
            }
            else
            {
              x[2] = 1.0; x[0] = x[1] = 0.0;
            }
          }

          u[0] = x[0] - from[0]; u[1] = x[1] - from[1]; u[2] = x[2] - from[2];
          v[0] = x[0] - to[0];   v[1] = x[1] - to[1];   v[2] = x[2] - to[2];

          c1 = 2.0 / DOT(u, u);
          c2 = 2.0 / DOT(v, v);
          c3 = c1 * c2  * DOT(u, v);

          for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
              mtx[i][j] =  - c1 * u[i] * u[j]
                                           - c2 * v[i] * v[j]
                                                           + c3 * v[i] * u[j];
            }
            mtx[i][i] += 1.0;
          }
        }
        else  /* the most common case, unless "from"="to", or "from"=-"to" */
        {
          /* ...otherwise use this hand optimized version (9 mults less) */
          float hvx, hvz, hvxy, hvxz, hvyz;
          /* h = (1.0 - e)/DOT(v, v); old code */
          h = 1.0/(1.0 + e);      /* optimization by Gottfried Chen */
          hvx = h * v[0];
          hvz = h * v[2];
          hvxy = hvx * v[1];
          hvxz = hvx * v[2];
          hvyz = hvz * v[1];
          mtx[0][0] = e + hvx * v[0];
          mtx[0][1] = hvxy - v[2];
          mtx[0][2] = hvxz + v[1];

          mtx[1][0] = hvxy + v[2];
          mtx[1][1] = e + h * v[1] * v[1];
          mtx[1][2] = hvyz - v[0];

          mtx[2][0] = hvxz - v[1];
          mtx[2][1] = hvyz + v[0];
          mtx[2][2] = e + hvz * v[2];
        }
      }
      void toOpengl(float in[3][3], float out[16])
      {
        out[0] = in[0][0]; out[4] = in[0][1]; out[ 8] = in[0][2]; out[12] = 0;
        out[1] = in[1][0]; out[5] = in[1][1]; out[ 9] = in[1][2]; out[13] = 0;
        out[2] = in[2][0]; out[6] = in[2][1]; out[10] = in[2][2]; out[14] = 0;
        out[3] =        0; out[7] =        0; out[11] =        0; out[15] = 1;
      }
    }
    AxisWidget::AxisWidget(QWidget *parent) : QGLWidget(parent)
    {
    }
    void AxisWidget::add(float x, float y, float z)
    {
      std::cout << "AxisWidget::add(" << x << "," << y << "," << z << ")" << std::endl;
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

      // Build the transformation
      //
      float mtx[3][3];
      float from[3] = {1, 0, 0};
      float to[3]  = {Rx, Ry, Rz};
      fromToRotation(from, to, mtx);

      // Convert to opengl format
      //
      float oglmat[16];
      toOpengl(mtx, oglmat);
      //::glLoadMatrixf(oglmat);

      // Draw x
      //
      ::glColor3f(1,0,0);
      ::glBegin(GL_LINES);
      ::glVertex3f(0, 0, 0);
      ::glVertex3f(1, 0, 0);
      ::glEnd();

      // Draw y
      //
      ::glColor3f(0,1,0);
      ::glBegin(GL_LINES);
      ::glVertex3f(0, 0, 0);
      ::glVertex3f(0, 1, 0);
      ::glEnd();

      // Draw z
      //
      ::glColor3f(0,0,1);
      ::glBegin(GL_LINES);
      ::glVertex3f(0, 0, 0);
      ::glVertex3f(0, 0, 1);
      ::glEnd();

    }
  }
}

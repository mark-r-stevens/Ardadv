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

#ifndef ardadv_accviewer_AxisWidget_h
#define ardadv_accviewer_AxisWidget_h

#include <QtGui>
#include <QtOpenGL>

namespace ardadv
{
  namespace accviewer
  {

    //! @class AxisWidget
    //!
    //! @brief The opengl rendering surface to draw the frame
    //!
    class AxisWidget : public QGLWidget
    {
      Q_OBJECT

    public:

      //! @brief Constructor
      //!
      //! @param[in] parent the parent widget
      //!
      AxisWidget(QWidget *parent = 0);

      //! @brief Provide a size hint
      //!
      //! @return the size hint
      //!
      inline virtual QSize sizeHint() const
      {
        return QSize(640, 480);
      }

      //! @brief Provide a size hint
      //!
      //! @return the size hint
      //!
      inline virtual QSize minimumSizeHint() const
      {
        return QSize(640, 480);
      }

      //! @brief Add a measurement
      //!
      //! @param[in] x The first value
      //! @param[in] y The first value
      //! @param[in] z The first value
      //!
      void add(float x, float y, float z);

    protected:

      //! @brief Initialize opengl for rendering
      //!
      virtual void initializeGL();

      //! @brief Render the screen
      //!
      virtual void paintGL();

    private:

      //! @brief The values to draw
      //!
      float Rx;
      float Ry;
      float Rz;

    };
  }
}

#endif

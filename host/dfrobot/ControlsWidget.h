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

#ifndef ardadv_dfrobot_ControlsWidget_h
#define ardadv_dfrobot_ControlsWidget_h

#include <QtGui>
#include <QtOpenGL>

namespace ardadv
{
  namespace dfrobot
  {

    //! @class ControlsWidget
    //!
    //! @brief The control widget
    //!
    class ControlsWidget : public QGLWidget
    {
      Q_OBJECT

    public:

      //! @brief Constructor
      //!
      //! @param[in] parent the parent widget
      //!
      ControlsWidget(QWidget *parent = 0);

      //! @brief Provide a size hint
      //!
      //! @return the size hint
      //!
      inline virtual QSize sizeHint() const
      {
        return QSize(360, 360);
      }

      //! @brief Provide a size hint
      //!
      //! @return the size hint
      //!
      inline virtual QSize minimumSizeHint() const
      {
        return QSize(360, 360);
      }

    protected:

      //! @brief Initialize opengl for rendering
      //!
      virtual void initializeGL();

      //! @brief Render the screen
      //!
      virtual void paintGL();

      //! @brief The mouse position
      //!
      //! @param[in] event The event
      //!
      virtual void mouseMoveEvent(QMouseEvent * event);

      //! @brief Draw the grid
      //!
      void drawGrid() const;

      //! @brief Draw the mouse position
      //!
      void drawMouse() const;

    private:

      //! @brief The mouse position
      //!
      float mMouseX;

      //! @brief The mouse position
      //!
      float mMouseY;

    };
  }
}

#endif

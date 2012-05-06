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

#ifndef ardadv_dfrobot_Camera_h
#define ardadv_dfrobot_Camera_h

#include <QThread>
#include <QImage>
#include <QTimer>

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

namespace ardadv
{
  namespace dfrobot
  {

    //! @class Camera
    //!
    //! @brief Capture imagery from a camera, send out a signal
    //!
    class Camera : public QThread
    {
      Q_OBJECT
    public:

      //! @brief Constructor
      //!
      //! @param[in] parent the parent widget
      //!
      Camera(QObject *parent = 0) : QThread(parent)
      {
        capture = ::cvCaptureFromCAM(CV_CAP_ANY);
        if ( !capture )
        {
          std::cerr << "ERROR: capture is NULL\n";
        }
      }

      //! @brief Destructor
      //!
      ~Camera()
      {
        ::cvReleaseCapture(&capture);
      }

    public slots:

      //! @brief Start running, fetch image, drop frames, resize, send signal
      //!
      inline void run()
      {

        // Keep running
        //
        for (int count = 0; true; ++count)
        {

          // Grab the frame
          //
          ::cvGrabFrame(capture);

          // Decide to drop
          //
          if ((count % 5) != 0)
          {
            continue;
          }

          // Grab a frame
          //
          IplImage* frame = ::cvRetrieveFrame(capture);

          // Resize and convert to a QImage to send
          //
          QImage qimg = QImage((const uchar*)frame->imageData,
                               frame->width,
                               frame->height,
                               frame->widthStep,
                               QImage::Format_RGB888).scaled(320,240).rgbSwapped();

          // Send
          //
          emit send(qimg);
        }
      }

    signals:

      //! @brief Emitted when a new image is available
      //!
      //! @param[in] qimg The image read
      //
      void send(QImage qimg);

    private:

      //! @brief The camera image
      //!
      CvCapture* capture;

    };
  }
}

#endif

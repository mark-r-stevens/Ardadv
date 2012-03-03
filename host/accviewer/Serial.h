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

#ifndef str_interfaces_video_mosaic_Subscriber_h
#define str_interfaces_video_mosaic_Subscriber_h

#include <interfaces/video/mosaic/Decoder.h>

#include <zmq.hpp>

#include <QThread>
#include <QMutex>

#include <iostream>

namespace str
{
  namespace interfaces
  {
    namespace video
    {
      namespace mosaic
      {

        //! @class Subscriber
        //!
        //! @ingroup mosaic
        //!
        //! @brief Catch and cache the zmq traffic
        //!
        template<typename T>class Subscriber : public QThread
        {
        public:

          //! @brief Constructor
          //!
          //! @param[in] iContext The context for creating the subscriber
          //!
          inline Subscriber(zmq::context_t& iContext) : mOk(true), mSocket(iContext, ZMQ_SUB), mValid(false)
          {
          }

          //! @brief Bind to the address and topic
          //!
          //! @param[in] address The address
          //! @param[in] topic   The topic
          //!
          //! @return true if connected properly
          //!
          inline bool open(const std::string& address, const std::string& topic)
          {
            try
            {
              mSocket.connect(address.c_str());
              mSocket.setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());
            }
            catch(...)
            {
              return false;
            }
            return true;
          }

          //! @brief Start running
          //!
          inline void run()
          {
            Decoder<T> decoder;
            zmq::message_t msg;
            while (keepRunning())
            {
              mSocket.recv(&msg);
              QMutexLocker locker(&mMutex);
              mValid = decoder.parse((const char*)(msg.data()), msg.size(), mData);
            }
          }

          //! @brief Copy out the last message received
          //!
          //! @param[in] iData The input data
          //!
          inline void copy(T& iData)
          {
            QMutexLocker locker(&mMutex);
            iData = mData;
          }

          //! @brief Tell the filter to stop
          //!
          inline void stop()
          {
            QMutexLocker locker(&mMutex);
            mOk = false;
          }

        protected:

          //! @brief Indicates the filter should keep running
          //!
          //! @return true if ok to keep running
          //!
          inline bool keepRunning() const
          {
            QMutexLocker locker(&mMutex);
            return mOk;
          }

        private:

          //! @brief Mutex for the running flag
          //!
          mutable QMutex mMutex;

          //! @brief True if keep running
          //!
          bool mOk;

          //! @brief The context
          //!
          zmq::socket_t mSocket;

          //! @brief Raw message data
          //!
          T mData;

          //! @brief True if data is valid
          //!
          bool mValid;
        };
      }
    }
  }
}

#endif

/*
 * Artemis HTTPD Library
 * A lightweight C++ library to add web server capabilities to an application.
 * Copyright (C) 2007 Andreas Buechele
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef ARTEMIS_UTIL_THREAD_HH
#define ARTEMIS_UTIL_THREAD_HH

#include <pthread.h>

namespace artemis
{
  namespace util
  {
    class Thread
    {
    public:
      Thread();

      virtual ~Thread()
      {
      }

    protected:
      virtual void * run() = 0;

      void start();

    private:
      pthread_t _thread;

      static void* thread_call(artemis::util::Thread * _this) 
      { 
	pthread_exit(_this->run());  
	return 0; 
      }
    };
  }
}

#endif

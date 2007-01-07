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

extern "C"
{
  typedef void * (*thread_fct)(void *);
}

namespace artemis
{
  namespace util
  {
    class Thread
    {
    public:
      Thread()
	: _thread(0)
      {
      }

      virtual ~Thread()
      {
      }

    protected:
      virtual void * run() = 0;

      void start()
      {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_create(&_thread, &attr, (thread_fct) thread_call, this);

	pthread_attr_destroy(&attr);
      }

    private:
      pthread_t _thread;

      static void* thread_call(Thread * _this) 
      { 
	pthread_exit(_this->run());  
	return 0; 
      }
    };
  }
}

#endif

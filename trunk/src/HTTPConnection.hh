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

#ifndef ARTEMIS_HTTPD_HTTPCONNECTION_HH
#define ARTEMIS_HTTPD_HTTPCONNECTION_HH

#include <string>
#include <iostream>
#include <arpa/inet.h>

#include "Thread.hh"
#include "HTTPRequest.hh"
#include "HTTPContentManager.hh"

namespace artemis
{
  namespace httpd
  {
    class HTTPConnection : public artemis::util::Thread
    {
    public:
      HTTPConnection(int fd, artemis::httpd::HTTPContentManager * contentManager);
      ~HTTPConnection();

    protected:
      void * run();

    private:
      int _socketfd;
      artemis::httpd::HTTPContentManager * _contentManager;
      
      artemis::httpd::HTTPRequest * receiveRequest();
    };
  }
}

#endif


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

#ifndef ARTEMIS_HTTPD_HTTPSERVER_HH
#define ARTEMIS_HTTPD_HTTPSERVER_HH

#include <string>

#include <arpa/inet.h>

#include "HTTPContentManager.hh"

namespace artemis
{
  namespace httpd
  {
    class HTTPServer
    {
    public:
      HTTPServer(int port);
      ~HTTPServer();
      
      void start();
      
      void addFileContent(std::string request, std::string filename);
      void addDirectoryContent(std::string request, std::string directory);
      void addContentHandler(std::string request, artemis::httpd::HTTPContentHandler * contentHandler);
      
    private:
      int _socketfd;
      int _yes;
      struct sockaddr_in _local_in_addr;

      artemis::httpd::HTTPContentManager * _contentManager;
    };
  }
}

#endif


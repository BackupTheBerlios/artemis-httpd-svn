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

#ifndef HTTPD_HTTPCONTENTMANAGER_HH
#define HTTPD_HTTPCONTENTMANAGER_HH

#include "HTTPRequest.hh"
#include "HTTPResponse.hh"

#include <map>

namespace HTTPD
{
  class HTTPContentManager
  {
  public:
    HTTPContentManager();
    ~HTTPContentManager();

    void addFileContent(std::string request, std::string filename);
    void addDirectoryContent(std::string request, std::string directory);
    void addDynamicContent(std::string request);

    HTTPD::HTTPResponse * handleRequest(HTTPD::HTTPRequest * request);

  private:
    std::map<std::string, std::string> * _contentMap;
  };
}

#endif


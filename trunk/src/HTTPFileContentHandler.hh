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

#ifndef ARTEMIS_HTTPD_FILECONTENTHANDLER_HH
#define ARTEMIS_HTTPD_FILECONTENTHANDLER_HH

#include "HTTPContentHandler.hh"

namespace artemis
{
  namespace httpd
  {
    class HTTPFileContentHandler : public artemis::httpd::HTTPContentHandler
    {
    public:
      HTTPFileContentHandler(std::string & filename, artemis::httpd::HTTPContentType contentType);
      ~HTTPFileContentHandler();
      artemis::httpd::HTTPResponse * handleRequest(const artemis::httpd::HTTPRequest & request);

    private:
      std::string _filename;
      artemis::httpd::HTTPContentType _contentType;
    };
  }
}

#endif


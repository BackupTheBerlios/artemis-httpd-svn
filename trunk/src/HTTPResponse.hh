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

#ifndef HTTPD_HTTPRESPONSE_HH
#define HTTPD_HTTPRESPONSE_HH

#include <string>

namespace HTTPD
{
  enum HTTPResponseCode
    {
      HTTP_RESPONSE_CODE_OKAY,
      HTTP_RESPONSE_CODE_NOT_FOUND
    };

  class HTTPResponse
  {
  public:
    HTTPResponse(HTTPResponseCode httpResponseCode);
    ~HTTPResponse();

    void addContent(const char * content, long length);
    void addContent(std::string & content);

    char * getResponseString();
    size_t getResponseLength();

  private:
    HTTPD::HTTPResponseCode _httpResponseCode;

    char * _httpResponseContent;

    long _httpResponseContentLength;
    long _httpResponseLength;

    std::string * getResponseHeader();
  };
}

#endif


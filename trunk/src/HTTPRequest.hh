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

#ifndef ARTEMIS_HTTPD_HTTPREQUEST_HH
#define ARTEMIS_HTTPD_HTTPREQUEST_HH

#include <string>
#include <map>

namespace artemis
{
  namespace httpd
  {
    enum RequestMethod
      {
	GET,
	HEAD,
	POST
      };

    enum HTTPVersion
      {
	HTTP_0_9,
	HTTP_1_0,
	HTTP_1_1
      };

    class HTTPRequest
    {
    public:
      HTTPRequest(std::string & request_str);
      ~HTTPRequest();

      std::string getRequestURI() const;

    private:
      // request fields
      artemis::httpd::RequestMethod _requestMethod;
      std::string _requestURI;
      artemis::httpd::HTTPVersion _httpVersion;

      std::map<std::string, std::string> _headerFields;
      std::string _messageBody;

      // parsing functions
      void parseRequestLine(std::string & request_str);
      void parseHeaderFields(std::string & request_str);

      // parsing helper functions
      std::string cutOutSequence(std::string & str, bool firstlast, std::string delimeter);
      void trim(std::string & str);
    };
  }
}

#endif


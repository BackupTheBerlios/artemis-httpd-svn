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

#include "HTTPRequest.hh"

#include <iostream>

HTTPD::HTTPRequest::HTTPRequest(std::string & request_str)
{
  // temp string for parsing, because parser eats it up
  std::string parseString = request_str;

  parseRequestLine(parseString);
  parseHeaderFields(parseString);

  _messageBody = parseString;
}

HTTPD::HTTPRequest::~HTTPRequest()
{

}

std::string 
HTTPD::HTTPRequest::getRequestURI()
{
  return _requestURI;
}

void 
HTTPD::HTTPRequest::parseRequestLine(std::string & request_str)
{
  std::string requestLine = cutOutSequence(request_str, true, "\r\n");

  // parse methode
  std::string method = cutOutSequence(requestLine, true, " ");

  if (method == "GET")
    {
      _requestMethod = GET;
    }

  if (method == "HEAD")
    {
      _requestMethod = HEAD;
    }

  if (method == "POST")
    {
      _requestMethod = POST;
    }

  // parse version
  std::string version = cutOutSequence(requestLine, false, " ");
  if (version == "HTTP/0.9")
    {
      _httpVersion = HTTP_0_9;
    }

  if (version == "HTTP/1.0")
    {
      _httpVersion = HTTP_1_0;
    }

  if (version == "HTTP/1.1")
    {
      _httpVersion = HTTP_1_1;
    }

  // parse request-URI
  _requestURI = requestLine;
}

void
HTTPD::HTTPRequest::parseHeaderFields(std::string & request_str)
{
  std::string headerLine = cutOutSequence(request_str, true, "\r\n");

  if (headerLine == "")
    return;

  std::string field = cutOutSequence(headerLine, true, ":");
  _headerFields[field] = headerLine;

  parseHeaderFields(request_str);
}

std::string
HTTPD::HTTPRequest::cutOutSequence(std::string & str, bool firstlast, std::string delimeter)
{
  std::string::size_type pos;
  if (firstlast)
    pos = str.find(delimeter, 0);
  else
    pos = str.rfind(delimeter, str.size());

  std::string line;
  if (pos == std::string::npos)
    {
      line = str;
      str = "";
    }
  else
    {
      if (firstlast)
	{
	  line = str.substr(0, pos);
	  str.erase(0, pos + delimeter.size());
	}
      else
	{
	  line = str.substr(pos + delimeter.size(), str.size());
	  str.erase(pos, str.size());
	}
    }

  trim(str);
  trim(line);
  return line;
}

void
HTTPD::HTTPRequest::trim(std::string & str)
{
  std::string::size_type pos = str.find_last_not_of(' ');
  if(pos != std::string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(' ');
    if(pos != std::string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());
}

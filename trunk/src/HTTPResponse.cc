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

#include "HTTPResponse.hh"

#include <iostream>
#include <sstream>

artemis::httpd::HTTPResponse::HTTPResponse(HTTPResponseCode httpResponseCode, HTTPContentType httpContentType)
  : _httpResponseCode(httpResponseCode),
    _httpContentType(httpContentType),
    _httpResponseContent(0),
    _httpResponseContentLength(0),
    _httpResponseLength(0)
{
}

artemis::httpd::HTTPResponse::~HTTPResponse()
{
  if (_httpResponseContent)
    delete [] _httpResponseContent;
}

void
artemis::httpd::HTTPResponse::addContent(const char * content, long length)
{
  _httpResponseContentLength = length;
  _httpResponseContent = new char[_httpResponseContentLength];

  memcpy(_httpResponseContent, content, _httpResponseContentLength);
}

void
artemis::httpd::HTTPResponse::addContent(std::string & content)
{
  _httpResponseContentLength = content.size();
  _httpResponseContent = new char[_httpResponseContentLength + 1];

  strcpy(_httpResponseContent, content.c_str());
}

char * 
artemis::httpd::HTTPResponse::getResponseString()
{
  std::string * response_header = getResponseHeader();

  _httpResponseLength = response_header->size();
  _httpResponseLength += _httpResponseContentLength;

  char * response = new char[_httpResponseLength + 1];

  memcpy(response, response_header->c_str(), response_header->size());

  if (_httpResponseContent)
    memcpy(response + response_header->size(), _httpResponseContent, _httpResponseContentLength);

  response[_httpResponseLength] = '\0';

  delete response_header;

  return response;
}

size_t
artemis::httpd::HTTPResponse::getResponseLength()
{
  return _httpResponseLength;
}

std::string * 
artemis::httpd::HTTPResponse::getResponseHeader()
{
  std::string * response = new std::string();

  response->append("HTTP/1.1 ");

  switch(_httpResponseCode)
    {
    case HTTP_RESPONSE_CODE_OKAY:
      response->append("200 OK\n"); 
      break;
    case HTTP_RESPONSE_CODE_NOT_FOUND:
      response->append("404 Not Found\n");
      break;
    default:
      response->append("500 Internal Server Error\n");
      break;
    }

  switch(_httpContentType)
    {
    case TEXT_HTML:
      response->append("Content-type: text/html\n");
      break;
    case IMAGE_JPEG:
      response->append("Content-type: image/jpeg\n");
      break;
    default:
      break;
    }

  if (_httpResponseContent)
    {
      std::ostringstream ss;
      ss << _httpResponseContentLength;
      response->append("Content-length: " + ss.str() + "\n");
    }

  // ...

  response->append("Connection: close\n");

  response->append("\n");

  return response;
}

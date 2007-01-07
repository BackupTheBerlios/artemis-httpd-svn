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

#include "HTTPFileContentHandler.hh"

#include <iostream>
#include <fstream>

artemis::httpd::HTTPFileContentHandler::HTTPFileContentHandler(std::string & filename, artemis::httpd::HTTPContentType contentType)
  : _filename(filename),
    _contentType(contentType)
{
}

artemis::httpd::HTTPFileContentHandler::~HTTPFileContentHandler()
{
}
 
artemis::httpd::HTTPResponse * 
artemis::httpd::HTTPFileContentHandler::handleRequest(const artemis::httpd::HTTPRequest & request)
{
  artemis::httpd::HTTPResponse * response = new artemis::httpd::HTTPResponse(HTTP_RESPONSE_CODE_OKAY, _contentType);

  // open file
  std::ifstream filestr;
  filestr.open(_filename.c_str());
  std::filebuf * pbuf = filestr.rdbuf();
  // get file size
  long size = pbuf->pubseekoff (0, std::ios::end, std::ios::in | std::ios::binary);
  char * buffer = new char[size];
  // read file
  pbuf->pubseekpos (0, std::ios::in | std::ios::binary);
  pbuf->sgetn (buffer, size);
  // close file
  filestr.close();

  response->addContent(buffer, size);

  delete [] buffer;

  return response;
}

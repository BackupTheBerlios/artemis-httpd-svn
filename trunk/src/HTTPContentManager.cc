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

#include "HTTPContentManager.hh"

#include <iostream>

artemis::httpd::HTTPContentManager::HTTPContentManager()
{
  _contentMap = new std::map<std::string, artemis::httpd::HTTPContentHandler *>();
}

artemis::httpd::HTTPContentManager::~HTTPContentManager()
{
  if (_contentMap)
    {
      delete _contentMap;
    }
}

void 
artemis::httpd::HTTPContentManager::addFileContent(std::string request, std::string filename)
{
  //  (*_contentMap)[request] = filename;
}

void 
artemis::httpd::HTTPContentManager::addDirectoryContent(std::string request, std::string directory)
{
  //  (*_contentMap)[request] = directory;
}

void 
artemis::httpd::HTTPContentManager::addContentHandler(std::string request, artemis::httpd::HTTPContentHandler * contentHandler)
{
  (*_contentMap)[request] = contentHandler;
}

artemis::httpd::HTTPResponse * 
artemis::httpd::HTTPContentManager::handleRequest(const artemis::httpd::HTTPRequest & request)
{
  std::string requestURI = request.getRequestURI();

  artemis::httpd::HTTPResponse * response;

  std::cout << "HTTPContentManager.cc: ***" << requestURI << "***" << std::endl;
  
  if (_contentMap->count(requestURI) == 0)
    {
      response = new artemis::httpd::HTTPResponse(HTTP_RESPONSE_CODE_NOT_FOUND, TEXT_HTML);
      std::string notfound = "<html>\n<head><title>NOT FOUND</title></head></html>";
      response->addContent(notfound);
    }
  else
    {
      artemis::httpd::HTTPContentHandler * contentHandler = (*_contentMap)[requestURI];
      response = contentHandler->handleRequest(request);
    }

  return response;
}

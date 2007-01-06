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

HTTPD::HTTPContentManager::HTTPContentManager()
{
  _contentMap = new std::map<std::string, std::string>();
}

HTTPD::HTTPContentManager::~HTTPContentManager()
{
  delete _contentMap;
}

void 
HTTPD::HTTPContentManager::addFileContent(std::string request, std::string filename)
{
  (*_contentMap)[request] = filename;
}

void 
HTTPD::HTTPContentManager::addDirectoryContent(std::string request, std::string directory)
{
  (*_contentMap)[request] = directory;
}

void 
HTTPD::HTTPContentManager::addDynamicContent(std::string request)
{
}

HTTPD::HTTPResponse * 
HTTPD::HTTPContentManager::handleRequest(HTTPD::HTTPRequest * request)
{
  HTTPD::HTTPResponse * response = new HTTPD::HTTPResponse(HTTP_RESPONSE_CODE_OKAY);
  std::string content = "<html>\n<head><title>Test</title></head></html>";
  response->addContent(content);
  return response;
}

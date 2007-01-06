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

#include "HTTPServer.hh"
#include "HTTPConnection.hh"

#include <stdexcept>
#include <iostream>

#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

HTTPD::HTTPServer::HTTPServer(int port)
{
  _contentManager = new HTTPD::HTTPContentManager();

  _yes = 1; // ????

  int _backlog = 10; // ????

  if ((_socketfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) 
    {
      throw std::runtime_error("Error while socket call.");
    }

  if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &_yes, sizeof(int)) == -1) 
    {
      throw std::runtime_error("Error while setsockopt call.");
    }

  _local_in_addr.sin_family = AF_INET; // host byte order
  _local_in_addr.sin_port = htons(port); // short, network byte order
  _local_in_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
  memset(&(_local_in_addr.sin_zero), '\0', 8); // zero the rest of the struct  

  if (bind(_socketfd, (struct sockaddr *)&_local_in_addr, sizeof(struct sockaddr)) == -1) 
    {
      throw std::runtime_error("Error while bind call.");
    }

  if (listen(_socketfd, _backlog) == -1) 
    {
      throw std::runtime_error("Error while listen call.");
    }

}

HTTPD::HTTPServer::~HTTPServer()
{
  if (_contentManager)
    delete _contentManager;
}

void 
HTTPD::HTTPServer::start()
{
  socklen_t sin_size;
  struct sockaddr_in client_addr; // connector's address information
  int new_fd;

  HTTPD::HTTPConnection * connection;

  while(true) 
    {
      std::cout << "HTTPServer::start() A" << std::endl;

      sin_size = sizeof(struct sockaddr_in);

      if ((new_fd = accept(_socketfd, (struct sockaddr *)&client_addr, &sin_size)) == -1) 
	{
	  std::cout << "Error while accepting." << std::endl;
	  continue;
	}

      connection = new HTTPD::HTTPConnection(new_fd, _contentManager);
    }
}

void
HTTPD::HTTPServer::addFileContent(std::string request, std::string filename)
{
  _contentManager->addFileContent(request, filename);
}

void
HTTPD::HTTPServer::addDirectoryContent(std::string request, std::string directory)
{
  _contentManager->addDirectoryContent(request, directory);
}

void
HTTPD::HTTPServer::addDynamicContent(std::string request)
{
  _contentManager->addDynamicContent(request);
}

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

#include "HTTPConnection.hh"

#include <stdexcept>

#include <iostream>

#define BUFFER_SIZE 10000

HTTPD::HTTPConnection::HTTPConnection(int fd, HTTPD::HTTPContentManager * contentManager)
  : artemis::util::Thread(),
    _socketfd(fd),
    _contentManager(contentManager)
{
  // start thread
  start();
}

HTTPD::HTTPConnection::~HTTPConnection()
{
  // close socket
  close(_socketfd);
}

void *
HTTPD::HTTPConnection::run()
{
  // receive request
  HTTPD::HTTPRequest * request = receiveRequest();

  // get response from content handler
  HTTPD::HTTPResponse * response = _contentManager->handleRequest(request);

  // send response
  char * response_str = response->getResponseString();
  size_t response_len = response->getResponseLength();

  if (send(_socketfd, response_str, response_len, 0) == -1)
    {
      std::cout << "Send error." << std::endl;
    }

  delete request;
  delete response;
  delete [] response_str;

  delete this;

  return 0;
}

HTTPD::HTTPRequest *
HTTPD::HTTPConnection::receiveRequest()
{
  std::string result;

  char buf[BUFFER_SIZE];
  int numbytes = 0;
  bool again = true;

  while (again)
    {
      if ((numbytes = recv(_socketfd, buf, BUFFER_SIZE - 1, 0)) == -1)
        {
	  throw std::runtime_error("Error while receiving.");
        }
      buf[numbytes] = '\0';
      result += buf;

      if (numbytes != BUFFER_SIZE - 1)
        again = false;
    }

  return new HTTPD::HTTPRequest(result);
}

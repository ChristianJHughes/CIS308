//Author: Christian Hughes
//CIS 308 Assignment 5
//Some code used from: http://vichargrave.com/network-programming-design-patterns-in-c/

#include "HTTPCnx.hpp"
#include <stdio.h>
#include <string.h>

#define MSGLEN  10000

HTTPCnx::HTTPCnx(const char *h)
{
	host = string(h);
	connector = new TCPConnector;
	stream = connector->connect(h, 80);
}

HTTPCnx::~HTTPCnx()
{
	delete connector;
}

string HTTPCnx::get(const char *page)
{
 char message[MSGLEN];
 ssize_t s;
 sprintf(message, "GET %s HTTP/1.1\nHOST: %s\n\n",
                  page, host.c_str());
  stream->send1(message, strlen(message));
  s = stream->receive(message, MSGLEN); 
  return string(message);
}

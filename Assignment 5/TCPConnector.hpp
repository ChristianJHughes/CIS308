//Author: Christian Hughes
//CIS 308 Assignment 5
//Some code used from: http://vichargrave.com/network-programming-design-patterns-in-c/

#include <netinet/in.h>
#include "TCPStream.hpp"
 
class TCPConnector
{
  public:
    TCPStream* connect(const char* server, int port);
 
  private:
    int resolveHostName(const char* host, struct in_addr* addr);
};

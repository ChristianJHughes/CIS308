//Author: Christian Hughes
//CIS 308 Assignment 5
//Some code used from: http://vichargrave.com/network-programming-design-patterns-in-c/

#include <arpa/inet.h>
#include "TCPStream.hpp"
#include <string>
 
TCPStream::TCPStream(int sd, struct sockaddr_in* address) : m_sd(sd) {
    char ip[50];
    inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), 
              ip, sizeof(ip)-1);
    m_peerIP = ip;
    m_peerPort = ntohs(address->sin_port);
}

TCPStream::~TCPStream()
{
    close(m_sd);
}

ssize_t TCPStream::send1(char* buffer, size_t len)
{
	return ::send(m_sd, buffer, len, 0);
}

ssize_t TCPStream::receive(char* buffer, size_t len)
{
	return ::recv(m_sd, buffer, len, 0);
}

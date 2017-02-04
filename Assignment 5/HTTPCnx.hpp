//Author: Christian Hughes
//CIS 308 Assignment 5
//Some code used from: http://vichargrave.com/network-programming-design-patterns-in-c/

#ifndef HTTPCnx_HPP
#define HTTPCnx_HPP

#include <string>
#include "TCPConnector.hpp"

using namespace std;

class HTTPCnx {
string host;
TCPConnector* connector;
TCPStream* stream;

public:
	HTTPCnx(const char *host);
	~HTTPCnx();

	string get(const char *page);
};

#endif

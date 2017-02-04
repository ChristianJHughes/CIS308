//Author: Christian Hughes
//CIS 308 Assignment 5

#include "HTTPCnx.hpp"
#include <stdio.h>
#include <string>
#include <iostream>

int main()
{
	const char *input = "httpbin.org";
	const char *page = "/html";
	HTTPCnx* streamDude = new HTTPCnx(input);
	string output = "";	
	output = streamDude->get(page);
	cout << output;	
	return 0;
}

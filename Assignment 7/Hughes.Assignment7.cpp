// CIS 308 Assignment 7
// ProgCtl c++ Project
// Author: Christian Hughes
// April 28, 2015

#include <iostream>
#include <string>
#include <stdio.h>

#include "ProgCtl.hpp"

using namespace std;

int main()
{
	char inputProcess[100];
	cout << "Please enter the name of the process that you wish to kill:";
	cin >> inputProcess;
	ProgCtl test(inputProcess);
	test.getPID();

	int result = test.send(9);
	
	if (result == 0)
	{
		cout << "Process '" << inputProcess << "' was sucessfully killed. All done." << endl;
	}
	else if (result == 1)
	{
		cout << "Process '" << inputProcess << "' was not found. Please try again." << endl;
	}
	exit(1);
}

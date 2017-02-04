// CIS 308 Assignment 8
// Program8.cpp
// Author: Christian Hughes
// May 5th, 2015

#include <iostream>
#include <string>
#include <stdio.h>

#include "beeperController.hpp"

using namespace std;

int main()
{
	//Creates a beeperController object for the running process.
	beeperController test;

	//An integer representing the user input.
	int result;

	//Sits in a loop and allows the user to manipulate the beeper process.
	while (result != 3)
	{
		cout << "Please enter (0) to stop the process, (1) to speed up the process, or (2) to slow down the process: ";
		cin >> result;

		if (result == 0)
		{
			test.stop();
			cout << "Process '" << "beeper" << "' was sucessfully stopped. All done." << endl;
			result = 3;
		}
		else if (result == 1)
		{	
			test.beep_faster();
			cout << "Process '" << "beeper" << "' was sped up." << endl;
		}
		else if (result == 2)
		{
			test.beep_slower();
			cout << "Process '" << "beeper" << "' was slowed down." << endl;
		}
	}
	exit(1);
}

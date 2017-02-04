// CIS 308 Assignment 7
// ProgCtl c++ Project
// Author: Christian Hughes
// April 28, 2015

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cstring>

class ProgCtl
{
	std::string _name;
	int _pid;

	public:
	//CONSTRUCTORS.

	//The default consturctor.
	ProgCtl(int pid=-1){_name = "";}
	//A constructor that takes the name of the process as a parameter.
	ProgCtl(char* name):_pid(-1){_name = std::string(name);} 

	//METHODS.
	
	//Reports whether or not the program is running.	
	bool alive(); 
	//Send a message to kill the given process, using a user defined signal number.
	int send(int sig);
	//Gets the PID of the process, and assigns it to the _pid field. 
	void getPID();

};

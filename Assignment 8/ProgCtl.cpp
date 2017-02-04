// CIS 308 Assignment 8
// ProgCtl.cpp
// Author: Christian Hughes
// May 5th, 2015

#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>

#include "ProgCtl.hpp"

using namespace std;

//The setter for the _PID field in the ProgCtl.c
void ProgCtl::getPID()
{
	
	char PIDAndName[100];
	char cmd[200];

	sprintf(cmd, "ps -e -o pid,comm | grep %s", _name.c_str());
	FILE* p = popen(cmd, "r");
        if (p == NULL) {
           cerr << "Popen error. Aborting. " << cmd << endl;
           exit(1);
        }
        if (fgets(PIDAndName, 100, p)) {
            sscanf(PIDAndName, "%d", &_pid);
        } 
	else {
            _pid = -1;
        }
        pclose(p);
}

//Kills the process using the given signal number, residing at whatever PID is being used by the program.
int ProgCtl::send(int sig)
{	
	//Simply runs the kill comand at the given pid.
	if (alive())
	{
		kill(_pid, sig);
		//_pid = -1; //Not necessary in program 8. Allows for repeated commands.
		return 0;
	}
	else
	{
		return 1;
	}
}

//Checks to see whether or not the PID is alive or not.
bool ProgCtl::alive()
{
	if (_pid == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

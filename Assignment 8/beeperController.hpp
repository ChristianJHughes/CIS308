// CIS 308 Assignment 8
// beeperContoller.hpp
// Author: Christian Hughes
// May 5th, 2015

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cstring>
#include <signal.h>

#include "ProgCtl.hpp"

class beeperController: public ProgCtl
{
	public:
	//Constructor that automatically assigns the process name to 'beeper' (as this is the beeper contoller).
        beeperController():ProgCtl((char *)"beeper"){getPID();}
	
	//Sends a signal to stop the beeper.
	void stop()
	{
		send(SIGTERM);
	}

	//Sends a signal to speed up the beeper.
	void beep_faster()
	{	
		send(SIGUSR1);
	}

	//Sends a signal to slow down the beeper. 
	void beep_slower()
	{	
		send(SIGUSR2);
	}
};

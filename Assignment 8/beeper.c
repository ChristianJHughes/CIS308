// CIS 308 Assignment 8
// beeper.c
// Author: Christian Hughes
// Code snippets by S. Faroult -- Used With Permission
// May 5th, 2015

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

#define SLEEP_TIME 10

//The nap time, in seconds. Defaulted to 10, but modifiable with the appropirate signals.
static int nap = SLEEP_TIME;

//Speeds up the beeper program by a factor of 2. 
void faster(int sig)
{
	nap /= 2;
	if (nap == 0)
	{
		nap = 1;
	}
}

//Slows down the program by a factor of 2.
void slower(int sig)
{
	nap *= 2;
}

//Stops and exits the beeper program.
void stop(int sig)
{
	printf("Beeper has stopped. See you later!\n");
	exit(1);
}

//The main method for the beeper program. Beeps every 10 seconds by default.
int main()
{	
	(void)signal(SIGUSR1,faster);
	(void)signal(SIGUSR2,slower);
	(void)signal(SIGTERM,stop);
	
	time_t now;
	struct tm *t;

	while(1) 
	{		
		now = time(NULL);
		t = localtime(&now);
		printf("%02d:%02d:%02d beep!\n",
			t->tm_hour, t->tm_min, t->tm_sec);
		sleep(nap);
	}
	return 0;
}

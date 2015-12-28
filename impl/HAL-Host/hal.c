/*  
    Real-Time Systems
    (C) 2009 J. Friedrich
    University of Applied Sciences Esslingen

    Author:  J. Friedrich, April 2009  
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "..\Application\hal.h"
#include "..\Application\button.h"
#include "..\Application\ticker.h"
#include "..\Application\beeper.h"

#define BUFFERSIZE 132
static unsigned long time = 0;
static unsigned int remainingTicks = 0;
static unsigned long switch1DownTime = 0;
static unsigned long switch2DownTime = 0;
static unsigned long switch3DownTime = 0;
static unsigned long switch4DownTime = 0;


void initHardware(void) {
	initButton();
	initTicker();
	initBeeper();
}

char switch1DownSimu(void) {
	if (time == 0 || time > switch1DownTime) {
		return 0;
	}
	else {
		return 1;
	}
}

char switch2DownSimu(void) {
	if (time == 0 || time > switch2DownTime) {
		return 0;
	}
	else {
		return 1;
	}
}

char switch3DownSimu(void) {
	if (time == 0 || time > switch3DownTime) {
		return 0;
	}
	else {
		return 1;
	}
}

char switch4DownSimu(void) {
	if (time == 0 || time > switch4DownTime) {
		return 0;
	}
	else {
		return 1;
	}
}


void tick(void) {
  time = time + 1;
  --remainingTicks;
}

unsigned long getTimeSimu(void) {
	return time;
}

void sampleInputs(void) {
 long delta = 0;
 char line[BUFFERSIZE];
 char *tailptr;
 char *dum;
 
 if (remainingTicks > 0) {
	 tick();
	 return;
 }

 if (gets_s(line,BUFFERSIZE) == NULL) {
	 exit(0);
 }

 if (line[0] != '#') {
	 
	 /* advance ticker */
	 if (line[0] == '+') {
		 tailptr = NULL;
		 remainingTicks = (int) strtol(line, &tailptr, 0);
		 return;
	 }

	 /* switch "1" pressed */
	 if( strstr(line, "s1") == line) {
		 remainingTicks = 1;
		 if ((tailptr = strstr(line,"+")) != NULL) {
			remainingTicks = (int) strtol(tailptr, &dum, 0);
		}
		 switch1DownTime = time + remainingTicks;
		 printf("%5d: S1 down until %d\n", time, switch1DownTime);
	 }

	 /* switch "2" pressed */
	 if( strstr(line, "s2") == line) {
		 remainingTicks = 1;
		 if ((tailptr = strstr(line,"+")) != NULL) {
			remainingTicks = (int) strtol(tailptr, &dum, 0);
		}
		 switch2DownTime = time + remainingTicks;
		 printf("%5d: S2 down until %d\n", time, switch2DownTime);
	 }

	 /* switch "3" pressed */
	 if( strstr(line, "s3") == line) {
		 remainingTicks = 1;
		 if ((tailptr = strstr(line,"+")) != NULL) {
			remainingTicks = (int) strtol(tailptr, &dum, 0);
		}
		 switch3DownTime = time + remainingTicks;
		 printf("%5d: S3 down until %d\n", time, switch3DownTime);
	 }

	 /* switch "4" pressed */
	 if( strstr(line, "s4") == line) {
		 remainingTicks = 1;
		 if ((tailptr = strstr(line,"+")) != NULL) {
			remainingTicks = (int) strtol(tailptr, &dum, 0);
		}
		 switch4DownTime = time + remainingTicks;
		 printf("%5d: S4 down until %d\n", time, switch4DownTime);
	 }
   }
}

void turnMachineOff() {
	printf("Turning machine off...\n");
	getc(stdin);
	exit(0);
}
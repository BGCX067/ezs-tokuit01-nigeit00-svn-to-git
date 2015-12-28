/*  
    Real-Time Systems
    (C) 2009 J. Friedrich
    University of Applied Sciences Esslingen

    Author:  J. Friedrich, April 2009  
*/
#include <stdio.h>
#include "..\Application\ticker.h"
#include "..\Application\hal.h"

void initTicker() {

}

static long timerStart = 0;

void resetTimer() {
	timerStart = getTime();
}

unsigned int getTimerValue() {
  return getTime() - timerStart;
}

long getTime() {
	return getTimeSimu();
}


void registerTickRoutine(void (*functionPointer)(void)){

}
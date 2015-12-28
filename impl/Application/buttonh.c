/*  
    Real-Time Systems
    (C) 2009 J. Friedrich
    University of Applied Sciences Esslingen

    Author:  J. Friedrich, April 2009  
*/
#include "button.h"
#include "buttonh.h"
#include "ticker.h"

static char switch1Last = 0;
static char switch2Last = 0;
static char switch3Last = 0;
static char switch4Last = 0;

static unsigned long bounceTimerSwitch1 = 0;
static unsigned long bounceTimerSwitch2 = 0;
static unsigned long bounceTimerSwitch3 = 0;
static unsigned long bounceTimerSwitch4 = 0;

static const bounceDelay = 4; /* 4 ticks to limit bouncing */


unsigned char eventSwitch1(void) {
	if ((getTime() - bounceTimerSwitch1) < bounceDelay) {
		return 0;  /* silence during bounce delay */
	}

	if (switch1Down() && (switch1Last == 0)) {
		switch1Last = 1;
		bounceTimerSwitch1 = getTime();
		return 1;
	}
	
	if (switch1Down() && (switch1Last == 1)) {
		return 0;
	}
	
	switch1Last = 0;
	return 0;
}

unsigned char eventSwitch2(void) {
	if ((getTime() - bounceTimerSwitch2) < bounceDelay) {
		return 0;  /* silence during bounce delay */
	}

	if (switch2Down() && (switch2Last == 0)) {
		switch2Last = 1;
		bounceTimerSwitch2 = getTime();
		return 1;
	}
	
	if (switch2Down() && (switch2Last == 1)) {
		return 0;
	}
	
	switch2Last = 0;
	return 0;
}

unsigned char eventSwitch3(void) {
	if ((getTime() - bounceTimerSwitch3) < bounceDelay) {
		return 0;  /* silence during bounce delay */
	}

	if (switch3Down() && (switch3Last == 0)) {
		switch3Last = 1;
		bounceTimerSwitch3 = getTime();
		return 1;
	}
	
	if (switch3Down() && (switch3Last == 1)) {
		return 0;
	}
	
	switch3Last = 0;
	return 0;
}

unsigned char eventSwitch4(void) {
	if ((getTime() - bounceTimerSwitch3) < bounceDelay) {
		return 0;  /* silence during bounce delay */
	}

	if (switch4Down() && (switch4Last == 0)) {
		switch4Last = 1;
		bounceTimerSwitch4 = getTime();
		return 1;
	}
	
	if (switch4Down() && (switch4Last == 1)) {
		return 0;
	}
	
	switch4Last = 0;
	return 0;
}
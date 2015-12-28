/*  
    Real-Time Systems Labor 1 Nils Gemba und Tobias Kußmaul
*/
#include "states.h"
#include "ticker.h"
#include "button.h"
#include "buttonh.h"
#include "hal.h"
#include "lcddrv.h"
#include "beeper.h"
#include <stdio.h>
#include <string.h>

static states currentState;
static states lastState;
#define LINELENGTH 17
char firstline[LINELENGTH] = ""; /* for Display */
char secondline[LINELENGTH] = "";

static unsigned short int actualTime = 0L; /* In seconds */
static unsigned short int presetTime = 0L; /* In seconds */
static unsigned long ranTicks=0;
static void resetRuntime(void) {
	ranTicks=0;
}

//typedef enum {NONE=0, YELLOWB2YELLOW=1, YELLOWB2OFF=2} transition; // Weiß net ob nötig
//static transition transitionActivity;

static void setGenericFirstline(void);
static void setGenericSecondline( char boolDisplayValue );

void setActualTime(unsigned short int aTimeSeconds) {
	actualTime = aTimeSeconds;
}

unsigned long int getActualTime(void) {
	return actualTime;
}

void setPresetTime(unsigned short int pTimeSeconds) {
	presetTime = pTimeSeconds;
}

unsigned long int getPresetTime(void) {
	return presetTime;
}

states getCurrentState() {
	return currentState;
}

void setCurrentState(states cs) {
	currentState = cs;
}

states getLastState() {
	return lastState;
}

void setLastState(states cs) {
	lastState = cs;
}

void initStateMachine() {
  setLastState(OFF); /* force initial transition */ 
  setCurrentState(SET); /* next after initial state */
  resetTimer();
}

void Set(void) {
	static unsigned short int savedPresetTimerValue=0L;
	if(getCurrentState()!=getLastState()) {/* OnEntry */
		setLastState(getCurrentState()); /* Transition aufessen */
		setPresetTime(0);
	}
	
	if(eventSwitch1()){ /* Zeit für Preset erhöhen */
		unsigned short int newPresetTimerValue=getPresetTime();
		if ( newPresetTimerValue+SETSTEP <= (5*60) ) {
			newPresetTimerValue +=SETSTEP;
		} else {
			newPresetTimerValue = 0;	
		}
		setPresetTime(newPresetTimerValue);
	}
	if(eventSwitch3()) {
		setPresetTime(savedPresetTimerValue);
	}

	if(eventSwitch2()){ /* Zeit für Preset verringern */
		unsigned short int newPresetTimerValue=getPresetTime();
		if ( newPresetTimerValue+SETSTEP*60 <= (5*60) ) {
			newPresetTimerValue +=SETSTEP*60;
		} else {
			newPresetTimerValue = 0;	
		}
		setPresetTime(newPresetTimerValue);
	}

	if(eventSwitch4()) { /* Transition */
		savedPresetTimerValue=getPresetTime(); /* On Exit - Save old */
		setCurrentState(COUNTDOWNRUNNING);
		resetRuntime();
	}
	setGenericFirstline();
	setGenericSecondline(0);
}

void CountdownRunning(void) {
	
	if(getCurrentState()!=getLastState()) {/* OnEntry */
		setLastState(getCurrentState()); /* Transition aufessen */
		resetTimer();
	}
	
	setActualTime((getTimerValue()+ranTicks)/TICKPERSECOND);
	
	if(getActualTime() >= getPresetTime()){ /* Tea done */
		setCurrentState(BEEPING);
	}

	if(eventSwitch4()) { /* Transition */
		setCurrentState(COUNTDOWNPAUSED);
		ranTicks+=getTimerValue();
	}
	setGenericSecondline(1);
}

void CountdownPaused(void){
	if(getCurrentState()!=getLastState()) {/* OnEntry */
		setLastState(getCurrentState()); /* Transition aufessen */
	}

	if(eventSwitch4() && (getActualTime() < getPresetTime()) ) { /* Transition, nur wenn der Timer noch nicht abgel. ist */
		setCurrentState(COUNTDOWNRUNNING);
	}
	
	if(eventSwitch1() || eventSwitch2()) {
		setCurrentState(SET);
	}
}

void Beeping(void){
	static int beepingFrequency = 3072;
	if(getCurrentState()!=getLastState()){
		resetTimer();					 /* Entry Activity */
		setLastState(getCurrentState()); /* Transition aufessen */
	  beepingFrequency = 3072;
	}
	
	/* Activity beeping */
	if(getTimerValue() % (TICKPERSECOND * 2) < TICKPERSECOND * 1) { /* 1. von 2 Sekunden */
		(void) beeperOn(beepingFrequency+=100);
	}	
	if (getTimerValue() % (TICKPERSECOND * 2) > TICKPERSECOND * 1) { /* 2. von 2 Sekunden */
		  beeperOff(); 
	}

	if(eventSwitch4() || getTimerValue()> TICKPERSECOND * 9) { /* Transition */
		setCurrentState(SET);
		beeperOff();
	}

}

void Off(void){ /* nicht erreichbarer Zustand, nur zur Initialisierung benötigt */

}

static void setGenericFirstline(void) {
	unsigned short int minute = getPresetTime()/60;
	unsigned short int sekunde = getPresetTime()%60;
	
	(void) sprintf(firstline, "Preset: %02d:%02d", minute, sekunde);
};
void setFirstline(const char * src){
	size_t size = (strlen(src)+1) % (LINELENGTH+1); /* Maximal so lang wie Inputpuffer und LINELENGTH */
	(void) memcpy(firstline, src, size);
};
const char * getFirstline(void){
	return firstline;
};

static void setGenericSecondline( char boolDisplayValue ) {
	unsigned short int minute = (getPresetTime() - getActualTime())/60;
	unsigned short int sekunde = (getPresetTime() - getActualTime())%60;
	if (boolDisplayValue) {
		(void) sprintf(secondline, "Actual: %02d:%02d", minute, sekunde);
	} else {
		(void) sprintf(secondline, "Actual: --:--");
	}
};
void setSecondline(const char * src){
	size_t size = (strlen(src)+1) % (LINELENGTH+1); /* Maximal so lang wie Inputpuffer und LINELENGTH */
	(void) memcpy(secondline, src, size);
};
const char * getSecondline(void){
	return secondline;
};

/* Write the two lines to the Display */
void updateDisplay(void){
	writeLine(firstline, 0);	
	writeLine(secondline, 1);	
};
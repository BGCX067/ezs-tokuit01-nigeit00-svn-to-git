/*  
    Real-Time Systems
    (C) 2009 J. Friedrich
    University of Applied Sciences Esslingen

    Author:  J. Friedrich, April 2009  
*/ /*für TeaTimer angepasst für Labor 1*/
#ifndef _statesh
#define _statesh

/* All states as an enum */
typedef enum {SET=0, COUNTDOWNRUNNING, COUNTDOWNPAUSED, BEEPING, OFF} states;

/* functions for timer*/
void setActualTime(unsigned short int aTime);
unsigned long int getActualTime(void);
void setPresetTime(unsigned short int pTime);
unsigned long int getPresetTime(void);

/* Functions for setting Display Text */
void setFirstline(const char * src);
const char * getFirstline(void);
void setSecondline(const char * src);
const char * getSecondline(void);

/* One function for each state */
#define SETSTEP 1L //1 Sekunden hinzufügen
void Set(void);
void CountdownRunning(void);
void CountdownPaused(void);
void Beeping(void);
void Off(void);

/* Setter and getters for the current state */
states getCurrentState(void);
void setCurrentState(enum cs);

/* Setter and getters for the previous state */
/* to detect a state transition              */
states getLastState(void);
void setLastStateState(enum cs);

/* Initialization of the state machine, go to initial state */
void initStateMachine(void);

/* Write the two lines to the Display */
void updateDisplay(void);
#endif
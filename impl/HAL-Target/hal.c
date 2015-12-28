#include <hidef.h> /* common defines and macros for CodeWarrior*/
#include <mc9s12dp256.h>
#pragma LINK_INFO DERIVATIVE "mc9s12dp256"

#include "..\Application\hal.h"
#include "..\Application\button.h"
#include "..\Application\ticker.h"
#include "..\Application\beeper.h"
#include "..\Application\lcddrv.h"


void initHardware(void) {
	initButton();
	initLcd();
	initTicker();
	initBeeper();
	EnableInterrupts;
}


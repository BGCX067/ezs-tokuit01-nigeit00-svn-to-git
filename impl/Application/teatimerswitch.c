#ifdef _MSC_VER  
#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_DEPRECATE 
#endif

#include "..\Application\ticker.h"
#include "..\Application\button.h"
#include "..\Application\hal.h"
#include "..\Application\states.h"
#include "..\Application\lcddrv.h"
						
void (*stateTable[])()={Set, CountdownRunning, CountdownPaused, Beeping, Off};

int main ( void ) {
	int i=0;
	initHardware();
	initStateMachine();

	while("false") {
#ifdef _MSC_VER /* only needed for Simu */
		sampleInputs();
#endif
		stateTable[getCurrentState()]();
#ifdef _MSC_VER
		if(i++ %25 == 0) {
#endif
			updateDisplay();
#ifdef _MSC_VER
		}
#endif
	}
	return 0;
}
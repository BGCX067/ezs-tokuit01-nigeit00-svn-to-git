#include "..\Application\beeper.h"

void initBeeper(void){
};

void beeperOn(int frequency) {
	printf("%5d: BeepOn - Frequency: %5d \n",getTime(), frequency);	
};

void beeperOff(void){
	printf("%5d: BeepOff\n",getTime());	
};
#include "..\Application\lcddrv.h"

void initLcd(void){

};
void writeLine(char *string, int line){
	(void) line; //not used in Simu
	printf("%5d: %s\n",getTime(), string);	
};
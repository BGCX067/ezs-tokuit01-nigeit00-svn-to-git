/*  
    Real-Time Systems
    (C) 2009 J. Friedrich
    University of Applied Sciences Esslingen

    Author:  J. Friedrich, April 2009  
*/
#include "button.h"
#include "hal.h"
#include <mc9s12dp256.h>

void initButton() {
   DDRH = 0x00;
}

char switch1Down() {
	/* if (PTH & 0x01) {  */
	if (~PTH & 0x01) {  /* for real hardware inverted */	
	  return 1;
	} 
	else {
	  return 0;  
	}
}

char switch2Down() {
	/*if (PTH & 0x02) {   */
	 if (~PTH & 0x02) {  /* for real hardware inverted */

	  return 1;
	} 
	else {
	  return 0;  
	}
}

char switch3Down() {
  /*	if (PTH & 0x04) {  */
	 if (~PTH & 0x04) {  /* for real hardware inverted */

	  return 1;
	} 
	else {
	  return 0;  
	}
}

char switch4Down() {
	/* if (PTH & 0x08) { */
	 if (~PTH & 0x08) {  /* for real hardware inverted */

	  return 1;
	} 
	else {
	  return 0;  
	}
}
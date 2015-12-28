/*  
    Real-Time Systems
    (C) 2009 J. Friedrich
    University of Applied Sciences Esslingen

    Author:  J. Friedrich, April 2009  
*/
#ifndef _buttonhh
#define _buttonhh

/* These routines return 1 if the "on" or "off" buttons were pressed    */
/* Debouncing is taken care off. The buttons need to be released before */
/* these routines return 1 again.                                       */
/* These routines are not hardware specific.                            */

unsigned char eventSwitch1(void);
unsigned char eventSwitch2(void);
unsigned char eventSwitch3(void);
unsigned char eventSwitch4(void);

#endif
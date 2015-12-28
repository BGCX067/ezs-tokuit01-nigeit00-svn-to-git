/*  
    Real-Time Systems
    (C) 2009 J. Friedrich
    University of Applied Sciences Esslingen

    Author:  J. Friedrich, April 2009  
*/
#ifndef _buttonh
#define _buttonh


void initButton(void);

/* Low level routines which detect a button is pressed. */
/* There is no need for debouncing, this is handled elsewhere.    */
char switch1Down(void);
char switch2Down(void);
char switch3Down(void);
char switch4Down(void);

#endif

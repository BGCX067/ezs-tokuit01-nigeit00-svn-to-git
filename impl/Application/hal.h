/*  
    Real-Time Systems
    (C) 2009 J. Friedrich
    University of Applied Sciences Esslingen

    Author:  J. Friedrich, April 2009  
*/
#ifndef _halh
#define _halh

/* Initialize the real hardware here */
void initHardware(void);

/* This we need to get inputs, either from events delivered by interrupts */
/* or polling the hardware, or by reading the input file during simulation */
#ifdef _MSC_VER
void sampleInputs(void);
#endif

/* This is the exit for the simulation, and could possibly put the */
/* real system to sleep.                                           */
/* void turnMachineOff(void); */ /* Not needed so far*/

/* This increments the real-world time on either the hardware or during simulation.  */
/* In hardware, this is driven by a hardware timer interrupt. In the simulation this */
/* is driven by the simulation input file.                                           */
#ifdef _MSC_VER
void tick(void);
#endif

/* As the name says, this is a very low level routine to get the time from the */
/* simulation input file. The real time is to be obtained from the ticker(.h)  */
/* You can replace this with a dummy for the real system.                      */
#ifdef _MSC_VER
unsigned long getTimeSimu(void);
#endif

/* Again, two routines solely for simulation. They simulate the two buttons,   */
/* where the values are read from the simulation input file. For the real      */
/* system these would be obtained from button(.h), and you could provide just  */
/* dummies for these routines.                                                 */
#ifdef _MSC_VER
char switch1DownSimu(void);
char switch2DownSimu(void);
char switch3DownSimu(void);
char switch4DownSimu(void);
#endif

/* Some more information on the simulation input file supported here:

# (as a first character in a line) makes this line a comment
# all text below has to be left aligned in a line
+10     advances ticker by 10 ticks
s1		presses "switch1" button for one tick (at time == 10)
s2		presses "switch2" button for one tick (at time == 10)
s3		presses "switch3" button for one tick (at time == 10)
s4		presses "switch4" button for one tick (at time == 10)
+5      advances ticker by 5 ticks to 16
s1+10  presses "switch1" button for 10 ticks (from time 16 until time 26)

*/
#endif
//DEFINE MAIN HEADER FILE
#ifndef MAIN_H
#define MAIN_H

//INCLUDE DEFINITILOW OF HEADER FILE
#include "includes.h"

//DEFINE PORTS/PINS
#define RFPORT		P3


//DEFINE CONSTANT
															  
struct  {
	volatile int8u RF:1;
    volatile int8u RFStart:1;
} Flag;

enum { ST_NRCVD = 0, ST_RCVD };

//FUNCTILOW PROTOTYPES
		void main		(void);
static	void init		(void);
static 	void tmr0_init	(void);
static 	void EXTint_int	(void);
static void disptitle	(void);
#endif


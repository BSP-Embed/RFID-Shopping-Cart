#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define INTDDR				DDRD
#define INTPORT				PORTD
#define INT0_PIN			PD2

//DEFINE CONSTANT


//FUNCTION PROTOTYPES
static void		init		(void);
static void		flagsinit	(void);
static void 	tmr2init	(void);
static void		EXT0init	(void);
static void 	disptitl 	(void);
static void		CartOp		(void);
static void		BillGen		(void);

#endif

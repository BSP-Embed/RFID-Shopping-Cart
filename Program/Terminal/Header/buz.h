#ifndef _BUZ_H
#define _BUZ_H

//INCLUDES
#include "includes.h"

// define constants
#define OFF_TIME	100

//DEFINE MACRO
#define buzon()		BUZ_PIN = LOW
#define buzoff()	BUZ_PIN = HIGH

//FUNCTION PROTOTYPES
void beep(int8u nbeep, int16u ontime);

#endif


#ifndef _LED_H
#define _LED_H

#include"includes.h"


//DEFINE LED PORT
#define LED		P0_0


//DEFINE MACRO
#define ledon()		LED = LOW
#define ledoff()	LED = HIGH


//FUNCTION PROTOTYPES
void blink(int8u nblink, int8u ontime);

#endif

/* led.c : LED interface programs */

#include "led.h"

void blink(int8u nblink, int8u ontime)
{
	while(nblink--){
		ledon();
		dlyms(ontime);
		ledoff();
		dlyms(100);
	}
}

	

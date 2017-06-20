/* buz.c: driver program for buzzer */
#include"buz.h"
void beep(int8u nbeep, int16u ontime){
	while(nbeep--)	{
		buzon();
		dlyms(ontime);
		buzoff();
		dlyms(OFF_TIME);
	}
}



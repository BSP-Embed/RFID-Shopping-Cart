/* main.c Main application program for traffic signal  */
# include "main.h"


char str[10];

void main(void)
{
	init();

	while (TRUE) {
		if (Flag.RF) {
			Flag.RF = FALSE;
			lcdclr();
			lcdws("Shopping Cart143");
			lcdr2();
			lcdws("S-AMOUNT: ");
			lcdws(str);
			lcdws("Rs");
			beep(1,100);
			EX1 = 1;
		}
	}
 }

static void init(void)
{
	RFPORT = 0xff;
	beep(2,100);
	lcdinit();
	tmr0_init();
	EXTint_int();
	disptitle();
}
static void disptitle(void)
{
	lcdclr();
	lcdws(" Mall of MYSORE");
}
static void tmr0_init(void)
{
	TMOD = TMOD & 0xf0 | 0x01;		/* TMR0 in mode1*/
	TH0 = 0x4B;
	TL0 = 0xFD;
	EA = ET0 = 1;
	TR0 = 1;
} 
static void tmr0ISR() interrupt 1 using 2
{
	static int8u i,j;

	TH0 = 0x4B;
	TL0 = 0xFD;

	 if (++i >= 2) {
		i = 0;
	
		if (++j >= 50)
			j = 0;
		switch(j) {
			case 0: case 2: ledon();  break;
			case 1: case 3: ledoff(); break;
		}
	}

} 

static void EXTint_int(void)
{
	EX1 = 1;		/* Enable external Interrupt 1 */
	IT1 = 1;		/* EDGE triggeres */
}
static void EXTintISR() interrupt 2 using 2
{
   static int8u i,j,state;
   static int8u RFData[4];
   char ch;

	RFData[i++] = RFPORT & 0xF0;

	if (i == 2)	{
		ch = (RFData[0] & 0xf0) | (RFData[1] >> 4);
		i = 0;
   		switch (state) {
			case  ST_NRCVD: if (ch == '<') 
								state = ST_RCVD;
							break;
			case ST_RCVD:
						str[j++] = ch;
						if (ch == '>') {
							EX1 = 0;
							str[j-1] = '\0';
							Flag.RF = TRUE;
							state = ST_NRCVD;
							i = j = 0;
						}
						break;
		}
	}
}
#include "main.h"

int8u item;
int8u AddRmv[5];
int16u tamt;

struct prod {
	char const prodname[16];
	int const prodprice;
};

struct prod items[4] = { " Fastrack Watch",1200,
						"    t-Shirt",499,
						"Parker Ball Pen",168,
						"  Axe perfume",220,
};

volatile struct  {
	volatile int8u RFIDtag:1;
	volatile int8u Sw:1;
}Flags;

extern int8u lcdptr;

int main(void)
{
	init();
	
	while (TRUE) {
		
		if (Flags.RFIDtag) {
			Flags.RFIDtag = FALSE;
			CartOp();
			EnUARTInt();
		}
		if (Flags.Sw) {
			Flags.Sw = FALSE;
			BillGen();
		}
		
		sleep();
	}
	return 0;
}
static void CartOp(void)
{
	 char amtstr[10];
	 
	 item = readtag();
	 switch(item)	{
		 case 1: case 2: case 3: case 4:
			 lcdclr();
			 lcdws(items[item-1].prodname);
			 lcdr2();
			 if(!AddRmv[item]) {
				 AddRmv[item] = TRUE;
				 tamt += items[item-1].prodprice;									
				 lcdws("   ITEM ADDED");
			 } else {
				 AddRmv[item] = 1;
				 tamt -= items[item-1].prodprice;
				 lcdws("  ITEM REMOVED");
			 }
			 beep(1,100);
			 dlyms(500);
			 lcdclrr(1);
			 lcdws("  Total Rs:");
			 itoa(tamt,amtstr);
			 lcdws(amtstr);
			 break;
		 default:
			 beep(1,250);
			 lcdclr();
			 lcdws("  PRODUCT HAS");
			 lcdr2();
			 lcdws(" BEEN EXPIRED!");
			 break;
	 }
 }


static void BillGen(void)
{
	char amtstr[10];
	int8u i;
	
	if (tamt != 0) {
		DisUARTInt();
		beep(1,250);
		lcdclr();
		lcdws("SHOPPING COMPLET");
		itoa(tamt,amtstr);
	
		trans(amtstr);

		lcdr2();
		lcdws("Bill Gen @ Term2");
		beep(1,100);
		dlyms(10000);
		lcdclr();
		lcdws("  Thank you for");
		lcdr2();
		lcdws("    Shopping.");
		beep(1,100);
		tamt = 0;					/* Reset Flags */
		for (i = 0; i < 6; i++)
			AddRmv[i] = 0;
		
		dlyms(10000);
		beep(1,100);
		disptitl();
	
		EnUARTInt();
	}
}

	
static void init(void)
{
	buzinit();
	rfinit();
	beep(2,100);
	ledinit();
	
	flagsinit();	
	lcdinit();
	uartinit();
	EnUARTInt();
	tmr2init();
	EXT0init();
	disptitl();
	sei();
}

static void flagsinit(void)
{
	int8u i;
	
	Flags.RFIDtag= FALSE;
	Flags.Sw = FALSE;
	
	tamt = 0;					/* Reset Flags */
	for (i = 0; i < 6; i++)
	AddRmv[i] = 0;
}
static void EXT0init(void)
{
	INTDDR 	&= ~_BV(INT0_PIN);
	INTPORT |= _BV(INT0_PIN);
	
	GICR |= _BV(INT0);			//ENABLE EXTERNAL INTERRUPT
	MCUCR |= _BV(ISC01);		//FALLING EDGE INTERRUPT

}
static void disptitl(void)
{
	lcdclr();
	lcdws(" SHOPPING CART");
	lcdr2();
	lcdws("TOTAL AMOUNT: 0");
}
static void tmr2init(void)
{
	TCNT2   = 75;
	TIMSK   |= _BV(TOIE2);			//ENABLE OVERFLOW INTERRUPT
	TCCR2  |=  _BV(CS22) | _BV(CS21) | _BV(CS20); /* PRESCALAR BY 256 */
}

/* overflows at every 25msec */
ISR(TIMER2_OVF_vect)
{
	static int8u i,j,k;
	TCNT2 = 75;

	if (++i >= 200) i = 0;
	switch(i) {
		case 0: case 5: ledon(); break;
		case 1: case 6: ledoff(); break;
	}
}
ISR(INT0_vect)
{
	Flags.Sw = TRUE;
	GICR |= _BV(INT0);
}
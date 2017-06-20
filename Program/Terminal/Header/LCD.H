#ifndef LCD_H
#define LCD_H

//INCLUDES
#include "includes.h"

//DEFINE CONSTANT

#define LCD_DOT		'.'
#define LCD_SPC		' '

//#define LCD_20X4		/* 20*4 LCD */


//DEFINES PORT/PINS
#define LCD_EN_PIN			P2_3
#define LCD_RS_PIN			P2_2
#define LCD_DATA_PORT		P2


//DEFINE MACROS 


//DEFINE PROTOTYPES
static	void lcden		(void);
		void lcdwc		(int8u command);
		void lcdwd		(int8u ascii);
		void lcdws		(int8u *s);
static 	void lcdwb		(int8u  LCDData);
		void lcdinit	(void);
		void lcddinit	(void);
static 	void lcdrs		(void);
		void lcdclrr	(int8u rowno);
		void lcdclr		(void);
		void lcdr1		();
		void lcdr2		();
		void itoa		(signed int n, char s[]);
		void reverse	(char s[]);
		void lcdwint	(int8u loc,signed int x);
	#if defined FLOAT_T0_STRING > 0
		void ftoa		(float n, char s[]);
	#endif
		void lcdwbin	(int8u no);
#endif


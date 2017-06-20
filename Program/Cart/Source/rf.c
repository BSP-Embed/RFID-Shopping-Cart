#include "rf.h"

void rfinit(void)
{
	RFDDR = OUTPUT_PORT;
	RFPORT = 0X08;

}

void trans(const char *str)
{
	int8u i;
	
	RFPORT = RFPORT & 0X0F | ('<' & 0xF0);
	EnRF();
	RFPORT = RFPORT & 0X0F | ('<' << 4);
	EnRF();
	
	for (i = 0; str[i] != '\0'; i++) {
		RFPORT = RFPORT & 0X0F | (str[i] & 0xF0);
		EnRF();
		RFPORT = RFPORT & 0X0F | (str[i] << 4);
		EnRF();
	}
	
	RFPORT = RFPORT & 0X0F | ('>' & 0xF0);
	EnRF();
	RFPORT = RFPORT & 0X0F | ('>' << 4);
	EnRF();
}
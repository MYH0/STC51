/*
 * Ê±ÖÓ(DS1302)Ä£¿é
 *
 * AUTHOR			WHAT		DATE
 * Huafeng Lin		created 	2011/10/08
 * Huafeng Lin		modified 	2011/10/08
 *
 */

#include "Common.h"
#include "Lcd.h"
#include "Clock.h"

void main()
{
	init_1602();
	display_1602(" Lcsoft  Studio ", 0, 0);
	delay_ms(500);
	reset_1602();
	init_clock();
	while(1)
	{
		display_clock();
	}
}

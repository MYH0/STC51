/*
 * ¹«¹²Ä£¿é
 *
 * AUTHOR			WHAT		DATE
 * Huafeng Lin		created 	2011/10/08
 * Huafeng Lin		modified 	2011/10/08
 *
 */

#include <Common.h>

void delay_ms(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		 for(b=100;b>0;b--);
}

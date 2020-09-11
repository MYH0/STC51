#include<reg52.h>
#include"DelayMs.h"

sbit d1 = P1 ^ 0;

uchar num = 0;

#include"Disaplay_digital-tube1.h"
#include"Independent_Keyboard.h"

void main()
{
	wx = 1;
	P0 = weixuan[0];
	wx = 0;

	P3 = 0xff;
	d1 = 1;

	while (1)
	{
		independent_key();

		dx = 1;
		P0 = duanxuan[num];
		dx = 0;
	}
}

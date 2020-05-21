#include<reg52.h>

sbit wx = P2 ^ 7;
sbit dx = P2 ^ 6;

uchar code duanxuan[] = { 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
0x77,0x7c,0x39,0x5e,0x79,0x71 };
uint i = 0, n = 0;

#include"timer0_interrupt_1.h"

void main()
{
	EA = 1;
	ET0 = 1;
	TMOD = 0X01;
	TH0 = (65535 - 50000) / 256;
	TL0 = (65535 - 50000) % 256;
	TR0 = 1;
	wx = 1;
	P0 = 0XC0;
	wx = 0;
	dx = 1;
	P0 = duanxuan[0];
	dx = 0;

	while (1)
	{
		if (n == 20)
		{
			n = 0;
			i++;
			if (i == 16)
				i = 0;
			dx = 1;
			P0 = duanxuan[i];
			dx = 0;
		}
	}
}

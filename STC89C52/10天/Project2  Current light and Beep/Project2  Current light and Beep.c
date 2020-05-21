#include <STC89C5XRC.H>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
#include<DelayMs.h>

sbit beep = P2 ^ 3;

void main()
{
	uint temp;
	temp = 0xfe;
	beep = 0;
	while (1)
	{
		P1 = temp;
		temp = _crol_(temp, 1);	
		DelayMs(80);
	}
}
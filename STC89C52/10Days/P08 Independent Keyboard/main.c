#include <STC89C5XRC.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"

void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	wx = 1;
	P0 = weixuan[0];
	wx = 0;

	P3 = 0xff;
	LED0_Off;

	while (1)
	{
		Keyboard_Independent();

		dx = 1;
		P0 = duanxuan[num];
		dx = 0;

		LED0_Off;
	}
}

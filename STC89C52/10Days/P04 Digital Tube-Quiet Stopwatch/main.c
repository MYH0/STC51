#include <STC89C5XRC.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"

void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	T0_Init(50000);
	TR0 = 1;
	DigitalTube_Display_1bit(6, 0);
	
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

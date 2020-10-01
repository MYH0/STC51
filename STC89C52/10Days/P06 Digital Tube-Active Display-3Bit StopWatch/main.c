#include <STC89C5XRC.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"

void main()
{
	STC89_TX_1C_Board_IO_Base_Init();
	
	T0_Init(50000);
	TR0 = 1;
	while (1)
	{
		if (n == 20)
		{
			n = 0;
			shu++;
			if (shu == 1000)
				shu = 0;

		}
		DigitalTube_Display_num_3bit(shu);
	}
}


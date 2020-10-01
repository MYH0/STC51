#include <STC89C5XRC.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"

void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	P1 = temp;
	TMOD = 0X11;
	T0_Init(50000);
	T1_Init(50000);
	TR0 = 1;
	TR1 = 1;

	while (1)
	{
		if (flag_t1 == 0)
			DigitalTube_Display_num_3bit(shu);
		else
			DigitalTube_Display_Str_HELLO();
		
	}
}
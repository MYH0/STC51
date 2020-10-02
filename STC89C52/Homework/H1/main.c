#include <STC89C5XRC.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"
void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	EX0_Init();

	T0_Init(50000);
	TMOD = 0X01;

	while (1)
	{
		DigitalTube_Display_1bit(0, 0);
		Delay_s_1();
		DigitalTube_Display_1bit(1, 1);
		Delay_s_1();
		DigitalTube_Display_1bit(2, 2);
		Delay_s_1();
		DigitalTube_Display_1bit(3, 3);
		Delay_s_1();
		DigitalTube_Display_1bit(4, 4);
		Delay_s_1();
		DigitalTube_Display_1bit(5, 5);
		Delay_s_1();

	}
}
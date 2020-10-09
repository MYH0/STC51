#include <STC89C5XRC.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"

void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	T0_Init(200);
	TMOD = 0X01;
	TR0 = 1;

	LED0_On;

	while (1)
	{

	}
}

#include <STC89C5XRC.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"
void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	EX1_Init();

	while (1)
	{
		LED1_On;
	}
}
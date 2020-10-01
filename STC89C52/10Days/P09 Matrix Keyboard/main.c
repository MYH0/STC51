#include <STC89C5XRC.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"

void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	num = 41;

	while (1)
	{
		Keyboard_4x4();
		DigitalTube_Display_1bit(6, num);
	}
}

#include <STC89C5XRC.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"
void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	UART1_Init();

	while (1)
	{
		Keyboard_4x4();
		DigitalTube_Display_1bit(5, Digital_Tube_Char_Num);
		P3 = 0xff;
		if (uart_flag == 1)
		{
			uart_flag = 0;
			SBUF = UART1_Char;
			while (!TI);
			TI = 0;
			UART1_Char = 48;
		}
		
	}
}


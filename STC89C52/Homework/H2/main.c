#include <STC12C5A60S2.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"

void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	T0_Init(200);
	TMOD = 0X01;
	TR0 = 1;

	

	while (1)
	{
		LED0_On;
		Delay_ms(500);
		LED0_Off;

		LED1_On;
		Delay_ms(500);
		LED1_Off;

		LED2_On;
		Delay_ms(500);
		LED2_Off;

		LED3_On;
		Delay_ms(500);
		LED3_Off;

		LED4_On;
		Delay_ms(500);
		LED4_Off;

		LED5_On;
		Delay_ms(500);
		LED5_Off;

		LED6_On;
		Delay_ms(500);
		LED6_Off;

		LED7_On;
		Delay_ms(500);
		LED7_Off;



	}
}

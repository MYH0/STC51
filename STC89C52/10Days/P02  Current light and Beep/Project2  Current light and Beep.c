#include <STC89C5XRC.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"

uint led_staus;

void main()
{
	STC89_TX_1C_Board_IO_Base_Init();
	
	led_staus = 0xfe;
	Beep_On;
	while (1)
	{
		P1 = led_staus;
		led_staus = _crol_(led_staus, 1);
		Delay_ms(80);
	}
}
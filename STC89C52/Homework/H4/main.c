#include <STC89C5XRC.H>
//#include <STC12C5A60S2.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"

void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	DS1302_Init();
	//DS1302_W_Time();
	DS1302_Check();

	while (1)
	{
		DS1302_R_Time();

		hour_shi = TimeBuff[4] / 10;
		hour_ge = TimeBuff[4] % 10;
		min_shi = TimeBuff[5] / 10;
		min_ge = TimeBuff[5] % 10;
		sec_shi = TimeBuff[6] / 10;
		sec_ge = TimeBuff[6] % 10;

		DigitalTube_Display_6bit(hour_shi, hour_ge, min_shi, min_ge, sec_shi, sec_ge);
	}
}
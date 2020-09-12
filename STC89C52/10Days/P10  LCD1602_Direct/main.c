#include <STC89C5XRC.H>
#include <intrins.h>
#include <math.h>
#include "MenYuhan_Drivers_STC89.h"
void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	LCD1602_Init();
	LCD1602_Display_Str(0, 0, LCD1602_Str0);
	LCD1602_Display_Str(1, 0, LCD1602_Str1);
	LCD1602_Display_Num(1, 13, LCD1602_Num0, 3);

	while (1)
	{

	}
}
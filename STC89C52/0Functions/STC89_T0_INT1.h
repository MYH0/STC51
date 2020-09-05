#pragma once

void Init_T0(uint timer0_long)
{
	ET0 = 1;
	TMOD = 0X01;
	TH0 = (65536 - timer0_long) / 256;
	TL0 = (65536 - timer0_long) % 256;
}

void T0_INT() interrupt 1
{
	/*****开始修改定时的时长*****/
	uint time_long0;	
	time_long0 = 50000; 
	/*****结束修改定时的时长*****/

	/*****开始装载定时的时长*****/
	TH0 = (65536 - time_long0) / 256;
	TL0 = (65536 - time_long0) % 256;
	/*****结束装载定时的时长*****/

	/*****开始后续操作**********/

	

	/*****结束后续操作**********/
}
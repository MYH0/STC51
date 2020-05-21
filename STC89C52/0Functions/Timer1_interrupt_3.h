//请根据实际需要设置TMOD和TR和EA
void init_timer1(uint timer1_long)
{
//	EA = 1;
	ET1 = 1;
//	TMOD = 0X10;
	TH1 = (65536 - timer1_long) / 256;
	TL1 = (65536 - timer1_long) % 256;
//	TR1 = 1;
}

void timer1() interrupt 3
{
	/*****开始修改定时的时长*****/

	uint time_long1;
	time_long1 = 50000;

	/*****结束修改定时的时长*****/

	TH1 = (65536 - time_long1) / 256;
	TL1 = (65536 - time_long1) % 256;

	/*****开始后续操作*****/

	

	/*****结束后续操作*****/
}

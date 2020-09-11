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

	t1++;
	if (t1 == 2)
	{
		t1 = 0;
		shu--;
		if (shu == 398)
		{
			TR1 = 0;
			TR0 = 0;
			TH0 = (65536 - 50000) / 256;
			TL0 = (65536 - 50000) % 256;
			t0 = 0;
			TR0 = 1;
			P1 = 0XFF;
			flag_t0 = 1;

		}
	}

	/*****结束后续操作*****/
}

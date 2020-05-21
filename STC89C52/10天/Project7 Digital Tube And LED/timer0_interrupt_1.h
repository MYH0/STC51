//请根据实际需要设置TMOD和TR和EA
void init_timer0(uint timer0_long)
{
//	EA = 1;
	ET0 = 1;
//	TMOD = 0X01;
	TH0 = (65536 - timer0_long) / 256;
	TL0 = (65536 - timer0_long) % 256;
//	TR0 = 1;
}

void timer0() interrupt 1
{
	/*****开始修改定时的时长*****/

	uint time_long0;	
	time_long0 = 50000; 

	/*****结束修改定时的时长*****/

	TH0 = (65536 - time_long0) / 256;
	TL0 = (65536 - time_long0) % 256;

	/*****开始后续操作*****/

	t0++;
	if (flag_t0 == 0)
	{
		if (t0 == 10)
		{
			t0 = 0;
			temp = _crol_(temp, 1);
			P1 = temp;
		}
	}
	else
	{
		if (t0 % 4 == 0)
			P1 = ~P1;
		if (t0 == 60)
		{
			TR0 = 0;
			t0 = 0;
			P1 = 0xff;
			flag_t1 = 1;
		}
	}

	/*****结束后续操作*****/
}
/**********************************T0初始化*********************************/
void T0_Init(uint timer0_long)
{
//	EA = 1;
	ET0 = 1;
//	TMOD = 0X01;
	TH0 = (65536 - timer0_long) / 256;
	TL0 = (65536 - timer0_long) % 256;
//	TR0 = 1;
}
/**********************************功能定义**********************************/
void T0_INT_Func()
{
	pwm_count++;
	if (pwm_count >= 5)
	{
		pwm_count = 0;
		period_count++;
		if (period_count >= 60)
		{
			period_count = 0;
			led_num++;
			if (led_num >= 8)
				led_num = 0;
		}
	}

	if (pwm_count == 0)
	{
		switch (led_num)
		{
		case 0:LED0_On; break;
		case 1:LED1_On; break;
		case 2:LED2_On; break;
		case 3:LED3_On; break;
		case 4:LED4_On; break;
		case 5:LED5_On; break;
		case 6:LED6_On; break;
		case 7:LED7_On; break;
		default:break;
		}
	}
	else
		LED_ALL_Off;

}
/************************************中断************************************/
void T0_INT() interrupt 1
{
	/*****修改定时的时长*****/
	uint time_long0;	
	time_long0 = 200; 
	/*****装载定时的时长*****/
	TH0 = (65536 - time_long0) / 256;
	TL0 = (65536 - time_long0) % 256;
	/*****中断功能*****/
	T0_INT_Func();
}

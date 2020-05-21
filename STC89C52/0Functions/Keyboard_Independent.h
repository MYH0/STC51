/*开始定义要使用的按键*/

sbit key_s2 = P3 ^ 4;

/*结束定义要使用的按键*/

void Keyboard_Independent()
{
	if (key_s2 == 0)			//有按下的倾向
	{
		delay_ms(5);
		if (key_s2 == 0)		//确实按下去了
		{
			/*开始执行按下后的操作*/
			
			

			/*结束执行按下后的操作*/
		}
		while (key_s2 != 1);	 //有抬起的倾向
		delay_ms(5);
		while (key_s2 != 1);	 //确实抬起了
	}
	else						 //根本就没有按下
	{
		/*开始执行不按的操作*/

		

		/*结束执行不按的操作*/
	}
}
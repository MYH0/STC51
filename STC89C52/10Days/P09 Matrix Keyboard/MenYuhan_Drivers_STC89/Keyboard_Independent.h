/**************************************IO定义******************************/
//sbit Key_i0 = P3 ^ 4;
//sbit Key_i1 = P3 ^ 5;
//sbit Key_i2 = P3 ^ 6;
//sbit Key_i3 = P3 ^ 7;
/**************************************功能定义******************************/
void Key_i0_Func()
{

}

void Key_i1_Func()
{

}

void Key_i2_Func()
{

}

void Key_i3_Func()
{

}
/**************************************操作*********************************/
void Keyboard_Independent()
{
	if (Key_i0 == 0)			//有按下的倾向
	{
		Delay_ms_5();
		if (Key_i0 == 0)		//确实按下去了
		{
			Key_i0_Func();
		}
		while (Key_i0 != 1);	 //有抬起的倾向
		Delay_ms_5();
		while (Key_i0 != 1);	 //确实抬起了
	}

	if (Key_i1 == 0)			//有按下的倾向
	{
		Delay_ms_5();
		if (Key_i1 == 0)		//确实按下去了
		{
			Key_i1_Func();
		}
		while (Key_i1 != 1);	 //有抬起的倾向
		Delay_ms_5();
		while (Key_i1 != 1);	 //确实抬起了
	}

	if (Key_i2 == 0)			//有按下的倾向
	{
		Delay_ms_5();
		if (Key_i2 == 0)		//确实按下去了
		{
			Key_i2_Func();
		}
		while (Key_i2 != 1);	 //有抬起的倾向
		Delay_ms_5();
		while (Key_i2 != 1);	 //确实抬起了
	}

	if (Key_i3 == 0)			//有按下的倾向
	{
		Delay_ms_5();
		if (Key_i3 == 0)		//确实按下去了
		{
			Key_i3_Func();
		}
		while (Key_i3 != 1);	 //有抬起的倾向
		Delay_ms_5();
		while (Key_i3 != 1);	 //确实抬起了
	}

}
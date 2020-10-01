//用于4*4矩阵键盘，接口为P3
/***************************************按键功能定义************************************/
void Key0_Func()
{
	num = 0;
}

void Key1_Func()
{
	num = 1;
}

void Key2_Func()
{
	num = 2;
}

void Key3_Func()
{
	num = 3;
}

void Key4_Func()
{
	num = 4;
}

void Key5_Func()
{
	num = 5;
}

void Key6_Func()
{
	num = 6;
}

void Key7_Func()
{
	num = 7;
}

void Key8_Func()
{
	num = 8;
}

void Key9_Func()
{
	num = 9;
}

void Key10_Func()
{
	num = 10;
}

void Key11_Func()
{
	num = 11;
}

void Key12_Func()
{
	num = 12;
}

void Key13_Func()
{
	num = 13;
}

void Key14_Func()
{
	num = 14;
}

void Key15_Func()
{
	num = 15;
}
/******************************************操作****************************************/
void Keyboard_4x4()
{
	uint temp=0;

	P3 = 0xfe;                      //检测P30这一行的按键
	temp = P3;						//读取P3的值
	temp = temp & 0xf0;
	if (temp != 0xf0)			//有按下的倾向
	{
		Delay_ms_5();				//等一会
		temp = P3;					//再次读取P3的值
		temp = temp & 0xf0;
		if (temp != 0xf0)		//确实按下了
		{
			/*****开始按下后的操作*****/
			temp = P3;
			switch (temp)
			{
			case 0xee:Key0_Func();
				break;
			case 0xde:Key1_Func();
				break;
			case 0xbe:Key2_Func();
				break;
			case 0x7e:Key3_Func();
				break;
			}
			/********结束按下后的操作********/

			/********检测抬起********/
			while (temp != 0xf0)      //有抬起的倾向
			{
				temp = P3;			  //重新读取P3
				temp = temp & 0xf0;
			}
			Delay_ms_5();
			while (temp != 0xf0)      //再检测抬起的倾向
			{
				temp = P3;			  //重新读取P3
				temp = temp & 0xf0;
			}
		}
	}

	P3 = 0xfd;
	temp = P3;
	temp = temp & 0xf0;
	if (temp != 0xf0)
	{
		Delay_ms_5();
		temp = P3;
		temp = temp & 0xf0;
		if (temp != 0xf0)
		{
			/*****开始按下后的操作*****/
			temp = P3;
			switch (temp)
			{
			case 0xed:Key4_Func();
				break;
			case 0xdd:Key5_Func();
				break;
			case 0xbd:Key6_Func();
				break;
			case 0x7d:Key7_Func();
				break;
			}
			/*****结束按下后的操作*****/

			/********检测抬起********/
			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
			Delay_ms_5();
			while (temp != 0xf0)      //再检测抬起的倾向
			{
				temp = P3;			  //重新读取P3
				temp = temp & 0xf0;
			}
		}
	}

	P3 = 0xfb;
	temp = P3;
	temp = temp & 0xf0;
	if (temp != 0xf0)
	{
		Delay_ms_5();
		temp = P3;
		temp = temp & 0xf0;
		if (temp != 0xf0)
		{
			/*****开始按下后的操作*****/

			temp = P3;
			switch (temp)
			{
			case 0xeb:Key8_Func();
				break;
			case 0xdb:Key9_Func();
				break;
			case 0xbb:Key10_Func();
				break;
			case 0x7b:Key11_Func();
				break;
			}

			/********结束按下后的操作********/

			/********检测抬起********/

			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
			Delay_ms_5();
			while (temp != 0xf0)      //再检测抬起的倾向
			{
				temp = P3;			  //重新读取P3
				temp = temp & 0xf0;
			}
		}
	}

	P3 = 0xf7;
	temp = P3;
	temp = temp & 0xf0;
	if (temp != 0xf0)
	{
		Delay_ms_5();
		temp = P3;
		temp = temp & 0xf0;
		if (temp != 0xf0)
		{
			/*****开始按下后的操作*****/
			temp = P3;
			switch (temp)
			{
			case 0xe7:Key12_Func();
				break;
			case 0xd7:Key13_Func();
				break;
			case 0xb7:Key14_Func();
				break;
			case 0x77:Key15_Func();
				break;
			}
			/********结束按下后的操作********/

			/********检测抬起********/
			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
			Delay_ms_5();
			while (temp != 0xf0)      //再检测抬起的倾向
			{
				temp = P3;			  //重新读取P3
				temp = temp & 0xf0;
			}
		}
	}
}

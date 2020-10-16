//用于4*4矩阵键盘，接口为P3
/***************************************按键功能定义************************************/
void Key0_Func()
{
	Digital_Tube_Char_Num = 0;
	UART1_Char += Digital_Tube_Char_Num;
}

void Key1_Func()
{
	Digital_Tube_Char_Num = 1;
	UART1_Char += Digital_Tube_Char_Num;
}

void Key2_Func()
{
	Digital_Tube_Char_Num = 2;
	UART1_Char += Digital_Tube_Char_Num;
}

void Key3_Func()
{
	Digital_Tube_Char_Num = 3;
	UART1_Char += Digital_Tube_Char_Num;
}

void Key4_Func()
{
	Digital_Tube_Char_Num = 4;
	UART1_Char += Digital_Tube_Char_Num;
}

void Key5_Func()
{
	Digital_Tube_Char_Num = 5;
	UART1_Char += Digital_Tube_Char_Num;
}

void Key6_Func()
{
	Digital_Tube_Char_Num = 6;
	UART1_Char += Digital_Tube_Char_Num;
}

void Key7_Func()
{
	Digital_Tube_Char_Num = 7;
	UART1_Char += Digital_Tube_Char_Num;
}

void Key8_Func()
{
	Digital_Tube_Char_Num = 8;
	UART1_Char += Digital_Tube_Char_Num;
}

void Key9_Func()
{
	Digital_Tube_Char_Num = 9;
	UART1_Char += Digital_Tube_Char_Num;
}

void Key10_Func()
{
	Digital_Tube_Char_Num = 10;
	UART1_Char += Digital_Tube_Char_Num;
	UART1_Char += 7;
}

void Key11_Func()
{
	Digital_Tube_Char_Num = 11;
	UART1_Char += Digital_Tube_Char_Num;
	UART1_Char += 7;
}

void Key12_Func()
{
	Digital_Tube_Char_Num = 12;
	UART1_Char += Digital_Tube_Char_Num;
	UART1_Char += 7;
}

void Key13_Func()
{
	Digital_Tube_Char_Num = 13;
	UART1_Char += Digital_Tube_Char_Num;
	UART1_Char += 7;
}

void Key14_Func()
{
	Digital_Tube_Char_Num = 14;
	UART1_Char += Digital_Tube_Char_Num;
	UART1_Char += 7;
}

void Key15_Func()
{
	Digital_Tube_Char_Num = 15;
	UART1_Char += Digital_Tube_Char_Num;
	UART1_Char += 7;
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
			uart_flag = 1;
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
			uart_flag = 1;
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
			uart_flag = 1;
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
			uart_flag = 1;
		}
	}
}

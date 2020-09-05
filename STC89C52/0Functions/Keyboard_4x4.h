/********************************************************/
//用于4*4矩阵键盘，接口为P3
/********************************************************/
uchar Keyboard_4x4()
{
	P3 = 0xfe;                      //检测P30这一行的按键
	temp = P3;						//读取P3的值
	temp = temp & 0xf0;
	if (temp != 0xf0)			//有按下的倾向
	{
		delay_ms(5);				//等一会
		temp = P3;					//再次读取P3的值
		temp = temp & 0xf0;
		if (temp != 0xf0)		//确实按下了
		{
			/*****开始按下后的操作*****/

			temp = P3;
			switch (temp)
			{
			case 0xee:num = 0;
				break;
			case 0xde:num = 1;
				break;
			case 0xbe:num = 2;
				break;
			case 0x7e:num = 3;
				break;
			}

			/********结束按下后的操作********/

			/********检测抬起********/

			while (temp != 0xf0)      //有抬起的倾向
			{
				temp = P3;			  //重新读取P3
				temp = temp & 0xf0;
			}
			delay_ms(5);
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
		delay_ms(5);
		temp = P3;
		temp = temp & 0xf0;
		if (temp != 0xf0)
		{
			/*****开始按下后的操作*****/

			temp = P3;
			switch (temp)
			{
			case 0xed:num = 4;
				break;
			case 0xdd:num = 5;
				break;
			case 0xbd:num = 6;
				break;
			case 0x7d:num = 7;
				break;
			}

			/*****结束按下后的操作*****/

			/********检测抬起********/

			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
			delay_ms(5);
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
		delay_ms(5);
		temp = P3;
		temp = temp & 0xf0;
		if (temp != 0xf0)
		{
			/*****开始按下后的操作*****/

			temp = P3;
			switch (temp)
			{
			case 0xeb:num = 8;
				break;
			case 0xdb:num = 9;
				break;
			case 0xbb:num = 10;
				break;
			case 0x7b:num = 11;
				break;
			}

			/********结束按下后的操作********/

			/********检测抬起********/

			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
			delay_ms(5);
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
		delay_ms(5);
		temp = P3;
		temp = temp & 0xf0;
		if (temp != 0xf0)
		{
			/*****开始按下后的操作*****/

			temp = P3;
			switch (temp)
			{
			case 0xe7:num = 12;
				break;
			case 0xd7:num = 13;
				break;
			case 0xb7:num = 14;
				break;
			case 0x77:num = 15;
				break;
			}

			/********结束按下后的操作********/

			/********检测抬起********/

			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
			delay_ms(5);
			while (temp != 0xf0)      //再检测抬起的倾向
			{
				temp = P3;			  //重新读取P3
				temp = temp & 0xf0;
			}
		}
	}
	return num;
}
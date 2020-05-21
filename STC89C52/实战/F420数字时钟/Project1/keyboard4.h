sbit Key1_P = P3 ^ 2;		// 设置时间按键
sbit Key2_P = P3 ^ 3;			// 设置闹钟按键
sbit Key3_P = P3 ^ 4;		// 秒表功能按键
sbit Key4_P = P3 ^ 5;			// 子功能按键-
sbit Key5_P = P3 ^ 6;		// 子功能按键+

/*********************************************************/
// 按键扫描(设置时间)
/*********************************************************/
void KeyScanf1()
{
	if (Key1_P == 0)
	{
		LcdWriteCmd(0x0f);			// 启动光标闪烁
		LcdGotoXY(0, 3);					// 定位光标到年份闪烁
		DelayMs(10);				// 延时等待，消除按键按下的抖动
		while (!Key1_P);					// 等待按键释放
		DelayMs(10);				// 延时等待，消除按键松开的抖动

		while (1)							//调整年份
		{
			if (Key4_P == 0)						// 如果减按键被下去
			{
				if (TimeBuff[0] > 0)					// 判断年份是否大于0		
					TimeBuff[0]--;				// 是的话就减去1
				LcdGotoXY(0, 2);						// 光标定位到年份的位置
				LcdPrintNum(TimeBuff[0]);		// 刷新显示改变后的年份
				LcdGotoXY(0, 3);						// 定位光标到年份闪烁
				DelayMs(300);					// 延时0.3秒左右
			}
			if (Key5_P == 0)						// 如果加按键被下去
			{
				if (TimeBuff[0] < 99)				// 判断年份是否小于99
					TimeBuff[0]++;					// 是的话就加上1
				LcdGotoXY(0, 2);					// 光标定位到年份的位置
				LcdPrintNum(TimeBuff[0]);			// 刷新显示改变后的年份
				LcdGotoXY(0, 3);					// 定位光标到年份闪烁
				DelayMs(300);						// 延时0.3秒左右
			}
			if (Key1_P == 0)
			{
				break;
			}
		}

		LcdGotoXY(0, 6);					// 定位光标到月份闪烁
		DelayMs(10);						// 延时等待，消除按键按下的抖动
		while (!Key1_P);					// 等待按键释放
		DelayMs(10);						// 延时等待，消除按键松开的抖动

		while (1)						//调整月份
		{
			if (Key4_P == 0)						// 如果减按键被下去
			{
				if (TimeBuff[1] > 1)				// 判断月份是否大于1		
					TimeBuff[1]--;					// 是的话就减去1
				LcdGotoXY(0, 5);					// 光标定位到月份的位置
				LcdPrintNum(TimeBuff[1]);			// 刷新显示改变后的月份
				LcdGotoXY(0, 6);					// 定位光标到月份闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key5_P == 0)						// 如果加按键被下去
			{
				if (TimeBuff[1] < 12)				// 判断月份是否小于12
					TimeBuff[1]++;					// 是的话就加上1
				LcdGotoXY(0, 5);					// 光标定位到月份的位置
				LcdPrintNum(TimeBuff[1]);			// 刷新显示改变后的月份
				LcdGotoXY(0, 6);					// 定位光标到月份闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key1_P == 0)
			{
				break;
			}
		}

		LcdGotoXY(0, 9);					// 定位光标到日期闪烁
		DelayMs(10);						// 延时等待，消除按键按下的抖动
		while (!Key1_P);					// 等待按键释放
		DelayMs(10);						// 延时等待，消除按键松开的抖动

		while (1)								//调整日期
		{
			if (Key4_P == 0)						// 如果减按键被下去
			{
				if (TimeBuff[2] > 1)				// 判断日期是否大于1		
					TimeBuff[2]--;					// 是的话就减去1
				LcdGotoXY(0, 8);					// 光标定位到日期的位置
				LcdPrintNum(TimeBuff[2]);			// 刷新显示改变后的日期
				LcdGotoXY(0, 9);					// 定位光标到日期闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key5_P == 0)						// 如果加按键被下去
			{
				if (TimeBuff[2] < 31)				// 判断日期是否小于31
					TimeBuff[2]++;					// 是的话就加上1
				LcdGotoXY(0, 8);					// 光标定位到日期的位置
				LcdPrintNum(TimeBuff[2]);			// 刷新显示改变后的日期
				LcdGotoXY(0, 9);					// 定位光标到日期闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key1_P == 0)
			{
				break;
			}
		}

		LcdGotoXY(0, 15);				// 定位光标到星期闪烁
		DelayMs(10);						// 延时等待，消除按键按下的抖动
		while (!Key1_P);					// 等待按键释放
		DelayMs(10);						// 延时等待，消除按键松开的抖动

		while (1)							//调整星期
		{
			if (Key4_P == 0)						// 如果减按键被下去
			{
				if (TimeBuff[3] > 1)				// 判断星期是否大于1		
					TimeBuff[3]--;					// 是的话就减去1
				LcdGotoXY(0, 12);				// 光标定位到星期的位置
				LcdPrintWeek(TimeBuff[3]);			// 刷新显示改变后的星期
				LcdGotoXY(0, 15);				// 定位光标到星期闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key5_P == 0)						// 如果加按键被下去
			{
				if (TimeBuff[3] < 7)				// 判断星期是否小于7
					TimeBuff[3]++;					// 是的话就加上1
				LcdGotoXY(0, 12);				// 光标定位到星期的位置
				LcdPrintWeek(TimeBuff[3]);			// 刷新显示改变后的星期
				LcdGotoXY(0, 15);				// 定位光标到星期闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key1_P == 0)
			{
				break;
			}
		}

		LcdGotoXY(1, 5);					// 定位光标到小时闪烁
		DelayMs(10);						// 延时等待，消除按键按下的抖动
		while (!Key1_P);					// 等待按键释放
		DelayMs(10);						// 延时等待，消除按键松开的抖动

		while (1)								//调整小时
		{
			if (Key4_P == 0)							// 如果减按键被下去
			{
				if (TimeBuff[4] > 0)					// 判断小时是否大于0
					TimeBuff[4]--;						// 是的话就减去1
				LcdGotoXY(1, 4);						// 光标定位到小时的位置
				LcdPrintNum(TimeBuff[4]);				// 刷新显示改变后的小时
				LcdGotoXY(1, 5);						// 定位光标到小时闪烁
				DelayMs(300);							// 延时0.3秒左右
			}

			if (Key5_P == 0)							// 如果加按键被下去
			{
				if (TimeBuff[4] < 23)					// 判断小时是否小于23
					TimeBuff[4]++;						// 是的话就加上1
				LcdGotoXY(1, 4);						// 光标定位到小时的位置
				LcdPrintNum(TimeBuff[4]);				// 刷新显示改变后的小时
				LcdGotoXY(1, 5);						// 定位光标到小时闪烁
				DelayMs(300);							// 延时0.3秒左右
			}

			if (Key1_P == 0)
			{
				break;
			}
		}

		LcdGotoXY(1, 8);					// 定位光标到分钟闪烁
		DelayMs(10);						// 延时等待，消除按键按下的抖动
		while (!Key1_P);					// 等待按键释放
		DelayMs(10);						// 延时等待，消除按键松开的抖动

		while (1)							//调整分钟
		{
			if (Key4_P == 0)						// 如果减按键被下去
			{
				if (TimeBuff[5] > 0)				// 判断分钟是否大于0
					TimeBuff[5]--;					// 是的话就减去1
				LcdGotoXY(1, 7);					// 光标定位到分钟的位置
				LcdPrintNum(TimeBuff[5]);			// 刷新显示改变后的分钟
				LcdGotoXY(1, 8);					// 定位光标到分钟闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key5_P == 0)						// 如果加按键被下去
			{
				if (TimeBuff[5] < 59)				// 判断分钟是否小于59
					TimeBuff[5]++;					// 是的话就加上1
				LcdGotoXY(1, 7);					// 光标定位到分钟的位置
				LcdPrintNum(TimeBuff[5]);			// 刷新显示改变后的分钟
				LcdGotoXY(1, 8);					// 定位光标到分钟闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key1_P == 0)
			{
				break;
			}
		}

		LcdGotoXY(1, 11);				// 定位光标到秒钟闪烁
		DelayMs(10);						// 延时等待，消除按键按下的抖动
		while (!Key1_P);					// 等待按键释放
		DelayMs(10);						// 延时等待，消除按键松开的抖动

		while (1)							//调整秒钟
		{
			if (Key4_P == 0)						// 如果减按键被下去
			{
				if (TimeBuff[6] > 0)					// 判断秒钟是否大于0
					TimeBuff[6]--;				// 是的话就减去1
				LcdGotoXY(1, 10);					// 光标定位到秒钟的位置
				LcdPrintNum(TimeBuff[6]);		// 刷新显示改变后的秒钟
				LcdGotoXY(1, 11);					// 定位光标到秒钟闪烁
				DelayMs(300);					// 延时0.3秒左右
			}

			if (Key5_P == 0)						// 如果加按键被下去
			{
				if (TimeBuff[6] < 59)				// 判断秒钟是否小于59
					TimeBuff[6]++;					// 是的话就加上1
				LcdGotoXY(1, 10);				// 光标定位到秒钟的位置
				LcdPrintNum(TimeBuff[6]);			// 刷新显示改变后的秒钟
				LcdGotoXY(1, 11);				// 定位光标到秒钟闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key1_P == 0)
			{
				break;
			}
		}

		/* 退出前的设置 */
		LcdWriteCmd(0x0C);			// 关闭光标闪烁
		DS1302_Write_Time();			// 把新设置的时间值存入DS1302芯片
		DelayMs(10);				// 延时等待，消除按键按下的抖动
		while (!Key1_P);					// 等待按键释放
		DelayMs(10);				// 延时等待，消除按键松开的抖动
	}
}

/*********************************************************/
// 按键扫描(设置闹钟)
/*********************************************************/
void KeyScanf2()
{
	if (Key2_P == 0)
	{
		LcdGotoXY(0, 0);							// 液晶显示为闹钟设置的界面
		LcdPrintStr("Alarm Clock Set ");
		LcdGotoXY(1, 0);
		LcdPrintStr("     :          ");
		LcdGotoXY(1, 3);							// 显示闹钟的小时
		LcdPrintNum(Clock_Hour);
		LcdGotoXY(1, 6);							// 显示闹钟的分钟
		LcdPrintNum(Clock_Minute);
		LcdGotoXY(1, 10);						// 显示闹钟状态
		if (Clock_Swt == 0)
		{
			LcdPrintStr("OFF");
		}
		else
		{
			LcdPrintStr(" ON");
		}
		LcdGotoXY(1, 4);					// 光标定位
		LcdWriteCmd(0x0f);					// 光标闪烁
		DelayMs(10);					// 延时等待，消除按键按下的抖动
		while (!Key2_P);						// 等待按键释放
		DelayMs(10);					// 延时等待，消除按键松开的抖动

		while (1)						//调整闹钟小时
		{
			if (Key4_P == 0)						// 如果减按键被下去
			{
				if (Clock_Hour > 0)				// 判断闹钟小时是否大于0
					Clock_Hour--;					// 是的话就减去1
				LcdGotoXY(1, 3);					// 光标定位到闹钟小时的位置
				LcdPrintNum(Clock_Hour);			// 刷新显示改变后的闹钟小时
				LcdGotoXY(1, 4);					// 定位光标到闹钟小时闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key5_P == 0)						// 如果加按键被下去
			{
				if (Clock_Hour < 23)				// 判断闹钟小时是否小于23
					Clock_Hour++;					// 是的话就加上1
				LcdGotoXY(1, 3);					// 光标定位到闹钟小时的位置
				LcdPrintNum(Clock_Hour);			// 刷新显示改变后的闹钟小时
				LcdGotoXY(1, 4);					// 定位光标到闹钟小时闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key2_P == 0)
			{
				break;
			}
		}

		LcdGotoXY(1, 7);					// 定位光标到闹钟分钟的闪烁
		DelayMs(10);						// 延时等待，消除按键按下的抖动
		while (!Key2_P);					// 等待按键释放
		DelayMs(10);						// 延时等待，消除按键松开的抖动

		while (1)						//调整分钟
		{
			if (Key4_P == 0)						// 如果减按键被下去
			{
				if (Clock_Minute > 0)				// 判断闹钟分钟是否大于0
					Clock_Minute--;					// 是的话就减去1
				LcdGotoXY(1, 6);					// 光标定位到闹钟分钟的位置
				LcdPrintNum(Clock_Minute);			// 刷新显示改变后的闹钟分钟
				LcdGotoXY(1, 7);					// 定位光标到闹钟分钟闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key5_P == 0)					// 如果加按键被下去
			{
				if (Clock_Minute < 59)				// 判断闹钟分钟是否小于59
					Clock_Minute++;					// 是的话就加上1
				LcdGotoXY(1, 6);					// 光标定位到闹钟分钟的位置
				LcdPrintNum(Clock_Minute);			// 刷新显示改变后的闹钟分钟
				LcdGotoXY(1, 7);					// 定位光标到闹钟分钟闪烁
				DelayMs(300);						// 延时0.3秒左右
			}

			if (Key2_P == 0)
			{
				break;
			}
		}

		LcdGotoXY(1, 12);			// 定位光标到闹钟开关的位置闪烁
		DelayMs(10);					// 延时等待，消除按键按下的抖动
		while (!Key2_P);				// 等待按键释放
		DelayMs(10);					// 延时等待，消除按键松开的抖动

		while (1)						//闹钟开关
		{
			if (Key4_P == 0)				// 如果减按键被下去
			{
				if (Clock_Swt == 1)		// 判断闹钟是否开启
					Clock_Swt = 0;			// 关闭闹钟
				LcdGotoXY(1, 10);		// 光标定位到秒钟开关的位置
				LcdPrintStr("OFF");		// 液晶显示“OFF”
				LcdGotoXY(1, 12);		// 定位光标到闹钟开关的位置闪烁
				DelayMs(300);				// 延时0.3秒左右
			}

			if (Key5_P == 0)					// 如果加按键被下去
			{
				if (Clock_Swt == 0)			// 判断闹钟是否关闭
					Clock_Swt = 1;				// 启动闹钟
				LcdGotoXY(1, 10);			// 光标定位到秒钟开关的位置
				LcdPrintStr(" ON");			// 液晶显示“ ON”
				LcdGotoXY(1, 12);			// 定位光标到闹钟开关的位置闪烁
				DelayMs(300);					// 延时0.3秒左右
			}

			if (Key2_P == 0)
			{
				break;
			}
		}

		//退出前的设置
		LcdWriteCmd(0x0C);						// 关闭光标闪烁
		LcdShowInit();								// 液晶显示内容恢复为检测界面的
		DelayMs(10);							// 延时等待，消除按键按下的抖动
		while (!Key2_P);								// 等待按键释放
		DelayMs(10);							// 延时等待，消除按键松开的抖动
		Sector_Erase(0x2000);
		EEPROM_Write(0x2000, Clock_Hour);		// 往0x2000这个地址写入闹钟的小时 
		EEPROM_Write(0x2001, Clock_Minute);			// 往0x2001这个地址写入闹钟的分钟
		EEPROM_Write(0x2002, Clock_Swt);		// 往0x2002这个地址写入闹钟的开关
	}
}

/*********************************************************/
// 进入/退出 秒表
/*********************************************************/
void KeyScanf3()
{
	if (Key3_P == 0)
	{
		LcdGotoXY(0, 0);								// 液晶显示为秒表的界面
		LcdPrintStr("   Stop-Watch   ");
		LcdGotoXY(1, 0);
		LcdPrintStr("  00:00:00 00   ");

		DelayMs(10);								// 延时等待，消除按键按下的抖动
		while (!Key3_P);									// 等待按键释放
		DelayMs(10);								// 延时等待，消除按键松开的抖动

		while (Key3_P)						//调整闹钟小时
		{
			if (Key4_P == 0)					// 秒表的开始和暂停切换		
			{
				if (TR1 == 0)					// 关变开
				{
					TR1 = 1;
				}
				else						// 开变关
				{
					TR1 = 0;
				}
				DelayMs(10);				// 延时等待，消除按键按下的抖动
				while (!Key4_P);					// 等待按键释放
				DelayMs(10);				// 延时等待，消除按键松开的抖动
			}

			if (Key5_P == 0)								// 秒表清零
			{
				Stop_Watch_Count = 0;						// 计数变量1清零
				Stop_Watch_Second = 0;						// 计数变量2清零
				LcdGotoXY(1, 0);							// 显示清零
				LcdPrintStr("  00:00:00 00   ");
				DelayMs(10);							// 延时等待，消除按键按下的抖动
				while (!Key5_P);								// 等待按键释放
				DelayMs(10);							// 延时等待，消除按键松开的抖动
			}


			if (TR1 == 1)									//秒表计时的显示
			{
				LcdGotoXY(1, 2);
				LcdPrintNum(Stop_Watch_Second / 3600);		// 小时
				LcdGotoXY(1, 5);
				LcdPrintNum(Stop_Watch_Second % 3600 / 60);	// 分钟
				LcdGotoXY(1, 8);
				LcdPrintNum(Stop_Watch_Second % 60);			// 秒钟
				LcdGotoXY(1, 11);
				LcdPrintNum(Stop_Watch_Count);				// 毫秒
			}

		}
		// 退出秒表，回到时钟模式
		TR1 = 0;								// 停止定时器		
		Stop_Watch_Count = 0;						// 计数变量1清零
		Stop_Watch_Second = 0;				// 计数变量2清零
		LcdShowInit();							// 液晶显示时钟界面
		DelayMs(10);						// 延时等待，消除按键按下的抖动
		while (!Key3_P);							// 等待按键释放
		DelayMs(10);						// 延时等待，消除按键松开的抖动
	}
}

/*********************************************************/
// 闹钟判断
/*********************************************************/
void ClockJudge()
{
	if (Clock_Swt == 1)			// 判断闹钟的开关是否开启
	{
		if ((Clock_Hour == TimeBuff[4]) && (Clock_Minute == TimeBuff[5]))	//当前小时和分钟，和闹钟的小时和分钟是否一致
		{
			if (TimeBuff[6] == 0)			// 秒数是否等于0
			{
				Buzzer_Flag = 1;			// 开启蜂鸣器报警标志
			}
		}
	}

	if (TimeBuff[6] == 59)					// 如果当前秒数为59秒
	{
		Buzzer_Flag = 0;					// 关闭蜂鸣器报警标志
	}

	if ((Key4_P == 0) || (Key5_P == 0))		// 如果加按键或减按键被按下
	{
		Buzzer_Flag = 0;					// 要关闭蜂鸣器
	}

	if (Buzzer_Flag == 1)				// 如果蜂鸣器要启动
	{
		Buzzer_P = 0;					// 启动蜂鸣器
		DelayMs(100);					// 延时0.1秒
		Buzzer_P = 1;					// 关闭蜂鸣器
		DelayMs(100);					// 延时0.1秒
	}
}

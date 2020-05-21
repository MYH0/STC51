sbit LcdRs_P = P2 ^ 7;       // 1602液晶的RS       
sbit LcdRw_P = P2 ^ 6;			// 1602液晶的RW 
sbit LcdEn_P = P2 ^ 5;       // 1602液晶的EN

/*********************************************************/
// 1602液晶写命令函数，cmd就是要写入的命令
/*********************************************************/
void LcdWriteCmd(uchar cmd)
{
	LcdRs_P = 0;
	LcdRw_P = 0;
	LcdEn_P = 0;
	P0 = cmd;
	DelayMs(2);
	LcdEn_P = 1;
	DelayMs(2);
	LcdEn_P = 0;
}

/*********************************************************/
// 1602液晶写数据函数，dat就是要写入的数据
/*********************************************************/
void LcdWriteData(uchar dat)
{
	LcdRs_P = 1;
	LcdRw_P = 0;
	LcdEn_P = 0;
	P0 = dat;
	DelayMs(2);
	LcdEn_P = 1;
	DelayMs(2);
	LcdEn_P = 0;
}

/*********************************************************/
// 1602液晶初始化函数
/*********************************************************/
void LcdInit()
{
	LcdWriteCmd(0x38);        // 16*2显示，5*7点阵，8位数据口
	LcdWriteCmd(0x0C);        // 开显示，不显示光标
	LcdWriteCmd(0x06);        // 地址加1，当写入数据后光标右移
	LcdWriteCmd(0x01);        // 清屏
}

/*********************************************************/
// 液晶输出字符串函数
/*********************************************************/
void LcdPrintStr(uchar* str)
{
	while (*str != '\0')
		LcdWriteData(*str++);
}

/*********************************************************/
// 液晶光标定位函数
/*********************************************************/
void LcdGotoXY(uchar hang, uchar lie)
{	
	if (hang == 0)							// 第一行
		LcdWriteCmd(0x80 + lie);	
	if (hang == 1)							// 第二行
		LcdWriteCmd(0x80 + 0x40 + lie);
}

/*********************************************************/
// 液晶显示内容的初始化
/*********************************************************/
void LcdShowInit()
{
	LcdGotoXY(0, 0);
	LcdPrintStr("20  -  -        ");
	LcdGotoXY(1, 0);
	LcdPrintStr("      :  :      ");
}

/*********************************************************/
// 液晶输出数字
/*********************************************************/
void LcdPrintNum(uchar num)
{
	LcdWriteData(num / 10 + 48);		// 十位
	LcdWriteData(num % 10 + 48); 		// 个位
}

/*********************************************************/
// 液晶显示星期
/*********************************************************/
void LcdPrintWeek(uchar week)
{
	switch (week)
	{
	case 1: LcdPrintStr(" Sun");	break;
	case 2: LcdPrintStr(" Mon");	break;
	case 3: LcdPrintStr("Tues");	break;
	case 4: LcdPrintStr(" Wed");	break;
	case 5: LcdPrintStr("Thur");	break;
	case 6: LcdPrintStr(" Fri");	break;
	case 7: LcdPrintStr(" Sat");	break;
	default:break;
	}
}

/*********************************************************/
// 刷新时间显示
/*********************************************************/
void FlashTime()
{
	LcdGotoXY(0, 2);					// 年份
	LcdPrintNum(TimeBuff[0]);
	LcdGotoXY(0, 5);					// 月份
	LcdPrintNum(TimeBuff[1]);
	LcdGotoXY(0, 8);					// 日期
	LcdPrintNum(TimeBuff[2]);
	LcdGotoXY(1, 4);					// 小时
	LcdPrintNum(TimeBuff[4]);
	LcdGotoXY(1, 7);					// 分钟
	LcdPrintNum(TimeBuff[5]);
	LcdGotoXY(1, 10);					// 秒钟
	LcdPrintNum(TimeBuff[6]);
	LcdGotoXY(0, 12);					// 星期	
	LcdPrintWeek(TimeBuff[3]);
}

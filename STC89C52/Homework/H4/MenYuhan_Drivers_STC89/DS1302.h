/************************************注意*****************************************/
//data为C51关键字
/***********************************预设量****************************************/
uchar TimeBuff[7] = { 20,10,31,7,11,25,20 };   //时间数组，默认2020年10月31日，星期五，18:30:40
// TimeBuff[0] 代表年份，范围00-99
// TimeBuff[1] 代表月份，范围1-12
// TimeBuff[2] 代表日期，范围1-31
// TimeBuff[3] 代表星期，范围1-7，1是星期天，2是星期一
// TimeBuff[4] 代表小时，范围00-23
// TimeBuff[5] 代表分钟，范围00-59
// TimeBuff[6] 代表秒钟，范围00-59

/**********************************IO定义*****************************************/
sbit DS1302_CLK = P2 ^ 1;
sbit DS1302_IO = P2 ^ 0;
sbit DS1302_RST = P2 ^ 4;
/***********************************操作******************************************/
/***********************************通信********************/
/*********************************读1字节*/
uchar DS1302_R_Byte(uchar addr)
{
	uchar i;
	uchar temp;

	DS1302_RST = 1;
	for (i = 0; i < 8; i++)			//写入目标地址：addr
	{
		if (addr & 0x01)
			DS1302_IO = 1;
		else
			DS1302_IO = 0;

		DS1302_CLK = 1;
		_nop_();
		DS1302_CLK = 0;
		_nop_();

		addr = addr >> 1;
	}

	for (i = 0; i < 8; i++)			//读出该地址的数据
	{
		temp = temp >> 1;

		if (DS1302_IO)
			temp |= 0x80;
		else
			temp &= 0x7F;

		DS1302_CLK = 1;
		_nop_();
		DS1302_CLK = 0;
		_nop_();
	}
	DS1302_RST = 0;
	return temp;
}

/*********************************写1字节*/
void DS1302_W_Byte(uchar addr, uchar dat)
{
	uchar i;

	DS1302_RST = 1;
	for (i = 0; i < 8; i++)			//写入目标地址：addr
	{
		if (addr & 0x01)
			DS1302_IO = 1;
		else
			DS1302_IO = 0;

		DS1302_CLK = 1;
		_nop_();
		DS1302_CLK = 0;
		_nop_();

		addr = addr >> 1;
	}

	for (i = 0; i < 8; i++)			//写入数据：dat
	{
		if (dat & 0x01)
			DS1302_IO = 1;
		else
			DS1302_IO = 0;

		DS1302_CLK = 1;
		_nop_();
		DS1302_CLK = 0;
		_nop_();

		dat = dat >> 1;
	}
	DS1302_RST = 0;
}

/***********************************行动********************/
/*******************************写入时间数据*/
void DS1302_W_Time()
{
	uchar i;
	uchar temp1;
	uchar temp2;

	for (i = 0; i < 7; i++)			// 十进制转BCD码
	{
		temp1 = (TimeBuff[i] / 10) << 4;
		temp2 = TimeBuff[i] % 10;
		TimeBuff[i] = temp1 + temp2;
	}
	DS1302_W_Byte(0x8E, 0x00);						// 关闭写保护 
	DS1302_W_Byte(0x80, 0x80);						// 暂停时钟 
	DS1302_W_Byte(0x8C, TimeBuff[0]);				// 年 
	DS1302_W_Byte(0x88, TimeBuff[1]);				// 月 
	DS1302_W_Byte(0x86, TimeBuff[2]);				// 日 
	DS1302_W_Byte(0x8A, TimeBuff[3]);				// 星期
	DS1302_W_Byte(0x84, TimeBuff[4]);				// 时 
	DS1302_W_Byte(0x82, TimeBuff[5]);				// 分
	DS1302_W_Byte(0x80, TimeBuff[6]);				// 秒
	DS1302_W_Byte(0x80, TimeBuff[6] & 0x7F);		// 运行时钟
	DS1302_W_Byte(0x8E, 0x80);						// 打开写保护  
}

/*******************************读出时间数据*/
void DS1302_R_Time()
{
	uchar i;
	TimeBuff[0] = DS1302_R_Byte(0x8D);				// 年 
	TimeBuff[1] = DS1302_R_Byte(0x89);				// 月 
	TimeBuff[2] = DS1302_R_Byte(0x87);				// 日 
	TimeBuff[3] = DS1302_R_Byte(0x8B);				// 星期
	TimeBuff[4] = DS1302_R_Byte(0x85);				// 时 
	TimeBuff[5] = DS1302_R_Byte(0x83);				// 分 
	TimeBuff[6] = (DS1302_R_Byte(0x81)) & 0x7F;		// 秒 

	for (i = 0; i < 7; i++)		// BCD转十进制
	{
		TimeBuff[i] = (TimeBuff[i] / 16) * 10 + TimeBuff[i] % 16;
	}
}

/*******************判断时钟芯片是否正常运行*/
void DS1302_Check()
{
	if (DS1302_R_Byte(0x81) >= 128)	// 判断时钟芯片是否正常运行
		DS1302_W_Time();				// 如果没有，则初始化一个时间
}
/***********************************初始化*/
void DS1302_Init()
{
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_IO = 0;
}

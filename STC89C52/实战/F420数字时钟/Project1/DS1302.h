sbit RST_P = P1 ^ 3;			// 时钟芯片DS1302的RST
sbit SDA_P = P1 ^ 2;		// 时钟芯片DS1302的SDA
sbit SCK_P = P1 ^ 1;			// 时钟芯片DS1302的SCK

/*********************************************************/
// 初始化DS1302
/*********************************************************/
void DS1302_Init(void)
{
	RST_P = 0;			// RST脚置低
	SCK_P = 0;			// SCK脚置低
	SDA_P = 0;			// SDA脚置低				
}

/*********************************************************/
// 从DS1302读出一字节数据
/*********************************************************/
uchar DS1302_Read_Byte(uchar addr)
{
	uchar i;
	uchar temp;
	RST_P = 1;
	for (i = 0; i < 8; i++)			//写入目标地址：addr
	{
		if (addr & 0x01)
			SDA_P = 1;
		else
			SDA_P = 0;

		SCK_P = 1;
		_nop_();
		SCK_P = 0;
		_nop_();

		addr = addr >> 1;
	}

	for (i = 0; i < 8; i++)			//读出该地址的数据
	{
		temp = temp >> 1;

		if (SDA_P)
			temp |= 0x80;
		else
			temp &= 0x7F;

		SCK_P = 1;
		_nop_();
		SCK_P = 0;
		_nop_();
	}
	RST_P = 0;
	return temp;
}

/*********************************************************/
// 向DS1302写入一字节数据
/*********************************************************/
void DS1302_Write_Byte(uchar addr, uchar dat)
{
	uchar i;
	RST_P = 1;
	for (i = 0; i < 8; i++)				//写入目标地址：addr
	{
		if (addr & 0x01)
			SDA_P = 1;
		else
			SDA_P = 0;

		SCK_P = 1;
		_nop_();
		SCK_P = 0;
		_nop_();

		addr = addr >> 1;
	}

	for (i = 0; i < 8; i++)			//写入数据：dat
	{
		if (dat & 0x01)
			SDA_P = 1;
		else
			SDA_P = 0;

		SCK_P = 1;
		_nop_();
		SCK_P = 0;
		_nop_();

		dat = dat >> 1;
	}
	RST_P = 0;
}

/*********************************************************/
// 向DS1302写入时间数据
/*********************************************************/
void DS1302_Write_Time()
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
	DS1302_Write_Byte(0x8E, 0x00);						// 关闭写保护 
	DS1302_Write_Byte(0x80, 0x80);						// 暂停时钟 
	DS1302_Write_Byte(0x8C, TimeBuff[0]);				// 年 
	DS1302_Write_Byte(0x88, TimeBuff[1]);				// 月 
	DS1302_Write_Byte(0x86, TimeBuff[2]);				// 日 
	DS1302_Write_Byte(0x8A, TimeBuff[3]);				// 星期
	DS1302_Write_Byte(0x84, TimeBuff[4]);				// 时 
	DS1302_Write_Byte(0x82, TimeBuff[5]);				// 分
	DS1302_Write_Byte(0x80, TimeBuff[6]);				// 秒
	DS1302_Write_Byte(0x80, TimeBuff[6] & 0x7F);		// 运行时钟
	DS1302_Write_Byte(0x8E, 0x80);						// 打开写保护  
}

/*********************************************************/
// 从DS1302读出时间数据
/*********************************************************/
void DS1302_Read_Time()
{
	uchar i;
	TimeBuff[0] = DS1302_Read_Byte(0x8D);						// 年 
	TimeBuff[1] = DS1302_Read_Byte(0x89);						// 月 
	TimeBuff[2] = DS1302_Read_Byte(0x87);						// 日 
	TimeBuff[3] = DS1302_Read_Byte(0x8B);						// 星期
	TimeBuff[4] = DS1302_Read_Byte(0x85);						// 时 
	TimeBuff[5] = DS1302_Read_Byte(0x83);						// 分 
	TimeBuff[6] = (DS1302_Read_Byte(0x81)) & 0x7F;		// 秒 

	for (i = 0; i < 7; i++)		// BCD转十进制
	{
		TimeBuff[i] = (TimeBuff[i] / 16) * 10 + TimeBuff[i] % 16;
	}
}


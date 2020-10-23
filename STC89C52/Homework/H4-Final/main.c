#include <STC89C5XRC.H>
//#include <STC12C5A60S2.H>
#include <intrins.h>
#include <math.h>

typedef unsigned int uint;
typedef unsigned char uchar;

#define BIT0 1<<0
#define BIT1 1<<1
#define BIT2 1<<2
#define BIT3 1<<3

#define BIT4 1<<4
#define BIT5 1<<5
#define BIT6 1<<6
#define BIT7 1<<7

#define BIT8_ALL 0xff

/*************************************注意******************************************/
//data是C51关键字
/***********************************预装数据****************************************/

/***********************************预设变量****************************************/
uchar hour_shi = 0;
uchar hour_ge = 0;
uchar min_shi = 0;
uchar min_ge = 0;
uchar sec_shi = 0;
uchar sec_ge = 0;

//f=11.0592MHz
/******************************************粗略延时***********************************/
void Delay_ms(uint time_ms)
{
	uint i, j;
	for (i = 0; i < time_ms; i++)
		for (j = 0; j < 113; j++);
}
/******************************************较为精准延时********************************/
/***********************************************ms*****************/
void Delay_ms_1()
{
	unsigned char i, j;
	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay_ms_2()
{
	unsigned char i, j;
	_nop_();
	i = 4;
	j = 146;
	do
	{
		while (--j);
	} while (--i);
}

void Delay_ms_5()
{
	unsigned char i, j;
	i = 9;
	j = 244;
	do
	{
		while (--j);
	} while (--i);
}
/***********************************************s******************/
void Delay_s_0_5()
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay_s_1()
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

/***************************************预定义*****************************************/
/***************************************LED**********************/
/**************************************IO预定义*/
sbit LED0 = P1 ^ 0;
sbit LED1 = P1 ^ 1;
sbit LED2 = P1 ^ 2;
sbit LED3 = P1 ^ 3;
sbit LED4 = P1 ^ 4;
sbit LED5 = P1 ^ 5;
sbit LED6 = P1 ^ 6;
sbit LED7 = P1 ^ 7;
/**************************************操作预定义*/
/*开灯*/
#define LED0_On LED0=0
#define LED1_On LED1=0
#define LED2_On LED2=0
#define LED3_On LED3=0
#define LED4_On LED4=0
#define LED5_On LED5=0
#define LED6_On LED6=0
#define LED7_On LED7=0
#define LED_ALL_On P1=0x00
/*关灯*/
#define LED0_Off LED0=1
#define LED1_Off LED1=1
#define LED2_Off LED2=1
#define LED3_Off LED3=1
#define LED4_Off LED4=1
#define LED5_Off LED5=1
#define LED6_Off LED6=1
#define LED7_Off LED7=1
#define LED_ALL_Off P1=0xff
/*反转*/
#define LED0_Toggle P1^=BIT0
#define LED1_Toggle P1^=BIT1
#define LED2_Toggle P1^=BIT2
#define LED3_Toggle P1^=BIT3
#define LED4_Toggle P1^=BIT4
#define LED5_Toggle P1^=BIT5
#define LED6_Toggle P1^=BIT6
#define LED7_Toggle P1^=BIT7
#define LED_ALL_Toggle P1^=BIT8_ALL

/***************************************Beep*****************/
/**************************************IO预定义*/
sbit Beep = P2 ^ 3;
/**************************************操作预定义*/
#define Beep_On Beep=0
#define Beep_Off Beep=1
#define Beep_Toggle P2^=BIT3
/***************************************数码管*****************/
sbit wx = P2 ^ 7;
sbit dx = P2 ^ 6;
/***************************************独立按键****************/
sbit Key_i0 = P3 ^ 4;
sbit Key_i1 = P3 ^ 5;
sbit Key_i2 = P3 ^ 6;
sbit Key_i3 = P3 ^ 7;
/***************************************操作****************************************/
void STC89_TX_1C_Board_IO_Base_Init()
{
	dx = 0;	//dx
	wx = 0;	//wx

	EA = 1;
}

/********************************************常量定义*********************************************/
/********************************************段选************************/
uchar code duanxuan[] =
{
	0x3f,		//0
	0x06,		//1
	0x5b,		//2
	0x4f,		//3
	0x66,		//4
	0x6d,		//5
	0x7d,		//6
	0x07,		//7
	0x7f,		//8
	0x6f,		//9

	0x77,		//A--10
	0x7c,		//b--11
	0x39,		//C--12
	0x5e,		//d--13
	0x79,		//E--14
	0x71,		//F--15
	0x3d,		//G--16
	0x76,		//H--17
	0x11,		//i--18
	0x0e,		//J--19
	0x7a,		//k--20
	0x38,		//L--21
	0x55,		//M--22
	0x54,		//n--23
	0X3f,		//O--24
	0x73,		//P--25
	0x67,		//q--26
	0x50,		//r--27
	0x6d,		//S--28
	0x78,		//t--29
	0x3e,		//U--30
	0x3e,		//V--31
	0x6a,		//W--32
	0x76,		//X--33
	0x6e,		//y--34
	0x5b,		//Z--35

	0x7b,		//e--36
	0x74,		//h--37
	0x5c,		//o--38
	0x1c,		//u--39
	0x62,		//v--40

	0x00		//0x00为全不亮--41
};
/********************************************位选************************/
uchar code weixuan[] =			//左边第一位为bit0
{
	0xfe,		//0
	0xfd,		//1
	0xfb,		//2
	0xf7,		//3
	0xef,		//4
	0xdf,		//5
	0xc0		//ALL--6
};
/*******************************************预装数据**********************************************/
uchar code HELLO[] = { 17,14,21,21,24,41 };
/********************************************IO定义**********************************************/
//sbit wx = P2 ^ 7;
//sbit dx = P2 ^ 6;
/***********************************************操作**********************************************/
/*******************************************数码管显示1bit******************/
void DigitalTube_Display_1bit(uchar wei, uchar duan)     //位数据，段数据
{
	dx = 1;
	P0 = duanxuan[duan];   //送段数据
	dx = 0;
	P0 = 0xff;		//送位数据前关闭所有显示，防止打开位选锁存后段选数据通过位选锁存器
	wx = 1;
	P0 = weixuan[wei];
	wx = 0;
	Delay_ms_1();
}
/*******************************************数码管显示3bit数字******************/
void DigitalTube_Display_num_3bit(uchar shu)
{
	uchar bai, shi, ge;
	bai = shu / 100;
	shi = shu / 10 % 10;
	ge = shu % 10;

	DigitalTube_Display_1bit(0, bai);
	DigitalTube_Display_1bit(1, shi);
	DigitalTube_Display_1bit(2, ge);
}
/*******************************************数码管显示6bit******************/
void DigitalTube_Display_6bit(uchar zero, uchar one, uchar two, uchar three, uchar four, uchar five)
{
	DigitalTube_Display_1bit(0, zero);
	DigitalTube_Display_1bit(1, one);
	DigitalTube_Display_1bit(2, two);
	DigitalTube_Display_1bit(3, three);
	DigitalTube_Display_1bit(4, four);
	DigitalTube_Display_1bit(5, five);
}
/*******************************************数码管显示HELLO******************/
void DigitalTube_Display_Str_HELLO()
{
	DigitalTube_Display_6bit(HELLO[0], HELLO[1], HELLO[2], HELLO[3], HELLO[4], HELLO[5]);
}

/************************************注意*****************************************/
//data为C51关键字
/***********************************预设量****************************************/
uchar TimeBuff[7] = { 20,10,23,6,21,56,00 };   //时间数组，默认2020年10月23日，星期五，18:30:40
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


void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	DS1302_Init();
	//DS1302_W_Time();
	DS1302_Check();

	while (1)
	{
		DS1302_R_Time();

		hour_shi = TimeBuff[4] / 10;
		hour_ge = TimeBuff[4] % 10;
		min_shi = TimeBuff[5] / 10;
		min_ge = TimeBuff[5] % 10;
		sec_shi = TimeBuff[6] / 10;
		sec_ge = TimeBuff[6] % 10;

		DigitalTube_Display_6bit(hour_shi, hour_ge, min_shi, min_ge, sec_shi, sec_ge);
	}
}
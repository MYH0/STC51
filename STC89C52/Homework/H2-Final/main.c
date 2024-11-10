#include <STC12C5A60S2.H>

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
/************************************数码管*********************/
uchar code HELLO[] = { 17,14,21,21,24,41 };
/************************************LCD1602*******************/
const uchar LCD1602_Str0[] = "Men Yuhan";
const uchar LCD1602_Str1[] = "18050100196";
const uint LCD1602_Num0 = 713;

/***********************************预设变量****************************************/
uint pwm_count = 0;		//控制高低电平;1xpwm_count==200;1--H,2、3、4、5--L
uint period_count = 0;	//控制LED切换;1xperiod_count==5xpwm_count
uint led_num = 0;

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

/**********************************T0初始化*********************************/
void T0_Init(uint timer0_long)
{
	//	EA = 1;
	ET0 = 1;
	//	TMOD = 0X01;
	TH0 = (65536 - timer0_long) / 256;
	TL0 = (65536 - timer0_long) % 256;
	//	TR0 = 1;
}
/**********************************功能定义**********************************/
void T0_INT_Func()
{
	pwm_count++;

	if (pwm_count >= 5)
		pwm_count = 0;
	if (pwm_count == 0)
		P00 = 1;
	else
		P00 = 0;

}
/************************************中断************************************/
void T0_INT() interrupt 1
{
	/*****修改定时的时长*****/
	uint time_long0;
	time_long0 = 200;
	/*****装载定时的时长*****/
	TH0 = (65536 - time_long0) / 256;
	TL0 = (65536 - time_long0) % 256;
	/*****中断功能*****/
	T0_INT_Func();
}



void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	T0_Init(200);
	TMOD = 0X01;
	TR0 = 1;



	while (1)
	{
		LED0_On;
		Delay_ms(500);
		LED0_Off;

		LED1_On;
		Delay_ms(500);
		LED1_Off;

		LED2_On;
		Delay_ms(500);
		LED2_Off;

		LED3_On;
		Delay_ms(500);
		LED3_Off;

		LED4_On;
		Delay_ms(500);
		LED4_Off;

		LED5_On;
		Delay_ms(500);
		LED5_Off;

		LED6_On;
		Delay_ms(500);
		LED6_Off;

		LED7_On;
		Delay_ms(500);
		LED7_Off;


	}
}

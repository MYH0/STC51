#include <STC89C5XRC.H>

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

/*************************************ע��******************************************/
//data��C51�ؼ���
/***********************************Ԥװ����****************************************/

/***********************************Ԥ�����****************************************/
uchar hour_shi = 0;
uchar hour_ge = 0;
uchar min_shi = 0;
uchar min_ge = 0;
uchar sec_shi = 0;
uchar sec_ge = 0;

//f=11.0592MHz
/******************************************������ʱ***********************************/
void Delay_ms(uint time_ms)
{
	uint i, j;
	for (i = 0; i < time_ms; i++)
		for (j = 0; j < 113; j++);
}
/******************************************��Ϊ��׼��ʱ********************************/
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

/***************************************Ԥ����*****************************************/
/***************************************LED**********************/
/**************************************IOԤ����*/
sbit LED0 = P1 ^ 0;
sbit LED1 = P1 ^ 1;
sbit LED2 = P1 ^ 2;
sbit LED3 = P1 ^ 3;
sbit LED4 = P1 ^ 4;
sbit LED5 = P1 ^ 5;
sbit LED6 = P1 ^ 6;
sbit LED7 = P1 ^ 7;
/**************************************����Ԥ����*/
/*����*/
#define LED0_On LED0=0
#define LED1_On LED1=0
#define LED2_On LED2=0
#define LED3_On LED3=0
#define LED4_On LED4=0
#define LED5_On LED5=0
#define LED6_On LED6=0
#define LED7_On LED7=0
#define LED_ALL_On P1=0x00
/*�ص�*/
#define LED0_Off LED0=1
#define LED1_Off LED1=1
#define LED2_Off LED2=1
#define LED3_Off LED3=1
#define LED4_Off LED4=1
#define LED5_Off LED5=1
#define LED6_Off LED6=1
#define LED7_Off LED7=1
#define LED_ALL_Off P1=0xff
/*��ת*/
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
/**************************************IOԤ����*/
sbit Beep = P2 ^ 3;
/**************************************����Ԥ����*/
#define Beep_On Beep=0
#define Beep_Off Beep=1
#define Beep_Toggle P2^=BIT3
/***************************************�����*****************/
sbit wx = P2 ^ 7;
sbit dx = P2 ^ 6;
/***************************************��������****************/
sbit Key_i0 = P3 ^ 4;
sbit Key_i1 = P3 ^ 5;
sbit Key_i2 = P3 ^ 6;
sbit Key_i3 = P3 ^ 7;
/***************************************����****************************************/
void STC89_TX_1C_Board_IO_Base_Init()
{
	dx = 0;	//dx
	wx = 0;	//wx

	EA = 1;
}

/********************************************��������*********************************************/
/********************************************��ѡ************************/
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

	0x00		//0x00Ϊȫ����--41
};
/********************************************λѡ************************/
uchar code weixuan[] =			//��ߵ�һλΪbit0
{
	0xfe,		//0
	0xfd,		//1
	0xfb,		//2
	0xf7,		//3
	0xef,		//4
	0xdf,		//5
	0xc0		//ALL--6
};
/*******************************************Ԥװ����**********************************************/
uchar code HELLO[] = { 17,14,21,21,24,41 };
/********************************************IO����**********************************************/
//sbit wx = P2 ^ 7;
//sbit dx = P2 ^ 6;
/***********************************************����**********************************************/
/*******************************************�������ʾ1bit******************/
void DigitalTube_Display_1bit(uchar wei, uchar duan)     //λ���ݣ�������
{
	dx = 1;
	P0 = duanxuan[duan];   //�Ͷ�����
	dx = 0;
	P0 = 0xff;		//��λ����ǰ�ر�������ʾ����ֹ��λѡ������ѡ����ͨ��λѡ������
	wx = 1;
	P0 = weixuan[wei];
	wx = 0;
	Delay_ms_1();
}
/*******************************************�������ʾ3bit����******************/
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
/*******************************************�������ʾ6bit******************/
void DigitalTube_Display_6bit(uchar zero, uchar one, uchar two, uchar three, uchar four, uchar five)
{
	DigitalTube_Display_1bit(0, zero);
	DigitalTube_Display_1bit(1, one);
	DigitalTube_Display_1bit(2, two);
	DigitalTube_Display_1bit(3, three);
	DigitalTube_Display_1bit(4, four);
	DigitalTube_Display_1bit(5, five);
}
/*******************************************�������ʾHELLO******************/
void DigitalTube_Display_Str_HELLO()
{
	DigitalTube_Display_6bit(HELLO[0], HELLO[1], HELLO[2], HELLO[3], HELLO[4], HELLO[5]);
}

/************************************ע��*****************************************/
//dataΪC51�ؼ���
/***********************************Ԥ����****************************************/
uchar TimeBuff[7] = { 20,10,24,7,12,12,00 };   //ʱ�����飬2020��10��24�գ���������12:12:00
// TimeBuff[0] ������ݣ���Χ00-99
// TimeBuff[1] �����·ݣ���Χ1-12
// TimeBuff[2] �������ڣ���Χ1-31
// TimeBuff[3] �������ڣ���Χ1-7��1�������죬2������һ
// TimeBuff[4] ����Сʱ����Χ00-23
// TimeBuff[5] ������ӣ���Χ00-59
// TimeBuff[6] �������ӣ���Χ00-59

/**********************************IO����*****************************************/
sbit DS1302_CLK = P2 ^ 1;
sbit DS1302_IO = P2 ^ 0;
sbit DS1302_RST = P2 ^ 4;
/***********************************����******************************************/
/***********************************ͨ��********************/
/*********************************��1�ֽ�*/
uchar DS1302_R_Byte(uchar addr)
{
	uchar i;
	uchar temp;

	DS1302_RST = 1;
	for (i = 0; i < 8; i++)			//д��Ŀ���ַ��addr
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

	for (i = 0; i < 8; i++)			//�����õ�ַ������
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

/*********************************д1�ֽ�*/
void DS1302_W_Byte(uchar addr, uchar dat)
{
	uchar i;

	DS1302_RST = 1;
	for (i = 0; i < 8; i++)			//д��Ŀ���ַ��addr
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

	for (i = 0; i < 8; i++)			//д�����ݣ�dat
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

/***********************************�ж�********************/
/*******************************д��ʱ������*/
void DS1302_W_Time()
{
	uchar i;
	uchar temp1;
	uchar temp2;

	for (i = 0; i < 7; i++)			// ʮ����תBCD��
	{
		temp1 = (TimeBuff[i] / 10) << 4;
		temp2 = TimeBuff[i] % 10;
		TimeBuff[i] = temp1 + temp2;
	}
	DS1302_W_Byte(0x8E, 0x00);						// �ر�д���� 
	DS1302_W_Byte(0x80, 0x80);						// ��ͣʱ�� 
	DS1302_W_Byte(0x8C, TimeBuff[0]);				// �� 
	DS1302_W_Byte(0x88, TimeBuff[1]);				// �� 
	DS1302_W_Byte(0x86, TimeBuff[2]);				// �� 
	DS1302_W_Byte(0x8A, TimeBuff[3]);				// ����
	DS1302_W_Byte(0x84, TimeBuff[4]);				// ʱ 
	DS1302_W_Byte(0x82, TimeBuff[5]);				// ��
	DS1302_W_Byte(0x80, TimeBuff[6]);				// ��
	DS1302_W_Byte(0x80, TimeBuff[6] & 0x7F);		// ����ʱ��
	DS1302_W_Byte(0x8E, 0x80);						// ��д����  
}

/*******************************����ʱ������*/
void DS1302_R_Time()
{
	uchar i;
	TimeBuff[0] = DS1302_R_Byte(0x8D);				// �� 
	TimeBuff[1] = DS1302_R_Byte(0x89);				// �� 
	TimeBuff[2] = DS1302_R_Byte(0x87);				// �� 
	TimeBuff[3] = DS1302_R_Byte(0x8B);				// ����
	TimeBuff[4] = DS1302_R_Byte(0x85);				// ʱ 
	TimeBuff[5] = DS1302_R_Byte(0x83);				// �� 
	TimeBuff[6] = (DS1302_R_Byte(0x81)) & 0x7F;		// �� 

	for (i = 0; i < 7; i++)		// BCDתʮ����
	{
		TimeBuff[i] = (TimeBuff[i] / 16) * 10 + TimeBuff[i] % 16;
	}
}

/*******************�ж�ʱ��оƬ�Ƿ���������*/
void DS1302_Check()
{
	if (DS1302_R_Byte(0x81) >= 128)	// �ж�ʱ��оƬ�Ƿ���������
		DS1302_W_Time();				// ���û�У����ʼ��һ��ʱ��
}
/***********************************��ʼ��*/
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
	DS1302_W_Time();
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
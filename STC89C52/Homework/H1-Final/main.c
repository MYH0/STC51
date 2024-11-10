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
/************************************�����*********************/
uchar code Error[] = { 14,27,27,38,27,41 };
/***********************************Ԥ�����****************************************/
uchar t0_flag = 0;
uchar n = 0;

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
/***************************************�����*****************/
sbit wx = P2 ^ 7;
sbit dx = P2 ^ 6;
/***************************************����****************************************/
void STC89_TX_1C_Board_IO_Base_Init()
{
	dx = 0;	//dx
	wx = 0;	//wx

	EA = 1;
}

/**********************************T0��ʼ��*********************************/
void T0_Init(uint timer0_long)
{
	//	EA = 1;
	ET0 = 1;
	//	TMOD = 0X01;
	TH0 = (65536 - timer0_long) / 256;
	TL0 = (65536 - timer0_long) % 256;
	//	TR0 = 1;
}
/**********************************���ܶ���**********************************/
void T0_INT_Func()
{
	n++;
	if (n == 60)
	{
		n = 0;
		t0_flag = 0;
		TR0 = 0;
	}
}
/************************************�ж�************************************/
void T0_INT() interrupt 1
{
	/*****�޸Ķ�ʱ��ʱ��*****/
	uint time_long0;
	time_long0 = 50000;
	/*****װ�ض�ʱ��ʱ��*****/
	TH0 = (65536 - time_long0) / 256;
	TL0 = (65536 - time_long0) % 256;
	/*****�жϹ���*****/
	T0_INT_Func();
}

/***********************************Ԥ������**********************************/
void DigitalTube_Display_Str_Error();
/************************************��ʼ��***********************************/
void EX0_Init()
{
	EX0 = 1;
	//	IT0 = 0;	//�͵�ƽ����
	IT0 = 1;	//�½��ش���
}
/************************************�жϹ���***********************************/
void EX0_Func()
{
	t0_flag = 1;
	TR0 = 1;
	//while (1)
	//{
	//	DigitalTube_Display_Str_Error();
	//	if (error_flag == 0)
	//		break;
	//}

}
/************************************�����ж�***********************************/
void EX0_INT() interrupt 0
{
	EX0_Func();
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
/*******************************************ȫ�ֱ���**********************************************/
/********************************************IO����************************/
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
/*******************************************�������ʾError******************/
void DigitalTube_Display_Str_Error()
{
	DigitalTube_Display_6bit(Error[0], Error[1], Error[2], Error[3], Error[4], Error[5]);
}


void main()
{
	STC89_TX_1C_Board_IO_Base_Init();

	EX0_Init();

	T0_Init(50000);
	TMOD = 0X01;

	while (1)
	{
		while (t0_flag == 1)
		{
			DigitalTube_Display_Str_Error();
		}

		DigitalTube_Display_1bit(0, 0);
		Delay_s_1();
		while (t0_flag == 1)
		{
			DigitalTube_Display_Str_Error();
		}

		DigitalTube_Display_1bit(1, 1);
		Delay_s_1();
		while (t0_flag == 1)
		{
			DigitalTube_Display_Str_Error();
		}

		DigitalTube_Display_1bit(2, 2);
		Delay_s_1();
		while (t0_flag == 1)
		{
			DigitalTube_Display_Str_Error();
		}

		DigitalTube_Display_1bit(3, 3);
		Delay_s_1();
		while (t0_flag == 1)
		{
			DigitalTube_Display_Str_Error();
		}

		DigitalTube_Display_1bit(4, 4);
		Delay_s_1();
		while (t0_flag == 1)
		{
			DigitalTube_Display_Str_Error();
		}

		DigitalTube_Display_1bit(5, 5);
		Delay_s_1();
		while (t0_flag == 1)
		{
			DigitalTube_Display_Str_Error();
		}
	}
}
#pragma once
/*******************************************Include**********************************************/
/********************************************常量定义*********************************************/
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
	0x77,		//A
	0x7c,		//B
	0x39,		//C
	0x5e,		//d
	0x79,		//E
	0x71,		//F
	0x00		//0x00为全不亮
};             
uchar code weixuan[] =			//左边第一位为bit0
{ 
	0xfe,		//0
	0xfd,		//1
	0xfb,		//2
	0xf7,		//3
	0xef,		//4
	0xdf		//5
};
/*******************************************全局变量**********************************************/
/********************************************位定义************************/
sbit wx = P2 ^ 7;
sbit dx = P2 ^ 6;
/***********************************************操作**********************************************/
/*******************************************数码管显示1bit******************/
void DigitalTube_Display_1bit(uchar duan, uchar wei)     //段数据，位数据
{
	dx = 1;
	P0 = duanxuan[duan];   //送段数据
	dx = 0;
	P0 = 0xff;		//送位数据前关闭所有显示，防止打开位选锁存后段选数据通过位选锁存器
	wx = 1;
	P0 = weixuan[wei];
	wx = 0;
	DelayMs(1);
}
/*******************************************数码管显示3bit数字******************/
void DigitalTube_Display_num_3bit(uchar shu)
{
	uchar bai, shi, ge;
	bai = shu / 100;
	shi = shu / 10 % 10;
	ge = shu % 10;

	DigitalTube_Display_1bit(bai, 0);
	DigitalTube_Display_1bit(shi, 1);
	DigitalTube_Display_1bit(ge, 2);
}
/*******************************************数码管显示6bit******************/
void DigitalTube_Display_6bit(uchar zero, uchar one, uchar two, uchar three, uchar four, uchar five)
{
	DigitalTube_Display_1bit(zero, 0);
	DigitalTube_Display_1bit(one, 1);
	DigitalTube_Display_1bit(two, 2);
	DigitalTube_Display_1bit(three, 3);
	DigitalTube_Display_1bit(four, 4);
	DigitalTube_Display_1bit(five, 5);
}

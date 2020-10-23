/*
 * 时钟(DS1302)模块
 *
 * AUTHOR			WHAT		DATE
 * Huafeng Lin		created 	2011/10/08
 * Huafeng Lin		modified 	2011/10/08
 *
 */

#include "Clock.h"
#include"Lcd.h"

sbit  IO=P0^5;
sbit  RST=P0^6;
sbit  SCLK=P0^7;

uchar code lookdis[16]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
uchar data display[16]={0x32,0x30,0x32,0x33,0x2e,0x35,0x36,0x2e,0x38,0x39};
uchar data xiaohui[16]={0x32,0x30,0x3a,0x33,0x2e,0x3a,0x36,0x2e};

uchar year,month,week,day,hour,mintue,second;

//***********************************
//写DS1302
//***********************************
void write1302(uchar DS1302_addr, uchar DS1302_data)
{
	uchar i;
	SCLK=0;
	_nop_();
	RST=1;				
	_nop_();
	for(i=0;i<8;i++)						  		//送地址给1302
	{
		SCLK=0;
		_nop_();
		_nop_();
		_nop_();
		if((DS1302_addr&0x01)==0x01)
		   IO=1;
		else
		   IO=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_(); 
		_nop_();
		DS1302_addr=DS1302_addr>>1;
	}
	_nop_();
	_nop_();
	for(i=0;i<8;i++)					   			//送数据给1302
	{
		SCLK=0;
		_nop_();
		_nop_();
		_nop_();
		if((DS1302_data&0x01)==0x01)
			IO=1;
		else
			IO=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_(); 
		_nop_();
		DS1302_data=DS1302_data>>1;
	}
	RST=0;
}

//***********************************
//读DS1302
//***********************************
uchar read1302(uchar DS1302_addr)
{
	uchar receive_data=0;
	uchar i;
	SCLK=0;
	_nop_();
	_nop_();
	RST=1;
	_nop_();									//送地址给1302
	for(i=0;i<8;i++)
	{
		SCLK=0;
		_nop_();
		_nop_();
		_nop_();
		if((DS1302_addr&0x01)==0x01)
			IO=1;
		else
			IO=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_(); 
		_nop_();
		DS1302_addr=DS1302_addr>>1;
	}
	_nop_();
	_nop_();
	for(i=0;i<8;i++)							//从1302读出数据
	{
		SCLK=0;
		_nop_();
			 _nop_();
			 _nop_();
		receive_data=receive_data>>1;
		if(IO==1)
			receive_data=receive_data|0x80;
		else
		receive_data=receive_data&0x7f;
		_nop_();
		_nop_();
			_nop_();
			SCLK=1;
		_nop_();
		_nop_(); 
		_nop_();
	}
	RST=0;
	return(receive_data);
}

void init_clock()
{
	write1302(0x8e,0x00);			 			//允许写1302
	//write1302(0x90,0xa6);			 			//1302充电，充电电流1.1mA
	
	second=read1302(0x81);
	write1302(0x80,second&0x7f);				//启动晶振
/*
	write1302(0x8c,0x9);						//年
	write1302(0x88,0x9);						//月
	write1302(0x86,0x3);						//日
	write1302(0x84,0x22);						//时
	write1302(0x82,0x33);						//分
	//write1302(0x80,0);							//秒
*/
}

void display_clock()
{
	uchar i;

	year=read1302(0x8d);
	display[3]=lookdis[year&0x0f];

	year=year>>4;
	display[2]=lookdis[year&0x0f];
	
	week=read1302(0x8b);
	display[14]=lookdis[week-1];

	month=read1302(0x89);
	display[6]=lookdis[month&0x0f];

	month=month>>4;
	display[5]=lookdis[month&0x0f];
	
	day=read1302(0x87);
	display[9]=lookdis[day&0x0f];

	day=day>>4;
	display[8]=lookdis[day&0x0f];
	
	hour=read1302(0x85);
	xiaohui[1]=lookdis[hour&0x0f];

	hour=hour>>4;
	xiaohui[0]=lookdis[hour&0x0f];
	
	mintue=read1302(0x83);
	xiaohui[4]=lookdis[mintue&0x0f];

	mintue=mintue>>4;
	xiaohui[3]=lookdis[mintue&0x0f];
	
	second=read1302(0x81);
	xiaohui[7]=lookdis[second&0x0f];

	second=second>>4;
	xiaohui[6]=lookdis[second&0x0f];


	for(i=0;i<10;i++)
	{
		DisplayOneChar(i,0,display[i]);
	}

	for(i=0;i<8;i++)
	{
		DisplayOneChar(i,1,xiaohui[i]);	
	}
}

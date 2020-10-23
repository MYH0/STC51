/*
 * 1602液晶显示模块
 *
 * AUTHOR			WHAT		DATE
 * Huafeng Lin		created 	2011/10/08
 * Huafeng Lin		modified 	2011/10/08
 *
 */

#include"Lcd.h"

sbit RS=P0^2;  
sbit RW=P0^1;  
sbit E=P0^0;
  
#define busy  0x80

void delay_LCM(uchar k)	//延时函数   
{   
	uint i,j;
    for(i=0;i<k;i++)
    {
        for(j=0;j<60;j++)
        	{;}
    }
}   

void test_1602busy()//测忙函数  
{  
    P2=0xff;   
    E=1;
	RS=0;
	RW=1;   
    _nop_();
	_nop_();   
  	while(P2&busy)	//检测LCD DB7 是否为1
	{
		E=0;
	   	_nop_();
	   	E=1;
	   	_nop_();
	}
   	E=0;  
}   

void write_1602Command(uchar co)  //写命令函数 
{ 
	test_1602busy();   	//检测LCD是否忙
    RS=0;
	RW=0;
	E=0;   
    _nop_(); 
    P2=co;          
    _nop_();  
    E=1;  				//LCD的使能端高电平有效
    _nop_();  
    E=0;   
}   

void write_1602Data(uchar Data)//写数据函数   
{
	test_1602busy(); 
	P2=Data; 
	RS=1;
	RW=0;
	E=1;   
	_nop_();
	E=0; 
}   

void init_1602(void)//初始化函数  
{   
	write_1602Command(0x38);  //LCD功能设定,DL=1(8位),N=1(2行显示)
	delay_LCM(5); 
	write_1602Command(0x01);  //清除LCD的屏幕
	delay_LCM(5);  
	write_1602Command(0x06);  //LCD模式设定,I/D=1(计数地址加1)
	delay_LCM(5);  
	write_1602Command(0x0F);  //显示屏幕
	delay_LCM(5);
}

void reset_1602(void)
{
	write_1602Command(0x01);
	delay_LCM(5);  
	write_1602Command(0x06);
	delay_LCM(5);  
	write_1602Command(0x0c);
	delay_LCM(5);
} 

void DisplayOneChar(uchar X,uchar Y,uchar DData)
{
    Y&=1;
    X&=15;
    if(Y)X|=0x40;               //若y为1（显示第二行），地址码+0X40
    X|=0x80;                    //指令码为地址码+0X80
    write_1602Command(X);
    write_1602Data(DData);
}

void display_1602(uchar *DData,X,Y)//显示函数  
{   
    uchar ListLength=0;
    Y&=0x01;
    X&=0x0f;
    while(X<16)
    {
        DisplayOneChar(X,Y,DData[ListLength]);
        ListLength++;
        X++;
    } 
}


/*******************说明:**************************
将实时时钟数据通过串口发送
--------------------------------------------------
基于战神单片机工作室51/AVR最小系统板及DS1302
实时时钟模块编写
淘宝店铺地址: http://zsmcu.taobao.com/
QQ:284083167
手机:15016732495
**************************************************/
#include <reg52.h>
#define uchar unsigned char
#define uint  unsigned int
//DS1302引脚定义,可根据实际情况自行修改端口定义
sbit RST=P1^3;
sbit IO=P1^2;
sbit SCK=P1^1;
//DS1302地址定义
#define ds1302_sec_add			0x80		//秒数据地址
#define ds1302_min_add			0x82		//分数据地址
#define ds1302_hr_add			0x84		//时数据地址
#define ds1302_date_add			0x86		//日数据地址
#define ds1302_month_add		0x88		//月数据地址
#define ds1302_day_add			0x8a		//星期数据地址
#define ds1302_year_add			0x8c		//年数据地址
#define ds1302_control_add		0x8e		//控制数据地址
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe
//初始时间定义
uchar time_buf[8] = {0x20,0x10,0x09,0x14,0x23,0x59,0x50,0x02};//初始时间
uchar readtime[14];//当前时间
uchar sec_buf=0;  //秒缓存
uchar sec_flag=0; //秒标志位
//功能:延时1毫秒
//入口参数:x
//出口参数:无
//说明:晶振为12M
void Delay_xms(uint x)
{
  uint i,j;
  for(i=0;i<x;i++)
    for(j=0;j<112;j++);
}
//DS1302初始化函数
void ds1302_init(void) 
{
	RST=0;			//RST脚置低
	SCK=0;			//SCK脚置低
}
//向DS1302写入一字节数据
void ds1302_write_byte(uchar addr, uchar d) 
{
	uchar i;
	RST=1;					//启动DS1302总线	
	//写入目标地址：addr
	addr = addr & 0xFE;   //最低位置零，寄存器0位为0时写，为1时读
	for (i = 0; i < 8; i ++) {
		if (addr & 0x01) {
			IO=1;
			}
		else {
			IO=0;
			}
		SCK=1;      //产生时钟
		SCK=0;
		addr = addr >> 1;
		}	
	//写入数据：d
	for (i = 0; i < 8; i ++) {
		if (d & 0x01) {
			IO=1;
			}
		else {
			IO=0;
			}
		SCK=1;    //产生时钟
		SCK=0;
		d = d >> 1;
		}
	RST=0;		//停止DS1302总线
}

//从DS1302读出一字节数据
uchar ds1302_read_byte(uchar addr) {

	uchar i,temp;	
	RST=1;					//启动DS1302总线
	//写入目标地址：addr
	addr = addr | 0x01;    //最低位置高，寄存器0位为0时写，为1时读
	for (i = 0; i < 8; i ++) {
		if (addr & 0x01) {
			IO=1;
			}
		else {
			IO=0;
			}
		SCK=1;
		SCK=0;
		addr = addr >> 1;
		}	
	//输出数据：temp
	for (i = 0; i < 8; i ++) {
		temp = temp >> 1;
		if (IO) {
			temp |= 0x80;
			}
		else {
			temp &= 0x7F;
			}
		SCK=1;
		SCK=0;
		}	
	RST=0;					//停止DS1302总线
	return temp;
}
//向DS302写入时钟数据
void ds1302_write_time(void) 
{
	ds1302_write_byte(ds1302_control_add,0x00);			//关闭写保护 
	ds1302_write_byte(ds1302_sec_add,0x80);				//暂停时钟 
	//ds1302_write_byte(ds1302_charger_add,0xa9);	    //涓流充电 
	ds1302_write_byte(ds1302_year_add,time_buf[1]);		//年 
	ds1302_write_byte(ds1302_month_add,time_buf[2]);	//月 
	ds1302_write_byte(ds1302_date_add,time_buf[3]);		//日 
	ds1302_write_byte(ds1302_hr_add,time_buf[4]);		//时 
	ds1302_write_byte(ds1302_min_add,time_buf[5]);		//分
	ds1302_write_byte(ds1302_sec_add,time_buf[6]);		//秒
	ds1302_write_byte(ds1302_day_add,time_buf[7]);		//周 
	ds1302_write_byte(ds1302_control_add,0x80);			//打开写保护     
}
//从DS302读出时钟数据
void ds1302_read_time(void)  
{
	time_buf[1]=ds1302_read_byte(ds1302_year_add);		//年 
	time_buf[2]=ds1302_read_byte(ds1302_month_add);		//月 
	time_buf[3]=ds1302_read_byte(ds1302_date_add);		//日 
	time_buf[4]=ds1302_read_byte(ds1302_hr_add);		//时 
	time_buf[5]=ds1302_read_byte(ds1302_min_add);		//分 
	time_buf[6]=(ds1302_read_byte(ds1302_sec_add))&0x7f;//秒，屏蔽秒的第7位，避免超出59
	time_buf[7]=ds1302_read_byte(ds1302_day_add);		//周 	
}
//串口初始化(系统晶振为12MHz)
void Uart_init(uchar Baud_flag)
{
   TMOD = 0x20;       //T1 2
   PCON = 0x00;       //SMOD = 0
   SCON = 0x50;	      //串口1 8
   switch(Baud_flag)
   {   	
    case 0x00:        //2400 11.0592M:0xf4
	  TH1=0xf3;
	  TL1=0xf3;
	break;
	case 0x01:        //4800 11.0592M:0xfa
	  TH1=0xf9;
	  TL1=0xf9;
	break;
    case 0x02:        //9600 11.0592M:0xfd
	  TH1=0xfd;
	  TL1=0xfd;
	break;
    case 0x03:        //19200 11.0592M:0xfe
      TH1=0xfd;
	  TL1=0xfd;
    break;
	default:          //默认为2400
	  TH1=0xf3;
	  TL1=0xf3;
	break;
   }
   TR1 = 1;	          //启动定时器1								
   ES=1;              //开串口中断
   EA=1;              //开总中断       
}
//串口发送
void Send_char(uchar ch)
{
 SBUF=ch; 
 while(!TI);      //等待发送完毕
 TI=0;           //清中断
}
//主函数
void main(void)
{ 
 Delay_xms(50);//等待系统稳定
 ds1302_init(); //DS1302初始化
 Uart_init(0); //波特率初始化为2400
 Delay_xms(10);
 ds1302_write_time(); //写入初始值
 while(1)
  { 
  ds1302_read_time();  //读取时间 
  readtime[0]=(time_buf[0]>>4);   //分离出年千位
  readtime[1]=(time_buf[0]&0x0F); //分离出年百位 
  readtime[2]=(time_buf[1]>>4);   //分离出年十位
  readtime[3]=(time_buf[1]&0x0F); //分离出年个位 

  readtime[4]=(time_buf[2]>>4);   //分离出月十位
  readtime[5]=(time_buf[2]&0x0F); //分离出月个位 

  readtime[6]=(time_buf[3]>>4);   //分离出日十位
  readtime[7]=(time_buf[3]&0x0F); //分离出日个位 

  readtime[8]=(time_buf[4]>>4);   //分离出小时十位
  readtime[9]=(time_buf[4]&0x0F); //分离出小时个位 
  readtime[10]=(time_buf[5]>>4);   //分离出分钟十位
  readtime[11]=(time_buf[5]&0x0F); //分离出分钟个位
  readtime[12]=(time_buf[6]>>4);   //分离出秒钟十位
  readtime[13]=(time_buf[6]&0x0F); //分离出秒钟个位   
  if(readtime[13]!=sec_buf)       
   { 
    EA=0;
    sec_flag=0;    
	sec_buf=readtime[13];	   
    Send_char(readtime[0]+'0');//年
	Send_char(readtime[1]+'0');     
    Send_char(readtime[2]+'0');
	Send_char(readtime[3]+'0');    

	Send_char('-');

    Send_char(readtime[4]+'0');//月
	Send_char(readtime[5]+'0');

	Send_char('-');

    Send_char(readtime[6]+'0');//日
	Send_char(readtime[7]+'0');

	Send_char(' ');

	Send_char(readtime[8]+'0');//时
	Send_char(readtime[9]+'0');

	Send_char(':');

	Send_char(readtime[10]+'0');//分
	Send_char(readtime[11]+'0');

	Send_char(':');

	Send_char(readtime[12]+'0');//秒
	Send_char(readtime[13]+'0');

	SBUF='\n';
    while(!TI);      //等待发送完毕
    TI=0;           //清中断
	EA=1;    	
   }
   Delay_xms(1000);
  }
}

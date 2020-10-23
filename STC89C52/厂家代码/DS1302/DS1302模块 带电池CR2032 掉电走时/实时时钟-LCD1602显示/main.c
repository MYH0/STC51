/*******************说明:**************************
将实时时钟数据通过LCD1602显示
--------------------------------------------------
基于战神单片机工作室51/AVR最小系统板及DS1302
实时时钟模块编写
淘宝店铺地址: http://zsmcu.taobao.com/
QQ:284083167
手机:15016732495
**************************************************/
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
uchar dis_time_buf[16]={0};
//LCD1602引脚定义
//采用8位并行方式,DB0~DB7连接至LCDDATA0~LCDDATA7
sbit RS=P3^5;
//sbit RW=P2^1;
sbit CS=P3^4;
#define LCDDATA P0
//DS1302引脚定义
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
uchar time_buf[8] = {0x20,0x10,0x06,0x01,0x23,0x59,0x55,0x02};//初始时间2010年6月1号23点59分55秒 星期二
//功能:延时1毫秒
//入口参数:x
//出口参数:无
//说明:当晶振为12M时，j<112；当晶振为11.0592M时，j<122
void Delay_xms(uint x)
{
  uint i,j;
  for(i=0;i<x;i++)
    for(j=0;j<112;j++);
}
//功能：12us延时
//STC89C52为1T单片机,即1个时钟/机器周期,速度为AT89C52的12倍
void Delay_xus(uint t)	  		 		
{ 
  for(;t>0;t--)
   {
	 _nop_();
   }
}
//控制LCD写时序
void LCD_en_write(void)       
{
   CS=1;    
    Delay_xus(20);
   CS=0;   
	Delay_xus(20);
}
  
//写指令函数
void Write_Instruction(uchar command)
{
  RS=0;
  //RW=0;
  CS=1;
  LCDDATA=command;
  LCD_en_write();//写入指令数据
}

//写数据函数
void Write_Data(uchar Wdata)
{
  RS=1;
  //RW=0;
  CS=1;
  LCDDATA=Wdata;
  LCD_en_write();//写入数据
}

//字符显示初始地址设置
void LCD_SET_XY(uchar X,uchar Y)
{
  uchar address;
  if(Y==0)
    address=0x80+X;//Y=0,表示在第一行显示，地址基数为0x80
  else 
    address=0xc0+X;//Y非0时，表时在第二行显示，地址基数为0xC0
  Write_Instruction(address);//写指令，设置显示初始地址
}
//在第X行Y列开始显示Wdata所对应的单个字符
void LCD_write_char(uchar X,uchar Y,uchar Wdata)
{
  LCD_SET_XY(X,Y);//写地址
  Write_Data(Wdata);//写入当前字符并显示
}
//清屏函数
void LCD_clear(void)
{
  Write_Instruction(0x01);
  Delay_xms(5);
}
//显示屏初始化函数
void LCD_init(void) 
{	
	Write_Instruction(0x38);				//8bit interface,2line,5*7dots
	Delay_xms(5);
	Write_Instruction(0x38);	
	Delay_xms(5);
	Write_Instruction(0x38);	

	Write_Instruction(0x08);	//关显示，不显光标，光标不闪烁
	Write_Instruction(0x01);	//清屏
	Delay_xms(5);
	
	Write_Instruction(0x04);	//写一字符，整屏显示不移动
	//Write_Instruction(0x05);	//写一字符，整屏右移
	//Write_Instruction(0x06);	//写一字符，整屏显示不移动
	//Write_Instruction(0x07);	//写一字符，整屏左移
	Delay_xms(5);
	
	//Write_Instruction(0x0B);	//关闭显示（不显示字符，只有背光亮）
	Write_Instruction(0x0C);	//开显示，光标、闪烁都关闭
	//Write_Instruction(0x0D);	//开显示，不显示光标，但光标闪烁
	//Write_Instruction(0x0E);	//开显示，显示光标，但光标不闪烁
	//Write_Instruction(0x0F);	//开显示，光标、闪烁均显示
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
void Display(void)
{
   
   LCD_write_char(3,0,dis_time_buf[0]+'0');
   
   LCD_write_char(4,0,dis_time_buf[1]+'0');
   
   LCD_write_char(5,0,dis_time_buf[2]+'0');
   
   LCD_write_char(6,0,dis_time_buf[3]+'0');

   LCD_write_char(7,0,'/');
   
   
   LCD_write_char(8,0,dis_time_buf[4]+'0');
   
   LCD_write_char(9,0,dis_time_buf[5]+'0');

   LCD_write_char(10,0,'/');

   
   LCD_write_char(11,0,dis_time_buf[6]+'0');
   
   LCD_write_char(12,0,dis_time_buf[7]+'0');
   
   
   LCD_write_char(15,0,dis_time_buf[14]+'0');
   //第2行显示  
   
   LCD_write_char(3,1,dis_time_buf[8]+'0');
  
   LCD_write_char(4,1,dis_time_buf[9]+'0');

   LCD_write_char(5,1,':');

  
   LCD_write_char(6,1,dis_time_buf[10]+'0');
   
   LCD_write_char(7,1,dis_time_buf[11]+'0');

   LCD_write_char(8,1,':');

   
   LCD_write_char(9,1,dis_time_buf[12]+'0');
   
   LCD_write_char(10,1,dis_time_buf[13]+'0');
}
//定时器中断函数
void Timer2() interrupt 5	  //定时器2是5号中断
{
 static uchar t;
 TF2=0;
 t++;
 if(t==4)               //间隔200ms(50ms*4)读取一次时间
  {
   t=0;
   ds1302_read_time();  //读取时间 
   dis_time_buf[0]=(time_buf[0]>>4); //年   
   dis_time_buf[1]=(time_buf[0]&0x0f);
   
   dis_time_buf[2]=(time_buf[1]>>4);   
   dis_time_buf[3]=(time_buf[1]&0x0f);
  

   
   
   dis_time_buf[4]=(time_buf[2]>>4); //月  
   dis_time_buf[5]=(time_buf[2]&0x0f);
   

   dis_time_buf[6]=(time_buf[3]>>4); //日   
   dis_time_buf[7]=(time_buf[3]&0x0f);
   
   dis_time_buf[14]=(time_buf[7]&0x07); //星期
   
   //第2行显示  
   dis_time_buf[8]=(time_buf[4]>>4); //时   
   dis_time_buf[9]=(time_buf[4]&0x0f);   

  

   dis_time_buf[10]=(time_buf[5]>>4); //分   
   dis_time_buf[11]=(time_buf[5]&0x0f);   

   dis_time_buf[12]=(time_buf[6]>>4); //秒   
   dis_time_buf[13]=(time_buf[6]&0x0f);
   
  }
}
//定时器2初始化
void Init_timer2(void)
{
 RCAP2H=0x3c;//赋T2初始值0x3cb0，溢出20次为1秒,每次溢出时间为50ms
 RCAP2L=0xb0;
 TR2=1;	     //启动定时器2
 ET2=1;		 //打开定时器2中断
 EA=1;		 //打开总中断
}


//主函数
void main(void)
{ 
 Delay_xms(50);//等待系统稳定
 LCD_init();   //LCD初始化
 LCD_clear();  //清屏   
 ds1302_init();  //DS1302初始化
 Delay_xms(10);
 ds1302_write_time(); //写入初始值
 Init_timer2(); //定时器2初始化 
 while(1)
  {  
   Display();
  }
}

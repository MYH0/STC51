
/*********************************************************************************
* 【编写时间】： 2011.07.07
* 【作    者】： 雁翎电子
* 【版    本】： V1.0
* 【网    站】： http://ylelectronic.taobao.com/ 
* 【Q      Q】： 348439350
* 【声    明】： 此程序仅用于学习与参考，引用请注明版权和作者信息！
* 【函数功能】： DA-AD试验			   			            			    
* 【使用说明】： 单片机：STC89C52 
                 串口波特率：9600
				 串口一共发送4个字节  
				 1 光敏电阻
				 2 热敏电阻
				 3 悬空
				 4 可调0-5V电压（蓝色电位器调节）
				 
**********************************************************************************/
/********************************************************************************************/

#include<reg52.h>    //包含单片机寄存器的头文件
#include <I2C.H>

#define uchar unsigned char
#define  PCF8591 0x90    //PCF8591 地址



// 变量定义
unsigned char AD_CHANNEL;
unsigned long xdata  LedOut[8];
unsigned int  D[32];
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;

unsigned char date;

uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};


  // 函数申明 

void display();
void delay(uchar i);
bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val);
bit ISendByte(unsigned char sla,unsigned char c);
unsigned char IRcvByte(unsigned char sla);
void Initial_com(void);
//******************************************************************/
main()
{  

	Initial_com();
	while(1)
	{

	/********以下AD-DA处理*************/  
	
	    switch(AD_CHANNEL)
		{
			case 0: ISendByte(PCF8591,0x41);
			     D[0]=IRcvByte(PCF8591);  //ADC0 模数转换1      光敏电阻
				 break;  
			
			case 1: ISendByte(PCF8591,0x42);
			     D[1]=IRcvByte(PCF8591);  //ADC1  模数转换2	  热敏电阻
				 break;  
			
			case 2: ISendByte(PCF8591,0x43);
			     D[2]=IRcvByte(PCF8591);  //ADC2	模数转换3	   悬空
				 break;  
			
			case 3: ISendByte(PCF8591,0x40);
			     D[3]=IRcvByte(PCF8591);  //ADC3   模数转换4	   可调0-5v
				 break;  
			
			case 4: DACconversion(PCF8591,0x40, D[4]); //DAC	  数模转换
			     break;
		 
		}

    	D[4]=D[3];  //把模拟输入采样的信号 通过数模转换输出
			
	   if(++AD_CHANNEL>4) AD_CHANNEL=0;
	
	   /********以下将AD的值通过串口发送出去*************/
	 delay(200);	
	 SBUF=D[0];		   	   
	 delay(200);		  
	 SBUF=D[1];			   
	 delay(200);	
	 SBUF=D[2];
	 delay(200);
	 SBUF=D[3];
	 delay(200);
	 if(RI)
	{
		date=SBUF;    //单片机接受
		SBUF=date;    //单片机发送
		RI=0;
	}	 
   }
}


void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

/*******************************************************************
DAC 变换, 转化函数               
*******************************************************************/
bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   Start_I2c();              //启动总线
   SendByte(sla);            //发送器件地址
   if(ack==0)return(0);
   SendByte(c);              //发送控制字节
   if(ack==0)return(0);
   SendByte(Val);            //发送DAC的数值  
   if(ack==0)return(0);
   Stop_I2c();               //结束总线
   return(1);
}

/*******************************************************************
ADC发送字节[命令]数据函数               
*******************************************************************/
bit ISendByte(unsigned char sla,unsigned char c)
{
   Start_I2c();              //启动总线
   SendByte(sla);            //发送器件地址
   if(ack==0)return(0);
   SendByte(c);              //发送数据
   if(ack==0)return(0);
   Stop_I2c();               //结束总线
   return(1);
}

/*******************************************************************
ADC读字节数据函数               
*******************************************************************/
unsigned char IRcvByte(unsigned char sla)
{  unsigned char c;

   Start_I2c();          //启动总线
   SendByte(sla+1);      //发送器件地址
   if(ack==0)return(0);
   c=RcvByte();          //读取数据0

   Ack_I2c(1);           //发送非就答位
   Stop_I2c();           //结束总线
   return(c);
}


//*****串口初始化函数***********

//******************************
void Initial_com(void)
{
 EA=1;        //开总中断
 ES=1;        //允许串口中断
 ET1=1;        //允许定时器T1的中断
 TMOD=0x20;   //定时器T1，在方式2中断产生波特率
 PCON=0x00;   //SMOD=0
 SCON=0x50;   // 方式1 由定时器控制
 TH1=0xfd;    //波特率设置为9600
 TL1=0xfd;
 TR1=1;       //开定时器T1运行控制位

}

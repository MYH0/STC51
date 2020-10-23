#include"reg52.h"
#include"intrins.h"

#define uchar unsigned char	
#define uint  unsigned int	

sbit Buzzer_P = P2 ^ 0;			// 蜂鸣器

uchar TimeBuff[7]={19,10,4,6,18,30,40};   //时间数组，默认2019年10月4日，星期五，18:30:40
// TimeBuff[0] 代表年份，范围00-99
// TimeBuff[1] 代表月份，范围1-12
// TimeBuff[2] 代表日期，范围1-31
// TimeBuff[3] 代表星期，范围1-7，1是星期天，2是星期一
// TimeBuff[4] 代表小时，范围00-23
// TimeBuff[5] 代表分钟，范围00-59
// TimeBuff[6] 代表秒钟，范围00-59

uchar Clock_Hour;				// 闹钟的小时
uchar Clock_Minute;					// 闹钟的分钟
uchar Clock_Swt;				// 闹钟的开关
uchar Buzzer_Flag = 0;				// 蜂鸣器工作标志

uchar Stop_Watch_Count = 0;		// 用于秒表计数，10毫秒加1
uint  Stop_Watch_Second = 0;			// 用于秒表计数，1秒加1

#include"DelayMs.h"
#include"EEPROM.h"
#include"LCD1602.h"
#include"DS1302.h"
#include"keyboard4.h"
#include"timer1.h"

void main()
{
	LcdInit();					// 执行液晶初始化	
	DS1302_Init();					// 时钟芯片的初始化
	LcdShowInit();				// 液晶显示内容的初始化
	TimerInit();					// 定时器初始化
	
	if(DS1302_Read_Byte(0x81)>=128)	// 判断时钟芯片是否正常运行
	{
		DS1302_Write_Time();				// 如果没有，则初始化一个时间
	}
	
	Clock_Hour = EEPROM_Read(0x2000);		// 读取0x2000这个地址的内容，赋值给闹钟的小时变量
	if(Clock_Hour>23)						// 如果读取到的闹钟小时数值不正常，则重新赋值
	{
		Clock_Hour = 12;
	}

	Clock_Minute = EEPROM_Read(0x2001);	// 读取0x2001这个地址的内容，赋值给闹钟的分钟变量
	if(Clock_Minute>59)						// 如果读取到的闹钟分钟数值不正常，则重新赋值
	{
		Clock_Minute = 30;
	}

	Clock_Swt = EEPROM_Read(0x2002);		// 读取0x2002这个地址的内容，赋值给闹钟的开关变量
	if(Clock_Swt>1)							// 如果读取到的闹钟开关数值不正常，则重新赋值
	{
		Clock_Swt = 0;
	}
	
	while(1)
	{
		DS1302_Read_Time();		// 获取当前时钟芯片的时间，存在数组time_buf中
		FlashTime();				// 刷新时间显示
		ClockJudge();					// 闹钟工作的判断

		KeyScanf1();				// 按键扫描(时间的设置)
		KeyScanf2();					// 按键扫描(闹钟的设置)
		KeyScanf3();				// 按键扫描(进入和退出秒表)
									
		DelayMs(100);				// 延时0.1s
	}
}

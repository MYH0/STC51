#include<intrins.h>
//使用UART1
#define FOSC 11059200L      //System frequency
#define BAUD 9600      //UART baudrate

uchar uart_count = 0;
void ISP_AUTO_Init()
{
	SCON = 0x50;            //8-bit variable UART
	TL2 = RCAP2L = (65536 - (FOSC / 32 / BAUD)); //Set auto-reload vaule
	TH2 = RCAP2H = (65536 - (FOSC / 32 / BAUD)) >> 8;
	T2CON = 0x34;           //Timer2 start run
	ES = 1;                 //Enable UART interrupt
	EA = 1;
}

/*****具体使用方法****

void main()
{
	ISP_AUTO_Init();
	while(1)
	{
	  P13 = 0;

	}
}
********************/


/*----------------------------
UART interrupt service routine
----------------------------*/
void Uart_Isr() interrupt 4
{
	if (RI)
	{
		RI = 0;             //Clear receive interrupt flag
		if (SBUF == 0x7f)
		{
			uart_count++;
			if (uart_count > 10)
			{
				uart_count = 0;
				ISP_CONTR = 0x60;
			}
		}
		else
		{
			uart_count = 0;
		}
	}
	if (TI)
	{
		TI = 0;             //Clear transmit interrupt flag
	}
}
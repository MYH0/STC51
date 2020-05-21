#include <STC89C5XRC.H>
#include "STC89_ISP_AUTO.H"
void main()
{
	UART1_init();
	P10 = 0;
}
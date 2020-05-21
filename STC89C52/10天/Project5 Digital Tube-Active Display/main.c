#include<STC89C5xRC.H>
#include"STC89_ISP_AUTO.H"
#include"DelayMs.h"
#include"DISPLAY_1BIT_SMG.H"
#include"Disaplay_digital-tube0.h"
#include"STC89_ISP_AUTO.H"

void main()
{
	UART1_init();
	while (1)
	{		
		Display_smg0(6, 5, 4, 3, 2, 1);
	}
}

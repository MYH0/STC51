#include<reg52.h>
#include<intrins.h>
#include"DelayMs.h"

uchar t0 = 0, t1 = 0;
uchar flag_t0 = 0, flag_t1 = 0;
uchar temp = 0xfe;
uint shu = 432;

#include"Disaplay_digital-tube1.h"
#include"timer0_interrupt_1.h"
#include"timer1_interrupt_3.h"

void main()
{
	P1 = temp;
	EA = 1;
	TMOD = 0X11;
	init_timer0(50000);
	init_timer1(50000);
	TR0 = 1;
	TR1 = 1;

	while (1)
	{
		if (flag_t1 == 0)
			Display_smg1(shu);
		else
			Display_smg_hello();
		
	}
}
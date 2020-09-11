#include<reg52.h>
#include"DelayMs.h"
#include"Disaplay_digital-tube1.h"

uchar n = 1;

#include"timer0_interrupt_1.h"

void main()
{
	int shu = 0;
	init_timer0(50000);
	while (1)
	{
		if (n == 20)
		{
			n = 0;
			shu++;
			if (shu == 1000)
				shu = 0;

		}
		Display_smg1(shu);
	}
}


#include<reg52.h>
#include"DelayMs.h"

uchar num, temp;

#include"Disaplay_digital-tube1.h"
#include"Matrix_Keyboard.h"

void main()
{
	num = 16;

	dx = 1;
	P0 = 0;
	dx = 0;
	P0 = 0xff;
	wx = 1;
	P0 = 0xc0;
	wx = 0;

	while (1)
	{
		display_smg1(matrix_keyboard());
	}
}

//f=11.0592MHz
/******************************************粗略延时***********************************/
void Delay_ms(uint time_ms)
{
	uint i, j;
	for (i = 0; i < time_ms; i++)
		for (j = 0; j < 113; j++);
}
/******************************************较为精准延时********************************/
void Delay_ms_1()
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay_ms_5()
{
	unsigned char i, j;

	i = 9;
	j = 244;
	do
	{
		while (--j);
	} while (--i);
}
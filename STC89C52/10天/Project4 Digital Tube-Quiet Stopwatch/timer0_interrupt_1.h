void timer0() interrupt 1
{
	/*****开始修改定时的时长*****/

	uint time_long0;	
	time_long0 = 50000; 

	/*****结束修改定时的时长*****/

	TH0 = (65536 - time_long0) / 256;
	TL0 = (65536 - time_long0) % 256;

	/*****开始后续操作*****/

	n++;

	/*****结束后续操作*****/
}
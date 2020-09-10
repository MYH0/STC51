#define uint unsigned int
#define uchar unsigned char

/*********************************************************/
// 毫秒级的延时函数，time是要延时的毫秒数
/*********************************************************/
void DelayMs(uint time)
{
	uint i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 113; j++);
}


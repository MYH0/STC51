typedef unsigned int uint;
typedef unsigned char uchar;

/*********************************************************/
// ���뼶����ʱ������time��Ҫ��ʱ�ĺ�����
/*********************************************************/
void delay_ms(uint time)
{
	uint i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 113; j++);
}
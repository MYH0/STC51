/************************************��ʼ��***********************************/
void EX1_Init()
{
	EX1 = 1;
	IT1 = 0;	//�͵�ƽ����
//	IT1 = 1;	//�½��ش���
}
/************************************�жϹ���***********************************/
void EX1_Func()
{
	
}
/************************************�����ж�***********************************/
void EX1_INT() interrupt 2
{
	EX1_Func();
}
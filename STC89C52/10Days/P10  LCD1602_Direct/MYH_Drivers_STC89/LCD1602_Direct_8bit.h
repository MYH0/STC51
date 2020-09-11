/**********************************IO定义*****************************************/
sbit LCD1602_En = P3 ^ 4;
sbit LCD1602_Rs = P3 ^ 5;
/***********************************操作******************************************/
/***********************************通信********************/
/*********************************写入命令*/
void LCD1602_W_Cmd(uchar cmd)
{
	LCD1602_Rs = 0;
	P0 = cmd;
	Delay_ms_2();
	LCD1602_En = 1;
	Delay_ms_2();
	LCD1602_En = 0;
}
/*********************************写入数据*/
void LCD1602_W_Data(uchar dataa)
{
	LCD1602_Rs = 1;
	P0 = dataa;
	Delay_ms_2();
	LCD1602_En = 1;
	Delay_ms_2();
	LCD1602_En = 0;
}
/***********************************行动********************/
/***********************************清屏*/
void LCD1602_Display_Clear()
{
	LCD1602_W_Cmd(0x01);
}
/*********************************光标定位*/
void LCD1602_Locate(uchar row, uchar col)
{
	if(row==0)
		LCD1602_W_Cmd(0x80 + col);
	if (row == 1)
		LCD1602_W_Cmd(0x80 + 0x40 + col);
}
/*********************************显示字符串*/
void LCD1602_Display_Str(uchar row, uchar col, char* str)
{
	LCD1602_Locate(row, col);
	while (*str)
		LCD1602_W_Data(*str++);
}
/*********************************显示数字*/
void LCD1602_Display_Num(uchar row, uchar col, uint num, uchar len)
{
	uchar i = 0;
	uchar temp = 0;	
	LCD1602_Locate(row, col);
	for (i = 0; i < len; i++)
	{
		temp = (num / low_pow(10, len - i - 1)) % 10;
		LCD1602_W_Data(temp + '0');
	}
}
/***********************************初始化*/
void LCD1602_Init()
{
	LCD1602_En = 0;
	LCD1602_W_Cmd(0x38);
	LCD1602_W_Cmd(0x0e);
	LCD1602_W_Cmd(0x06);
	LCD1602_W_Cmd(0x01);
	LCD1602_W_Cmd(0x80 + 0x01);
}

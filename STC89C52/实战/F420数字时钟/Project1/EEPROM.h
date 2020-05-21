sfr ISP_DATA = 0xe2;		// 数据寄存器
sfr ISP_ADDRH = 0xe3;			// 地址寄存器高八位
sfr ISP_ADDRL = 0xe4;		// 地址寄存器低八位
sfr ISP_CMD = 0xe5;			// 命令寄存器
sfr ISP_TRIG = 0xe6;		// 命令触发寄存器
sfr ISP_CONTR = 0xe7;			// 命令寄存器

/*********************************************************/
// 单片机内部EEPROM不使能
/*********************************************************/
void ISP_Disable()
{
	ISP_CONTR = 0;
	ISP_ADDRH = 0;
	ISP_ADDRL = 0;
}

/*********************************************************/
// 从单片机内部EEPROM读一个字节，从0x2000地址开始
/*********************************************************/
uchar EEPROM_Read(uint add)
{
	ISP_DATA = 0x00;
	ISP_CONTR = 0x83;
	ISP_CMD = 0x01;
	ISP_ADDRH = (uchar)(add >> 8);
	ISP_ADDRL = (uchar)(add & 0xff);

	ISP_TRIG = 0x46;	// 对STC89C51系列来说，每次要写入0x46，再写入0xB9,ISP/IAP才会生效
	ISP_TRIG = 0xB9;
	_nop_();
	ISP_Disable();
	return (ISP_DATA);
}

/*********************************************************/
// 往单片机内部EEPROM写一个字节，从0x2000地址开始
/*********************************************************/
void EEPROM_Write(uint add, uchar ch)
{
	ISP_CONTR = 0x83;
	ISP_CMD = 0x02;
	ISP_ADDRH = (uchar)(add >> 8);
	ISP_ADDRL = (uchar)(add & 0xff);
	ISP_DATA = ch;
	ISP_TRIG = 0x46;
	ISP_TRIG = 0xB9;
	_nop_();
	ISP_Disable();
}

/*********************************************************/
// 擦除单片机内部EEPROM的一个扇区
// 写8个扇区中随便一个的地址，以便擦除该扇区，写入前要先擦除
/*********************************************************/
void Sector_Erase(uint add)
{
	ISP_CONTR = 0x83;
	ISP_CMD = 0x03;
	ISP_ADDRH = (uchar)(add >> 8);
	ISP_ADDRL = (uchar)(add & 0xff);
	ISP_TRIG = 0x46;
	ISP_TRIG = 0xB9;
	_nop_();
	ISP_Disable();
}


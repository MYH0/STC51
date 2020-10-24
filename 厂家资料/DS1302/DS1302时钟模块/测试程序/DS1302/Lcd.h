/*
 * 1602Òº¾§ÏÔÊ¾Ä£¿é
 *
 * AUTHOR			WHAT		DATE
 * Huafeng Lin		created 	2011/10/08
 * Huafeng Lin		modified 	2011/10/08
 *
 */

#ifndef LCD_H
#define LCD_H

#include "Common.h"

void delay_LCM(uchar k);
void init_1602(void);
void reset_1602(void);
void display_1602(uchar *DData,X,Y);
void DisplayOneChar(uchar X,uchar Y,uchar DData);

#endif

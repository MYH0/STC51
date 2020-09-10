/***************************************LED********************************************/
sbit LED0 = P1 ^ 0;
sbit LED1 = P1 ^ 1;
sbit LED2 = P1 ^ 2;
sbit LED3 = P1 ^ 3;
sbit LED4 = P1 ^ 4;
sbit LED5 = P1 ^ 5;
sbit LED6 = P1 ^ 6;
sbit LED7 = P1 ^ 7;

#define LED0_On LED0=0
#define LED1_On LED1=0
#define LED2_On LED2=0
#define LED3_On LED3=0
#define LED4_On LED4=0
#define LED5_On LED5=0
#define LED6_On LED6=0
#define LED7_On LED7=0
#define LED_ALL_On P1=0x00

#define LED0_Off LED0=1
#define LED1_Off LED1=1
#define LED2_Off LED2=1
#define LED3_Off LED3=1
#define LED4_Off LED4=1
#define LED5_Off LED5=1
#define LED6_Off LED6=1
#define LED7_Off LED7=1
#define LED_ALL_Off P1=0xff

#define LED0_Toggle P1^=BIT0
#define LED1_Toggle P1^=BIT1
#define LED2_Toggle P1^=BIT2
#define LED3_Toggle P1^=BIT3
#define LED4_Toggle P1^=BIT4
#define LED5_Toggle P1^=BIT5
#define LED6_Toggle P1^=BIT6
#define LED7_Toggle P1^=BIT7
#define LED_ALL_Toggle P1^=BIT8_ALL

/***************************************Beep*******************************************/
sbit Beep = P2 ^ 3;

#define Beep_On Beep=1
#define Beep_Off Beep=0
#define Beep_Toggle P2^=BIT3


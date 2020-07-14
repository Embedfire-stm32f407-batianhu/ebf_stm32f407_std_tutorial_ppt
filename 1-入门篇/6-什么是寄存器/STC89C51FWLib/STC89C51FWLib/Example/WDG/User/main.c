/*
 * 实验现象：LED_0到LED_6逐个点亮，看门狗复位和复位引脚复位时，LED_7变亮
 *           当关闭电源再上电时，LED_7灭
 */

#include "stc89c51.h"


void Delay_ms(uint16 z);

sbit LED_7 = P1^7;


int main(void)
{
    uchar flag = 0, a = 0xfe;
 
    WDG_CntPeriod(WDG_CntPeriod_2275ms);   /* 设置看门狗复位时间 */
	WDG_ResetCounter();  /* 复位计数器，重新计数 */
	WDG_Cmd(ENABLE);     /* 开启看门狗 */

	flag = GET_PowerUp_Flag();  /* 获取电源复位标志 */ 
	LED_7 = flag;  /* 电源复位标志，LED_7等于1（即LED灭）为电源上电复位，否则为看门狗复位或手动复位（即LED亮）*/	 

	while (1)
	{
		Delay_ms(300);
		P1 &= (a <<= 1);  /* P1脚接LED */
		Delay_ms(300);

	//	WDG_ResetCounter();  /* 复位计数器，重新计数,看门狗不会复位 */
	}
}


void Delay_ms(uint16 z)  /* 不准确的延时 */
{
	uint16 x, y;

	for (x=z; x>0; x--)
	{
	    for (y=100; y>0; y--);
	}	
}



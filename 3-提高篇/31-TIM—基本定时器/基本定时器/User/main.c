#include "stm32f10x.h"
#include "./led/bsp_led.h"
#include "./basetime/bsp_basetime.h"

volatile uint32_t time = 0; // ms 计时变量 

void delay(uint32_t count)
{
	for(; count!=0; count--);
}

int main(void)
{
	/* 在程序来到main函数这里的时候，系统时钟已经配置成72M */
	LED_GPIO_Config();
	
	BASIC_TIM_Init();
	
	while(1)
	{
		if( time == 500 )
		{
			      time = 0;
			/* LED1 取反 */      
			LED1_TOGGLE;
		}
	}
}


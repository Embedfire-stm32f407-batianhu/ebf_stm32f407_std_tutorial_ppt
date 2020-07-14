#include "stm32f10x.h"
#include "./led/bsp_led.h"
#include "./basetime/bsp_basetime.h"

volatile uint32_t time = 0; // ms ��ʱ���� 

void delay(uint32_t count)
{
	for(; count!=0; count--);
}

int main(void)
{
	/* �ڳ�������main���������ʱ��ϵͳʱ���Ѿ����ó�72M */
	LED_GPIO_Config();
	
	BASIC_TIM_Init();
	
	while(1)
	{
		if( time == 500 )
		{
			      time = 0;
			/* LED1 ȡ�� */      
			LED1_TOGGLE;
		}
	}
}


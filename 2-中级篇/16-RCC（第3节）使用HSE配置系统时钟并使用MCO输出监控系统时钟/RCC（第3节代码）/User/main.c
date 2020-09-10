/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ƶ����ˮ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include "stm32f4xx.h"
#include "./led/bsp_led.h"

#include "./rcc/bsp_clkconfig.h"

void Delay(__IO u32 nCount); 



/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* �������������ʱ��ϵͳ��ʱ���Ѿ���SystemInit���������ʼ������ */
	//User_SetSysClock();
	
	/* �����Ŀ�������ⲿ������25M�Ļ����޸ĵ�һ���β�M
	������볬Ƶʹ�õĻ����޸ĵڶ����β�N*/
	
	HSE_SetSysClock(25, 336, 2, 7);
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();
	
	MCO1_GPIO_Config();
	MCO2_GPIO_Config();
	
	RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_1);
	RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO2Div_1);

	/* ����LED�� */
	while (1)
	{
		LED1( ON );			 // �� 
		Delay(0x0FFFFF);
		LED1( OFF );		  // ��
		Delay(0x0FFFFF);
	}
}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/


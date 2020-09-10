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
	User_SetSysClock();
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

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


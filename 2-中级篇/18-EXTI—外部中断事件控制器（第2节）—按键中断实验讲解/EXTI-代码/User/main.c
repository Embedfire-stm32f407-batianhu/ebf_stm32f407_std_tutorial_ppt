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
#include "bsp_exti.h"

void Delay(__IO u32 nCount); 



/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* �������������ʱ��ϵͳ��ʱ���Ѿ���SystemInit���������ʼ������ */	
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

	/* ��ʼ��EXTI */
	EXTI_Key_Config();
	while (1)
	{
		/*  */
	}
}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/


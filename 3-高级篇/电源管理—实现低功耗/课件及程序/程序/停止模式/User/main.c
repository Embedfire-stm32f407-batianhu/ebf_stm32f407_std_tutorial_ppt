/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ڽӷ����ԣ����ڽ��յ����ݺ����ϻش���
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
#include "./usart/bsp_debug_usart.h"
#include "./key/bsp_exti.h"
#include "./led/bsp_led.h"   

static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  Debug_USART_Config();
	EXTI_Key_Config();
	LED_GPIO_Config();
	
	/* ����һ���ַ��� */
	printf("����һ��ֹͣģʽʵ��\n");
	LED_GREEN;
	Delay(0xFFFFF);
	
  while(1)
	{	
		printf("\r\n����whileѭ��");
		
		printf("\r\n����ֹͣģʽ");
		
		
		LED_RED;
		
		PWR_FlashPowerDownCmd(ENABLE);
		PWR_EnterSTOPMode(PWR_MainRegulator_ON, PWR_STOPEntry_WFI);
		
		//��������ϵͳʱ��
		SystemInit();
		
		printf("\r\nоƬ�Ѿ�������");
		
		LED_GREEN;
		Delay(0xFFFFF);
		
	}	
}



/*********************************************END OF FILE**********************/


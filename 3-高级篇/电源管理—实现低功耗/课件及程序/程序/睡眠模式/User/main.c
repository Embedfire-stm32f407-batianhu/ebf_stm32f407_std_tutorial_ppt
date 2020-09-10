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
	
	/* ����һ���ַ��� */
	printf("����һ��˯��ģʽʵ��\n");
	
  while(1)
	{	
		printf("\r\n����whileѭ��");
		
		printf("\r\n����˯��ģʽ");
		
		__WFI();
		
		printf("\r\nоƬ�Ѿ�������");
		
	}	
}



/*********************************************END OF FILE**********************/


/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "./led/bsp_led.h"  
#include "./key/bsp_exti.h"





/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	EXTI_Key_Config();
	
	LED_GPIO_Config();
	
	//�ϵ��Ĭ��״̬
	LED2_ON;
	LED1_OFF;

	
	/* ����һ���ַ��� */
	printf("˯��ģʽ��ʾ\n\n\n\n");
	
  while(1)
	{	
		printf("\r\n��ʼwhileѭ��");
				
		printf("\r\n˯��ǰ����Ϣ");
		
		printf("\r\n����˯��״̬");
		
		__WFI();
		
		printf("\r\n���Ѻ����Ϣ");
		
		printf("\r\n������������״̬");

		
	}	
}
/*********************************************END OF FILE**********************/

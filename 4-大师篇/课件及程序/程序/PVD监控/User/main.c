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
#include "./pvd/bsp_pvd.h"




/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	LED_GPIO_Config();
	
	//�ϵ��Ĭ��״̬
	LED2_ON;
	LED1_OFF;
	
	PVD_Config();
	
	/* ����һ���ַ��� */
	printf("��ӭʹ�ñ���STM32������\n\n\n\n");
	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/

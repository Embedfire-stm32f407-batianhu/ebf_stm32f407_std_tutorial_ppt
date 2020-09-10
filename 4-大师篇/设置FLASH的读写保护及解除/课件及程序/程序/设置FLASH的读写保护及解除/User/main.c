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
#include "./rw_protect/bsp_rw_protect.h"  
#include "./key/bsp_key.h" 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  Debug_USART_Config();
	Key_GPIO_Config();
	
	/* ����һ���ַ��� */
	printf("\r\n����һ����д����ʵ��\n");
	
	printf("\r\n����������");
	Read_Protect_Config();
	
//	printf("\r\nд��������");

//	Write_Protect_Config();
	
  while(1)
	{	
		
	}	
}



/*********************************************END OF FILE**********************/


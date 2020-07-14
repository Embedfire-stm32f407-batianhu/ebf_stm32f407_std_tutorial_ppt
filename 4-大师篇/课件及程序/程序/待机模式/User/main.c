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




/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	
	//��������Ҫʹ��PWRʱ�Ӳ�������ʹ��WAUP���Ż���
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	
	LED_GPIO_Config();
	
	//�ϵ��Ĭ��״̬
	LED2_ON;
	LED1_OFF;
	
	
	if(PWR_GetFlagStatus(PWR_FLAG_WU) == SET)
	{
		printf("\r\n �������Ѹ�λ\r\n");
	}
	else{
		printf("\r\n ��  �������Ѹ�λ\r\n");
	}

	
	/* ����һ���ַ��� */
	printf("����ģʽ��ʾ\n\n\n\n");
	
  while(1)
	{	
		printf("\r\n��ʼwhileѭ��");
				
		printf("\r\n����ǰ����Ϣ");
		
		printf("\r\n�������״̬");
		
		PWR_ClearFlag(PWR_FLAG_WU);
		PWR_WakeUpPinCmd(ENABLE);
		
		PWR_EnterSTANDBYMode();
		
		printf("\r\n���Ѻ����Ϣ");
		
		printf("\r\n������������״̬");

		
	}	
}
/*********************************************END OF FILE**********************/

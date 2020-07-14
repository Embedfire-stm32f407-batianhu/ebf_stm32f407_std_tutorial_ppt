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
#include "./sdcard/bsp_spi_sdcard.h"

SD_Error status;
SD_CardInfo info;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	/* ����һ���ַ��� */
	Usart_SendString( DEBUG_USARTx,"����һ�������жϽ��ջ���ʵ��\n");
	printf("��ӭʹ�ñ���STM32������\n\n\n\n");
	
	status = SD_Init();
	
	if( status == SD_RESPONSE_NO_ERROR)
	{
		printf("\r\n��ʼ��SD���ɹ�");
	}
	else
	{
			printf("\r\nʶ�𲻵�SD��");
	}
	
	SD_GetCardInfo(&info);
	printf("cy = %d",info.CardCapacity);
	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/

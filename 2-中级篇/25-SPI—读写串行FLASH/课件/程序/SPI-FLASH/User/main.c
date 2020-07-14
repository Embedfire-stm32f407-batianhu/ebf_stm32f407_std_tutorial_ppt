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
#include "./flash/bsp_spi_flash.h"


uint8_t write_temp[4096]={0};
uint8_t read_temp[4096]={0};

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	uint32_t i=0;
	uint32_t read_id = 0;
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
	USART_Config();
  
	SPI_GPIO_Config();
	
	printf("\r\n��ӭʹ�ñ���STM32������\r\n");

	read_id = SPI_FLASH_Read_JEDEC_ID();
	
	printf("\r\nread_id = %x\r\n",read_id);
	
	SPI_FLASH_Erase_Sector(0);
	
	printf("\r\n�������\r\n");
	
	for(i=0;i<4096;i++)
	{
		write_temp[i] = i+3;
	}
	
	SPI_FLASH_Write_Buff(0,write_temp,4096);
	
	printf("\r\nд�����\r\n");
	
	SPI_FLASH_Read_Buffer(0,read_temp,4096);
	
	printf("\r\n��ȡ��������\r\n");

	for(i=0;i<4096;i++)
	{
		printf("%x ",read_temp[i]);
	}	
	
	for(i=0;i<4096;i++)
	{
		if(write_temp[i] != read_temp[i])
		{
			printf("\r\n��д��һ��\r\n");
			break;
		}			
	}
	
	printf("\r\nУ�����");
	
	 while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/

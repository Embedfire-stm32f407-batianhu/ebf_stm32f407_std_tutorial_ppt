/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��дEEPROM
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
#include "./flash/bsp_spi_flash.h"
#include "./led/bsp_led.h"


uint8_t read_buf[4096]={0};
uint8_t write_buf[4096]={0};

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	
	uint8_t flash_id = 0;
	uint32_t i;
	
  LED_GPIO_Config();
	
	LED_BLUE;
  /*��ʼ��USART1*/
  Debug_USART_Config(); 

	printf("\r\n ��ӭʹ�ñ���  STM32 F407 �����塣\r\n");		 

	printf("\r\n ����һ��FLASH��д�������� \r\n");

	SPI_FLASH_Init();

	flash_id = SPI_FLASH_Read_ID();
	
	printf("\r\n flash id = 0x%x\r\n", flash_id);
	
	printf("\r\n������ʼ");

	//��������
	SPI_FLASH_Erase_Sector(4096*0);
	
		//��������
	SPI_FLASH_Erase_Sector(4096*1);	
	
	printf("\r\n�������");
	
	SPI_FLASH_Read_Buff(0,read_buf,4096);
	
	for(i=0;i<4096;i++)
	{
		//��������0xFF��˵���������ɹ�
		if(read_buf[i] != 0xFF)
		{
			printf("\r\n����У��ʧ��");
		}	
	}
	
	printf("\r\n����У�����");
	
	//��ʼ��Ҫд�������
	for(i=0;i<4096;i++)
	{
		write_buf[i] = 0x55;
	}
	
	printf("\r\n��ʼд��");
	
	SPI_FLASH_Write_Buff(10,write_buf,4096);
	printf("\r\nд�����");

	SPI_FLASH_Read_Buff(10,read_buf,4096);
	
	printf("\r\n��ȡ��������:\r\n");

	for(i=0;i<4096;i++)
	{
		printf("0x%02x ",read_buf[i]);
	}
  
  while (1)
  {      
  }  

}





/*********************************************END OF FILE**********************/


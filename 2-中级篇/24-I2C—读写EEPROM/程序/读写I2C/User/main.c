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
#include "./i2c/bsp_i2c_gpio.h"
#include "./i2c/bsp_i2c_ee.h"

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	uint16_t i;

	uint8_t temp[256] = {0};
	uint8_t w_temp[256] ={0};
	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();	
	
	i2c_GPIO_Config();

	printf("��ӭʹ�ñ���STM32������\n\n\n\n");
	
	if(ee_CHECK_DEVICE(EEPROM_ADDR|EEPROM_WRITE_DIR) == 0)
	{
		printf("\r\n��⵽EEPROM\r\n");
	}
	else
	{
		printf("\r\nû��⵽EEPROM\r\n");
	}
	

	for(i=0;i<256;i++)
	{
		w_temp[i] = i;
	}	
	
	if(ee_WRITE_BYTES(0,w_temp,256) == 1)
	{
		printf("\r\nд������\r\n");
	}
	else
	{
		printf("\r\nд�벻����\r\n");
	}	

	
	if(ee_READ_BYTES(0,temp,256))
	{
		printf("\r\n��ȡ����\r\n");
	}
	else
	{
		printf("\r\n��ȡ������\r\n");
	}
	
	

	for(i=0;i<256;i++)
	{
		printf("\r\ntemp[%d]=%d",i,temp[i]);
	}

	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/

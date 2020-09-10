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
#include "./iic/bsp_i2c_ee.h"

uint8_t test[500*1024];
#define TEST_SIZE   256
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	uint16_t i;
	uint8_t data[TEST_SIZE];
	uint8_t buff[TEST_SIZE];
	
	/*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
	Debug_USART_Config();
	
	/* ����һ���ַ��� */
	printf("����һ��EEPROM��дʵ��\n");
	
	//��buff��ֵ
	for(i=0;i<TEST_SIZE;i++)
	{
		buff[i]=i;
	}
	
	if(test[0])
	{
		printf("\r\nҳ��д����Խ���,��ȡ��������Ϊ:\r\n");

	}

	EEPROM_I2C_Config();
	
	//д�����
	EEPROM_Byte_Write(0x01,0x12);
		
	EEPROM_Random_Read(0x01,data);
	
	printf("\r\n���ֽڶ�д����Խ���,data=0x%x\n",data[0]);
		
//	EEPROM_Page_Write(0x00, buff, TEST_SIZE);	
	//1 , , 9
	//1
	EEPROM_Buffer_Write(0x00, buff, TEST_SIZE);
	
	EEPROM_Buffer_Read(0x00,data, TEST_SIZE);
	
	printf("\r\nҳ��д����Խ���,��ȡ��������Ϊ:\r\n");

	for(i=0;i<TEST_SIZE;i++)
	{
		printf("0x%02x ",data[i]);
	}
	
	while(1)
	{	
		
	}	
}



/*********************************************END OF FILE**********************/


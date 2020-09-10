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
#include "./i2c/bsP_i2c_ee.h"
#include "./led/bsp_led.h"
#include <string.h>

//���������������
//���ֽ�����ʾ���ݵ�����
void show_bytes(uint8_t * data , uint8_t size)
{
	uint8_t i;
	printf("\r\nsize = %d,data in bytes:\r\n",size);
	for(i=0;i<size;i++)
	{
		printf("0x%02x ",*data);
		data++;	
	}
}

uint8_t test_8bit = 0x02;
uint32_t test_32bit = 0x12345678;
float test_float = 1.3;
double test_double = 1.3;

char eng_text[] = "abcdefg";
char cn_text[] = "����";

uint8_t read_buf[30];


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  LED_GPIO_Config();
	
	LED_BLUE;
  /*��ʼ��USART1*/
  Debug_USART_Config(); 

	printf("\r\n ����һ��EEPROM �洢�������ݵ�ʵ�� \r\n");

	/* I2C �����(AT24C02)ʼ�� */
	I2C_EE_Init();
	
	printf("\r\n�ֽ����ݣ�");
	//�ֽ�����
	show_bytes(&test_8bit, sizeof(test_8bit));
	
	printf("\r\n4�ֽ����ݣ�");	
	printf("\r\n����:0x%02x",test_32bit);
	//4�ֽ�����
	show_bytes((uint8_t *)&test_32bit, sizeof(test_32bit));
	
	printf("\r\n���������ݣ�");	
	//����������
	show_bytes((uint8_t *)&test_float, sizeof(test_float));
	
	printf("\r\ndouble���������ݣ�");	
	printf("\r\n����:%f",test_double);
	//double����������
	show_bytes((uint8_t *)&test_double, sizeof(test_double));
		
	printf("\r\nӢ���ַ������ݣ�");		
	//Ӣ���ַ�������,strlen������'\0'
	show_bytes((uint8_t *)eng_text, strlen(eng_text)+1);
	
	printf("\r\n�����ַ������ݣ�");		
	//�����ַ�������
	show_bytes((uint8_t *)cn_text, strlen(cn_text)+1);
	
	printf("\r\n�洢double���ݵ�EEPROM\r\n");
	I2C_EE_BufferWrite((uint8_t *)&test_double,0,sizeof(test_double));
	
	I2C_EE_BufferRead((uint8_t *)read_buf,0,sizeof(test_double));
	
	printf("\r\n��EEPROM��������test_double����:\r\n");
	show_bytes(read_buf,sizeof(test_double));
	
	printf("\r\n����:%f",*(double *)read_buf);
	
	
	printf("\r\n�洢�������ݵ�EEPROM\r\n");
	I2C_EE_BufferWrite((uint8_t *)&test_32bit,0,sizeof(test_32bit));
	
	I2C_EE_BufferRead((uint8_t *)read_buf,0,sizeof(test_32bit));
	
	printf("\r\n��EEPROM��������test_32bit����:\r\n");
	show_bytes(read_buf,sizeof(test_32bit));
	
	printf("\r\n����:0x%02x",*(uint32_t *)read_buf);
	
	
	printf("\r\n�洢Ӣ������\r\n");
	I2C_EE_BufferWrite((uint8_t *)eng_text,0,strlen(eng_text)+1);
	
	I2C_EE_BufferRead((uint8_t *)read_buf,0,strlen(eng_text)+1);
	
	printf("\r\n��EEPROM��������eng_text����:\r\n");
	show_bytes(read_buf,strlen(eng_text)+1);
	
	printf("\r\n����:%s",read_buf);
	
		
  while (1)
  {      
  }  

}




/*********************************************END OF FILE**********************/


/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   读写EEPROM
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./i2c/bsP_i2c_ee.h"
#include "./led/bsp_led.h"
#include <string.h>

//计算机里边万物皆数
//按字节来显示数据的内容
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
char cn_text[] = "中文";

uint8_t read_buf[30];


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
  LED_GPIO_Config();
	
	LED_BLUE;
  /*初始化USART1*/
  Debug_USART_Config(); 

	printf("\r\n 这是一个EEPROM 存储各种数据的实验 \r\n");

	/* I2C 外设初(AT24C02)始化 */
	I2C_EE_Init();
	
	printf("\r\n字节数据：");
	//字节数据
	show_bytes(&test_8bit, sizeof(test_8bit));
	
	printf("\r\n4字节数据：");	
	printf("\r\n数据:0x%02x",test_32bit);
	//4字节数据
	show_bytes((uint8_t *)&test_32bit, sizeof(test_32bit));
	
	printf("\r\n浮点型数据：");	
	//浮点型数据
	show_bytes((uint8_t *)&test_float, sizeof(test_float));
	
	printf("\r\ndouble浮点型数据：");	
	printf("\r\n数据:%f",test_double);
	//double浮点型数据
	show_bytes((uint8_t *)&test_double, sizeof(test_double));
		
	printf("\r\n英文字符串数据：");		
	//英文字符串数据,strlen不包括'\0'
	show_bytes((uint8_t *)eng_text, strlen(eng_text)+1);
	
	printf("\r\n中文字符串数据：");		
	//中文字符串数据
	show_bytes((uint8_t *)cn_text, strlen(cn_text)+1);
	
	printf("\r\n存储double数据到EEPROM\r\n");
	I2C_EE_BufferWrite((uint8_t *)&test_double,0,sizeof(test_double));
	
	I2C_EE_BufferRead((uint8_t *)read_buf,0,sizeof(test_double));
	
	printf("\r\n从EEPROM读回来的test_double数据:\r\n");
	show_bytes(read_buf,sizeof(test_double));
	
	printf("\r\n数据:%f",*(double *)read_buf);
	
	
	printf("\r\n存储整型数据到EEPROM\r\n");
	I2C_EE_BufferWrite((uint8_t *)&test_32bit,0,sizeof(test_32bit));
	
	I2C_EE_BufferRead((uint8_t *)read_buf,0,sizeof(test_32bit));
	
	printf("\r\n从EEPROM读回来的test_32bit数据:\r\n");
	show_bytes(read_buf,sizeof(test_32bit));
	
	printf("\r\n数据:0x%02x",*(uint32_t *)read_buf);
	
	
	printf("\r\n存储英文数据\r\n");
	I2C_EE_BufferWrite((uint8_t *)eng_text,0,strlen(eng_text)+1);
	
	I2C_EE_BufferRead((uint8_t *)read_buf,0,strlen(eng_text)+1);
	
	printf("\r\n从EEPROM读回来的eng_text数据:\r\n");
	show_bytes(read_buf,strlen(eng_text)+1);
	
	printf("\r\n数据:%s",read_buf);
	
		
  while (1)
  {      
  }  

}




/*********************************************END OF FILE**********************/


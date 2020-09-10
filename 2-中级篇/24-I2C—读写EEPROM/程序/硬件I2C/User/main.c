/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   串口接发测试，串口接收到数据后马上回传。
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
#include "./iic/bsp_i2c_ee.h"

uint8_t test[500*1024];
#define TEST_SIZE   256
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	uint16_t i;
	uint8_t data[TEST_SIZE];
	uint8_t buff[TEST_SIZE];
	
	/*初始化USART 配置模式为 115200 8-N-1，中断接收*/
	Debug_USART_Config();
	
	/* 发送一个字符串 */
	printf("这是一个EEPROM读写实验\n");
	
	//给buff赋值
	for(i=0;i<TEST_SIZE;i++)
	{
		buff[i]=i;
	}
	
	if(test[0])
	{
		printf("\r\n页读写入测试结束,读取到的数据为:\r\n");

	}

	EEPROM_I2C_Config();
	
	//写入测试
	EEPROM_Byte_Write(0x01,0x12);
		
	EEPROM_Random_Read(0x01,data);
	
	printf("\r\n单字节读写入测试结束,data=0x%x\n",data[0]);
		
//	EEPROM_Page_Write(0x00, buff, TEST_SIZE);	
	//1 , , 9
	//1
	EEPROM_Buffer_Write(0x00, buff, TEST_SIZE);
	
	EEPROM_Buffer_Read(0x00,data, TEST_SIZE);
	
	printf("\r\n页读写入测试结束,读取到的数据为:\r\n");

	for(i=0;i<TEST_SIZE;i++)
	{
		printf("0x%02x ",data[i]);
	}
	
	while(1)
	{	
		
	}	
}



/*********************************************END OF FILE**********************/


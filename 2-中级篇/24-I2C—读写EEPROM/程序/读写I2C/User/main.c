/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "./i2c/bsp_i2c_gpio.h"
#include "./i2c/bsp_i2c_ee.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	uint16_t i;

	uint8_t temp[256] = {0};
	uint8_t w_temp[256] ={0};
	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();	
	
	i2c_GPIO_Config();

	printf("欢迎使用秉火STM32开发板\n\n\n\n");
	
	if(ee_CHECK_DEVICE(EEPROM_ADDR|EEPROM_WRITE_DIR) == 0)
	{
		printf("\r\n检测到EEPROM\r\n");
	}
	else
	{
		printf("\r\n没检测到EEPROM\r\n");
	}
	

	for(i=0;i<256;i++)
	{
		w_temp[i] = i;
	}	
	
	if(ee_WRITE_BYTES(0,w_temp,256) == 1)
	{
		printf("\r\n写入正常\r\n");
	}
	else
	{
		printf("\r\n写入不正常\r\n");
	}	

	
	if(ee_READ_BYTES(0,temp,256))
	{
		printf("\r\n读取正常\r\n");
	}
	else
	{
		printf("\r\n读取不正常\r\n");
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

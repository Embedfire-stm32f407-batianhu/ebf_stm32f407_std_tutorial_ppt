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
#include "./flash/bsp_spi_flash.h"
#include "./led/bsp_led.h"


uint8_t read_buf[4096]={0};
uint8_t write_buf[4096]={0};

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	
	uint8_t flash_id = 0;
	uint32_t i;
	
  LED_GPIO_Config();
	
	LED_BLUE;
  /*初始化USART1*/
  Debug_USART_Config(); 

	printf("\r\n 欢迎使用秉火  STM32 F407 开发板。\r\n");		 

	printf("\r\n 这是一个FLASH读写测试例程 \r\n");

	SPI_FLASH_Init();

	flash_id = SPI_FLASH_Read_ID();
	
	printf("\r\n flash id = 0x%x\r\n", flash_id);
	
	printf("\r\n擦除开始");

	//擦除测试
	SPI_FLASH_Erase_Sector(4096*0);
	
		//擦除测试
	SPI_FLASH_Erase_Sector(4096*1);	
	
	printf("\r\n擦除完成");
	
	SPI_FLASH_Read_Buff(0,read_buf,4096);
	
	for(i=0;i<4096;i++)
	{
		//若不等于0xFF，说明擦除不成功
		if(read_buf[i] != 0xFF)
		{
			printf("\r\n擦除校验失败");
		}	
	}
	
	printf("\r\n擦除校验完成");
	
	//初始化要写入的数据
	for(i=0;i<4096;i++)
	{
		write_buf[i] = 0x55;
	}
	
	printf("\r\n开始写入");
	
	SPI_FLASH_Write_Buff(10,write_buf,4096);
	printf("\r\n写入完成");

	SPI_FLASH_Read_Buff(10,read_buf,4096);
	
	printf("\r\n读取到的数据:\r\n");

	for(i=0;i<4096;i++)
	{
		printf("0x%02x ",read_buf[i]);
	}
  
  while (1)
  {      
  }  

}





/*********************************************END OF FILE**********************/


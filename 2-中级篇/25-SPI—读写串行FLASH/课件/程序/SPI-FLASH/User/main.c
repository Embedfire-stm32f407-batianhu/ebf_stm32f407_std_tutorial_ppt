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
#include "./flash/bsp_spi_flash.h"


uint8_t write_temp[4096]={0};
uint8_t read_temp[4096]={0};

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	uint32_t i=0;
	uint32_t read_id = 0;
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
	USART_Config();
  
	SPI_GPIO_Config();
	
	printf("\r\n欢迎使用秉火STM32开发板\r\n");

	read_id = SPI_FLASH_Read_JEDEC_ID();
	
	printf("\r\nread_id = %x\r\n",read_id);
	
	SPI_FLASH_Erase_Sector(0);
	
	printf("\r\n擦除完毕\r\n");
	
	for(i=0;i<4096;i++)
	{
		write_temp[i] = i+3;
	}
	
	SPI_FLASH_Write_Buff(0,write_temp,4096);
	
	printf("\r\n写入完毕\r\n");
	
	SPI_FLASH_Read_Buffer(0,read_temp,4096);
	
	printf("\r\n读取到的数据\r\n");

	for(i=0;i<4096;i++)
	{
		printf("%x ",read_temp[i]);
	}	
	
	for(i=0;i<4096;i++)
	{
		if(write_temp[i] != read_temp[i])
		{
			printf("\r\n读写不一致\r\n");
			break;
		}			
	}
	
	printf("\r\n校验结束");
	
	 while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/

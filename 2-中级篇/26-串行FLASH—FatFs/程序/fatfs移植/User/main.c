/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   SPI FLASH基本读写例程
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
#include "./led/bsp_led.h"
#include "./usart/bsp_debug_usart.h"
#include "./flash/bsp_spi_flash.h" 
#include "ff.h"
#include <string.h>
 
FATFS fs;
FRESULT res;
FIL fil;
UINT bw;
UINT br;

#define STR_WRITE  "野火stm32"

char read_buff[100];

/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{ 	
	
	LED_GPIO_Config();
	LED_BLUE;
	
	/* 配置串口1为：115200 8-N-1 */
	Debug_USART_Config();
  
	printf("\r\n这是一个文件系统移植实验 \r\n");
	
	res = f_mount(&fs,"1:",1);
	
	printf("\r\nfmount res=%d",res);
	
	if(res == FR_NO_FILESYSTEM)
	{
		//格式化
		res = f_mkfs("1:",0,0);
		printf("\r\nf_mkfs res=%d",res);
		
		//格式化后需要重新挂载文件系统
		res = f_mount(NULL,"1:",1);
		
		res = f_mount(&fs,"1:",1);		
	}
	
	res = f_open(&fil, "1:mes.txt", FA_CREATE_ALWAYS|FA_READ|FA_WRITE);
	printf("\r\nf_open res=%d",res);
	
	res = f_write(&fil, STR_WRITE, strlen(STR_WRITE) ,&bw);
	printf("\r\nf_write res=%d len=%d bw=%d",res,strlen(STR_WRITE),bw);
	
	res = f_close(&fil);
	printf("\r\nf_close res=%d",res);
	
	
	res = f_open(&fil, "1:abcdefghijklmnopqrstuvwz.txt", FA_CREATE_ALWAYS|FA_READ|FA_WRITE);
	printf("\r\nf_open res=%d",res);
	
	res = f_write(&fil, STR_WRITE, strlen(STR_WRITE) ,&bw);
	printf("\r\nf_write res=%d len=%d bw=%d",res,strlen(STR_WRITE),bw);
	
	res = f_close(&fil);
	printf("\r\nf_close res=%d",res);
	
	
	
	res = f_open(&fil, "1:中文文件名.txt", FA_CREATE_ALWAYS|FA_READ|FA_WRITE);
	printf("\r\nf_open res=%d",res);
	
	res = f_write(&fil, "afdadf中文写入测试", strlen("afdadf中文写入测试") ,&bw);
	printf("\r\nf_write res=%d len=%d bw=%d",res,strlen("afdadf中文写入测试"),bw);
	
	res = f_close(&fil);
	printf("\r\nf_close res=%d",res);
	
	
	res = f_open(&fil, "1:中文文件名.txt", FA_OPEN_EXISTING|FA_READ);
	
	res = f_read(&fil, read_buff, 40, &br);
	printf("\r\nf_read res=%d br=%d",res,br);
	read_buff[br] = '\0';

	printf("\r\n读取到的文件内容:\r\n");
	printf("%s", read_buff);

	res = f_close(&fil);
	
	
	
	
	
	
	res = f_open(&fil, "1:mes.txt", FA_OPEN_EXISTING|FA_READ);
	
	res = f_read(&fil, read_buff, 20, &br);
	printf("\r\nf_read res=%d br=%d",res,br);
	read_buff[br] = '\0';
	printf("\r\n读取到的文件内容:\r\n");
	printf("%s", read_buff);

	res = f_close(&fil);


	
	while(1);  
}


void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/*********************************************END OF FILE**********************/


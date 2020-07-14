 /**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   华邦 8M串行flash测试，并将测试信息通过串口1在电脑的超级终端中打印出来
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
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"
#include "./flash/bsp_spi_flash.h"
#include "ff.h"


FATFS fs;
FRESULT res;
FIL file_p;
char write_buf[] = "这是一个文件系统实验2131313etwateqwtq";
UINT bw;
UINT br;

char read_buf[1024] = {0};

/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{ 	
	
	LED_GPIO_Config();
	
	/* 配置串口为：115200 8-N-1 */
	USART_Config();
	printf("\r\n 这是文件系统移植实验 \r\n");
	
	res = f_mount(&fs,"1:",1);
	
	if(res == FR_NO_FILESYSTEM)
	{
		printf("\r\n before fmkfs ");
		res = f_mkfs("1:",0,0);
		
		if(res != FR_OK)
		{
			printf("\r\n f_mkfs res=%d",res);
		}
	}	
	else if(res ==FR_OK)
	{
		printf("\r\n f_mount res=%d",res);
		
		res = f_open(&file_p,"1:中文长文件名andenglish.txt",FA_READ|FA_WRITE|FA_CREATE_ALWAYS);
		
		printf("\r\n open res=%d",res);

		res = f_write(&file_p,write_buf,sizeof(write_buf),&bw);
		
		printf("\r\n fwrite res=%d",res);
	
		res = f_close(&file_p);
		
		printf("\r\n close res=%d",res);
		
		
		res = f_open(&file_p,"1:中文长文件名andenglish.txt",FA_READ|FA_OPEN_EXISTING);
		
		printf("\r\n r-open res=%d",res);

		res = f_read(&file_p,read_buf,1024,&br);
		printf("\r\n read res=%d,br=%d,sizeof writebuf=%d",res,br,sizeof(write_buf));

		printf("\r\nreadbuf=%s",read_buf);
		
		res = f_close(&file_p);
		
		printf("\r\n close res=%d",res);
		
		
	}
	
	
	
	
	
	while(1);  
}


void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

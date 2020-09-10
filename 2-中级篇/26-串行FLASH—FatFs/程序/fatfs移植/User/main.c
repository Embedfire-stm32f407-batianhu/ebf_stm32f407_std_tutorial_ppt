/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   SPI FLASH������д����
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

#define STR_WRITE  "Ұ��stm32"

char read_buff[100];

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{ 	
	
	LED_GPIO_Config();
	LED_BLUE;
	
	/* ���ô���1Ϊ��115200 8-N-1 */
	Debug_USART_Config();
  
	printf("\r\n����һ���ļ�ϵͳ��ֲʵ�� \r\n");
	
	res = f_mount(&fs,"1:",1);
	
	printf("\r\nfmount res=%d",res);
	
	if(res == FR_NO_FILESYSTEM)
	{
		//��ʽ��
		res = f_mkfs("1:",0,0);
		printf("\r\nf_mkfs res=%d",res);
		
		//��ʽ������Ҫ���¹����ļ�ϵͳ
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
	
	
	
	res = f_open(&fil, "1:�����ļ���.txt", FA_CREATE_ALWAYS|FA_READ|FA_WRITE);
	printf("\r\nf_open res=%d",res);
	
	res = f_write(&fil, "afdadf����д�����", strlen("afdadf����д�����") ,&bw);
	printf("\r\nf_write res=%d len=%d bw=%d",res,strlen("afdadf����д�����"),bw);
	
	res = f_close(&fil);
	printf("\r\nf_close res=%d",res);
	
	
	res = f_open(&fil, "1:�����ļ���.txt", FA_OPEN_EXISTING|FA_READ);
	
	res = f_read(&fil, read_buff, 40, &br);
	printf("\r\nf_read res=%d br=%d",res,br);
	read_buff[br] = '\0';

	printf("\r\n��ȡ�����ļ�����:\r\n");
	printf("%s", read_buff);

	res = f_close(&fil);
	
	
	
	
	
	
	res = f_open(&fil, "1:mes.txt", FA_OPEN_EXISTING|FA_READ);
	
	res = f_read(&fil, read_buff, 20, &br);
	printf("\r\nf_read res=%d br=%d",res,br);
	read_buff[br] = '\0';
	printf("\r\n��ȡ�����ļ�����:\r\n");
	printf("%s", read_buff);

	res = f_close(&fil);


	
	while(1);  
}


void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/*********************************************END OF FILE**********************/


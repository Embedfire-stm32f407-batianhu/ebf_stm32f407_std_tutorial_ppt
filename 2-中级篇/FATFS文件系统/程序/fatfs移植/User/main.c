 /**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ���� 8M����flash���ԣ�����������Ϣͨ������1�ڵ��Եĳ����ն��д�ӡ����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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
char write_buf[] = "����һ���ļ�ϵͳʵ��2131313etwateqwtq";
UINT bw;
UINT br;

char read_buf[1024] = {0};

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{ 	
	
	LED_GPIO_Config();
	
	/* ���ô���Ϊ��115200 8-N-1 */
	USART_Config();
	printf("\r\n �����ļ�ϵͳ��ֲʵ�� \r\n");
	
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
		
		res = f_open(&file_p,"1:���ĳ��ļ���andenglish.txt",FA_READ|FA_WRITE|FA_CREATE_ALWAYS);
		
		printf("\r\n open res=%d",res);

		res = f_write(&file_p,write_buf,sizeof(write_buf),&bw);
		
		printf("\r\n fwrite res=%d",res);
	
		res = f_close(&file_p);
		
		printf("\r\n close res=%d",res);
		
		
		res = f_open(&file_p,"1:���ĳ��ļ���andenglish.txt",FA_READ|FA_OPEN_EXISTING);
		
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

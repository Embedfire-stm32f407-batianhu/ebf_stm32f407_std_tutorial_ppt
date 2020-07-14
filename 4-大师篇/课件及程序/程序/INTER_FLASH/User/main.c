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


#define PAGE_ADDR(n)   (0x08000000 + n*2048)

uint32_t write_buff[10];
uint32_t read_buff[10];

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	uint8_t i;
	uint32_t write_addr=0;
	uint32_t *wrtie_data_p;
	uint32_t *read_p ;
	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	
	/* 发送一个字符串 */
	printf("欢迎使用秉火STM32开发板\n\n\n\n");
	
	//解除内部FLASH的锁
	FLASH_Unlock();
	
	//写入前必须先擦除
	FLASH_ErasePage(PAGE_ADDR(5));
	
	printf("\r\n擦除完成");

	
	for(i=0;i<10;i++)
	{
		write_buff[i] = i;
	}
	
	//写入的基址
	write_addr = PAGE_ADDR(5);
	wrtie_data_p = (uint32_t *)write_buff;
	
	for(i=0;i<10;i++)
	{
		//写入数据
		FLASH_ProgramWord(write_addr,*wrtie_data_p);
		write_addr += 4;	
		wrtie_data_p++;		
	}
	
	printf("\r\n写入完成");
	
	//重新上锁
	FLASH_Lock();
	
	
	//读取数据
	read_p = (uint32_t *)PAGE_ADDR(5);
	
	for(i=0;i<10;i++)
	{
		read_buff[i] = *read_p;
		read_p++;
	}
	
	printf("\r\n读取完成");
	
	for(i=0;i<10;i++)
	{
		printf("\r\nwrite[%d] = %d , read[%d] = %d",i,write_buff[i],i,read_buff[i]);
		if(write_buff[i] != read_buff[i])
		{
			printf("\r\n数据校验不等");
			break;
		}
		
		if(i == 9)
		{
			printf("\r\n写入的数据与读取的数据完全一致");
		}
	}
	
	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/

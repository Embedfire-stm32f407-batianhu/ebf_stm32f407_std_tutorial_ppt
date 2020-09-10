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
#include "./sdio/bsp_sdio_sd.h"
#include "./key/bsp_key.h" 
#include "./led/bsp_led.h"   

extern void SD_Test(void);

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  Debug_USART_Config();
	Key_GPIO_Config();
	LED_GPIO_Config();
	
	printf("\r\n欢迎使用秉火  STM32 F407 开发板。\r\n");	
	
	printf("在开始进行SD卡基本测试前，请给开发板插入32G以内的SD卡\r\n");			
	printf("本程序会对SD卡进行 非文件系统 方式读写，会删除SD卡的文件系统\r\n");		
	printf("实验后可通过电脑格式化或使用SD卡文件系统的例程恢复SD卡文件系统\r\n");		
	printf("\r\n 但sd卡内的原文件不可恢复，实验前务必备份SD卡内的原文件！！！\r\n");		
	
	printf("\r\n 若已确认，请按开发板的KEY1按键，开始SD卡测试实验....\r\n");	
	
	
	while(1)
	{
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON)
		{
				SD_Test();			
		}
	}
}



/*********************************************END OF FILE**********************/


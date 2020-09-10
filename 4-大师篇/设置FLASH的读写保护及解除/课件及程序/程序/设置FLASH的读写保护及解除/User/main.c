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
#include "./rw_protect/bsp_rw_protect.h"  
#include "./key/bsp_key.h" 

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
	
	/* 发送一个字符串 */
	printf("\r\n这是一个读写保护实验\n");
	
	printf("\r\n读保护测试");
	Read_Protect_Config();
	
//	printf("\r\n写保护测试");

//	Write_Protect_Config();
	
  while(1)
	{	
		
	}	
}



/*********************************************END OF FILE**********************/


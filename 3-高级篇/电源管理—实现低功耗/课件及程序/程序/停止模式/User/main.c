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
#include "./key/bsp_exti.h"
#include "./led/bsp_led.h"   

static void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  Debug_USART_Config();
	EXTI_Key_Config();
	LED_GPIO_Config();
	
	/* 发送一个字符串 */
	printf("这是一个停止模式实验\n");
	LED_GREEN;
	Delay(0xFFFFF);
	
  while(1)
	{	
		printf("\r\n进入while循环");
		
		printf("\r\n进入停止模式");
		
		
		LED_RED;
		
		PWR_FlashPowerDownCmd(ENABLE);
		PWR_EnterSTOPMode(PWR_MainRegulator_ON, PWR_STOPEntry_WFI);
		
		//重新配置系统时钟
		SystemInit();
		
		printf("\r\n芯片已经被唤醒");
		
		LED_GREEN;
		Delay(0xFFFFF);
		
	}	
}



/*********************************************END OF FILE**********************/


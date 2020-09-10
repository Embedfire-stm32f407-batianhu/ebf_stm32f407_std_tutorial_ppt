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
//	EXTI_Key_Config();
	LED_GPIO_Config();
	
	/* 发送一个字符串 */
	printf("\r\n这是一个待机模式实验\n");
	LED_GREEN;
	Delay(0xFFFFF);
	
	if(PWR_GetFlagStatus(PWR_FLAG_WU) == RESET)
	{
			printf("\r\n芯片不是从待机状态唤醒的");
	}
	else
	{
			printf("\r\n芯片从待机状态唤醒的");
	}
	
	
  while(1)
	{	
		printf("\r\n进入while循环");
		
		printf("\r\n进入待机模式");
		
		
		LED_RED;
		
		//使能WAUP引脚的功能
		PWR_WakeUpPinCmd(ENABLE);
		
		//清除待机唤醒标志
		PWR_ClearFlag(PWR_FLAG_WU);
		
		PWR_EnterSTANDBYMode();
		
		printf("\r\n芯片已经被唤醒");
		
		LED_BLUE;
		Delay(0xFFFFF);
		
	}	
}



/*********************************************END OF FILE**********************/


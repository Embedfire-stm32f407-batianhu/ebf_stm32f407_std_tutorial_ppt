/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   控制多彩流水灯
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
#include "bsp_systick.h"

void Delay(__IO u32 nCount); 



/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	/* 程序来到这里的时候，系统的时钟已经由SystemInit这个函数初始化好了 */	
	
	/* LED 端口初始化 */
	LED_GPIO_Config();
	
	SysTick_Init();

	/* 控制LED灯 */
	while (1)
	{
		LED1( ON );			 // 亮 
		//Delay_ms(500);
		SysTick_Delay_Ms(300);
		LED1( OFF );		  // 灭
		//Delay_ms(500);
		SysTick_Delay_Ms(300);
	}
}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/


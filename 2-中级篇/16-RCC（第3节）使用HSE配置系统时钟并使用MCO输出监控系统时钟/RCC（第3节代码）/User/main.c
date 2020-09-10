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

#include "./rcc/bsp_clkconfig.h"

void Delay(__IO u32 nCount); 



/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	/* 程序来到这里的时候，系统的时钟已经由SystemInit这个函数初始化好了 */
	//User_SetSysClock();
	
	/* 如果你的开发板的外部晶振不是25M的话，修改第一个形参M
	如果你想超频使用的话，修改第二个形参N*/
	
	HSE_SetSysClock(25, 336, 2, 7);
	
	/* LED 端口初始化 */
	LED_GPIO_Config();
	
	MCO1_GPIO_Config();
	MCO2_GPIO_Config();
	
	RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_1);
	RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO2Div_1);

	/* 控制LED灯 */
	while (1)
	{
		LED1( ON );			 // 亮 
		Delay(0x0FFFFF);
		LED1( OFF );		  // 灭
		Delay(0x0FFFFF);
	}
}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/


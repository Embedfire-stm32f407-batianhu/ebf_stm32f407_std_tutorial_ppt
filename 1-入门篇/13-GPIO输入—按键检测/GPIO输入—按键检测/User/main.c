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

/* 下面这两种头文件的包含方法有什么不同 */
#include "./led/bsp_led.h"
#include "bsp_key.h"


void Delay(__IO u32 nCount); 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	/* LED 端口初始化 */
	LED_GPIO_Config();
	
	KEY_GPIO_Config();

	/* 按键扫描 */
	while (1)
	{
		if( KEY_Scan(GPIOA,GPIO_Pin_0) == KEY_ON  )
		{
			LED1_TOGGLE;
		}
		
		if( KEY_Scan(GPIOC,GPIO_Pin_13) == KEY_ON  )
		{
			LED2_TOGGLE;
		}
	}
}


//  如何提高代码的可移植性
//  就是把跟硬件相关的IO都用宏定义来实现








void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/


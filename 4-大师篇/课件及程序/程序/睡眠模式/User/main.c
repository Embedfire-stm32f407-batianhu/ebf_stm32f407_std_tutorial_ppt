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
#include "./led/bsp_led.h"  
#include "./key/bsp_exti.h"





/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	
	EXTI_Key_Config();
	
	LED_GPIO_Config();
	
	//上电后默认状态
	LED2_ON;
	LED1_OFF;

	
	/* 发送一个字符串 */
	printf("睡眠模式演示\n\n\n\n");
	
  while(1)
	{	
		printf("\r\n开始while循环");
				
		printf("\r\n睡眠前的信息");
		
		printf("\r\n进入睡眠状态");
		
		__WFI();
		
		printf("\r\n唤醒后的信息");
		
		printf("\r\n进入正常运行状态");

		
	}	
}
/*********************************************END OF FILE**********************/

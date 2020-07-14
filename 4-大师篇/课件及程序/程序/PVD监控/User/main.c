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
#include "./pvd/bsp_pvd.h"




/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	
	LED_GPIO_Config();
	
	//上电后默认状态
	LED2_ON;
	LED1_OFF;
	
	PVD_Config();
	
	/* 发送一个字符串 */
	printf("欢迎使用秉火STM32开发板\n\n\n\n");
	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/

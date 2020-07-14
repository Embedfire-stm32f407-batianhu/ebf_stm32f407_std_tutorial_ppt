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



void sysclk_reconfig(void);


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	//刚唤醒的时钟状态
	uint8_t pr_clock_sources = 0;
	RCC_ClocksTypeDef pr_clock_freq;
	
	//重新配置后的时钟状态
	uint8_t clock_sources = 0;
	RCC_ClocksTypeDef clock_freq;
	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	
	EXTI_Key_Config();
	
	LED_GPIO_Config();
	
	//上电后默认状态
	LED2_ON;
	LED2_ON;

	
	/* 发送一个字符串 */
	printf("停止模式演示\n\n\n\n");
		LED2_ON;
		LED1_ON;
		
		
  while(1)
	{	
		

		
		printf("\r\n开始while循环");
				
		printf("\r\n停止前的信息");
		
		printf("\r\n进入停止状态");
		
		PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);
		
		//获取刚唤醒的时钟状态
		pr_clock_sources = RCC_GetSYSCLKSource();		
		RCC_GetClocksFreq(&pr_clock_freq);

		//重新配置系统时钟
		sysclk_reconfig();
		
		
		//获取刚重新配置系统时钟后的状态
		clock_sources = RCC_GetSYSCLKSource();		
		RCC_GetClocksFreq(&clock_freq);
		
		
		
		printf("\r\n刚唤醒的时钟状态");
		printf("\r\npr_clock_sources = 0x%x",pr_clock_sources);
		printf("\r\npr_clock_freq.SYSCLK_Frequency = %d",pr_clock_freq.SYSCLK_Frequency);

		printf("\r\n重新配置系统时钟后的状态");
		printf("\r\nclock_sources = 0x%x",clock_sources);
		printf("\r\nclock_freq.SYSCLK_Frequency = %d",clock_freq.SYSCLK_Frequency);

		
//		LED2_OFF;
//		LED1_OFF;
		
		printf("\r\n唤醒后的信息");
		
		printf("\r\n进入正常运行状态");

		
	}	
}

//重新配置系统时钟
void sysclk_reconfig(void)
{
	RCC_HSEConfig(RCC_HSE_ON);
	
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) != SET);
	
	
	RCC_PLLCmd(ENABLE);
	
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);
	
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
	while(RCC_GetSYSCLKSource() != 0x08);

}

/*********************************************END OF FILE**********************/

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
#include "./sram/bsp_sram.h" 


#define SRAM_BASE_ADDR  0x6C000000
#define INER_SRAM_ADDR  0x20001000

volatile uint8_t testvalue __attribute((at(0x6C000050)));
volatile double testvalue_double __attribute((at(0x6C000080)));

//变量类型 变量名 __attribute((at(指定的变量地址)));
//当地址为外部SRAM空间时
//1.必须为全局变量
//2.变量定义的初始值无效
//3.必须放在FSMC初始化之后才使用

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	//加入volatile防止CPU优化
	volatile uint8_t * p = (uint8_t *)SRAM_BASE_ADDR;
	volatile uint16_t * p_16 = (uint16_t *)(SRAM_BASE_ADDR+10);
	volatile uint32_t * p_32 = (uint32_t *)(SRAM_BASE_ADDR+20);

	//加入volatile防止CPU优化
	volatile uint8_t * p_iner = (uint8_t *)INER_SRAM_ADDR;
	

	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  Debug_USART_Config();
	
	//初始化FSMC
	FSMC_Config();	
	
	testvalue = 0xA;	
	printf("\ntestvalue的内容为:0x%x,其地址为:0x%x",testvalue,&testvalue);
	
	testvalue_double = 0.166;
	printf("\ntestvalue_double的内容为:%f,其地址为:0x%x",testvalue_double,&testvalue_double);


	/* 发送一个字符串 */
	printf("\n这是一个串口中断接收回显实验\n");
	
	//写入操作
	*p = 0xAA;
	
	//读取操作
	printf("\nP写入的内容为:0x%x",*p);
	
		//写入操作
	*p_16 = 0xABCD;
	
	//读取操作
	printf("\nP16写入的内容为:0x%x",*p_16);
	
			//写入操作
	*p_32 = 0x01ABCDEF;
	
	//读取操作
	printf("\nP32写入的内容为:0x%x",*p_32);
	
	
	//写入操作
	*p_iner = 0x77;
	
	//读取操作
	printf("\n写入的内容为:0x%x",*p_iner);
	
	
	
  while(1)
	{	
		
	}	
}



/*********************************************END OF FILE**********************/


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

#if 0

P0 = 0XFE;     // 总线操作

sbit led1 = p0^0   // 位操作
led1 = 0;

GPIOF->ODR |= (0<<6);

GPIOFODR_BITADDR = 0;

#endif



/* 求出位带别名区地址 */
#define BITBAND(addr,bitnum)      ((addr & 0xF0000000)+0x02000000+((addr &0x000FFFFF)<<5)+(bitnum<<2))

/* 对地址进行指针操作 */
#define MEM(addr)     (*(volatile unsigned long*)(addr))
	
#define BIT_ADDR(addr,bitnum)    MEM(BITBAND(addr,bitnum))

#define GPIOF_ODR_ADDR   (GPIOF_BASE+0X14)
#define PFout(n)         BIT_ADDR(GPIOF_ODR_ADDR,n)


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

	/* 控制LED灯 */
	while (1)
	{
		PFout(6) = 0;
		Delay(0xFFFFFF);
		
		PFout(6) = 1;
		Delay(0xFFFFFF);
	}
}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/


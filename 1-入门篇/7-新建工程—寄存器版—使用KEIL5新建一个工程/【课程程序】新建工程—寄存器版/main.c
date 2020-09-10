#include "stm32f4xx.h"

#if 0
#include <reg51.h>

void main(void)
{
	 PA0 = 0XFE;
	 while(1);
}
#endif




int main(void)
{
	
#if 0
	/* 第一步：开启GPIO端口的时钟 */
	/* 打开GPIOF端口的时钟 */
	*( unsigned int *)(0x40023800+0x30) |= ( 1<<5 );
	
	
	/* 第二步：控制GPIO的方向 */
	/* GPIOF 配置为输出 */
	*( unsigned int *)(0x40021400+0x00) &=~ ( (0x03) << (2*6) );
	*( unsigned int *)(0x40021400+0x00) |= ( 1 << (2*6) );
	
	/* 第一步：控制GPIO的数据输出寄存器 */	
	/* PF6 输出高电平 */
	*( unsigned int *)(0x40021400+0x14) |= (1<<6);	
	/* PF6 输出低电平 */
	*( unsigned int *)(0x40021400+0x14) &= ~(1<<6);	
	
#elif 1	
	
	
	/* 第一步：开启GPIO端口的时钟 */
	/* 打开GPIOF端口的时钟 */
	RCC_AHB1ENR |= ( 1<<5 );
	
	
	/* 第二步：控制GPIO的方向 */
	/* GPIOF 配置为输出 */
	GPIOF_MODER &=~ ( (0x03) << (2*6) );
	GPIOF_MODER |= ( 1 << (2*6) );
	
	/* 第一步：控制GPIO的数据输出寄存器 */	
	/* PF6 输出高电平 */
	GPIOF_ODR |= (1<<6);	
	/* PF6 输出低电平 */
	GPIOF_ODR &= ~(1<<6);	

#endif 
}

void SystemInit(void)
{
	/* 函数体为空，目的是为了骗过编译器不报错 */
}

/*
小作业
1- 把其它两个灯也点亮
2- 实现三个灯闪烁（时间的控制使用软件延时）
*/



















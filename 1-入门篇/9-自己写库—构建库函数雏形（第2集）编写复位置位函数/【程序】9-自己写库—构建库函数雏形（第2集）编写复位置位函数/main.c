#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

/* 自己写库—构建库函数雏形 */

/*
 * 注意事项
 * 要在 Options for target 选项里面的 Use MicroLIB这个勾选上
 * 这样才能执行C文件里面的main函数
 */

void delay( unsigned int count )
{
	for( ; count != 0; count-- );
}

int main(void)
{
#if 0 
	/* 第一步：开GPIO端口时钟 */
	RCC_AHB1ENR |= (1<<5);
	
	/* 第二步：配置GPIO为输出 */
	GPIOF_MODER &= ~( 3<<(2*6) );
	GPIOF_MODER |= ( 1<<(2*6) );
	
	/* 第三步：让GPIO输出0或者1，ODR寄存器或者BSRR寄存器 */	
	GPIOF_ODR |= (1<<6);
	
	while(1)
 {
	 GPIOF_ODR &= ~(1<<6);
	 delay(0x0fffff);
	 GPIOF_ODR |= (1<<6);
	 delay(0x0fffff);
 }

#elif 0  /* 定义外设的寄存器结构体 */
 
	/* 第一步：开GPIO端口时钟 */
	RCC_AHB1ENR |= (1<<5);
	
	/* 第二步：配置GPIO为输出 */
	GPIOF->MODER &= ~( 3<<(2*6) );
	GPIOF->MODER |= ( 1<<(2*6) );
	
	/* 第三步：让GPIO输出0或者1，ODR寄存器或者BSRR寄存器 */	
	GPIOF->ODR |= (1<<6);
	
	while(1)
 {
	 GPIOF->ODR &= ~(1<<6);
	 delay(0x0fffff);
	 GPIOF->ODR |= (1<<6);
	 delay(0x0fffff);
 }

#elif 1  /* 编写端口的复位和置位函数 */
 
	/* 第一步：开GPIO端口时钟 */
	RCC_AHB1ENR |= (1<<5);
	
	/* 第二步：配置GPIO为输出 */
	GPIOF->MODER &= ~( 3<<(2*6) );
	GPIOF->MODER |= ( 1<<(2*6) ); 

 
	/* 第三步：让GPIO输出0或者1，ODR寄存器或者BSRR寄存器 */	
	GPIOF->ODR |= (1<<6);
	
	while(1)
 {
	 GPIO_ResetBits(GPIOF,GPIO_Pin_6);
	 delay(0x0fffff);
	 GPIO_SetBits(GPIOF,GPIO_Pin_6);
	 delay(0x0fffff);
 }
 
#endif 
	
}

void SystemInit(void)
{
	/* 函数体为空，目的是为了骗过编译器不报错 */
}





















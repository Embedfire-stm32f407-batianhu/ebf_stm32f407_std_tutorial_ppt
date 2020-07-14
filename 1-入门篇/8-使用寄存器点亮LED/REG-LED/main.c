#include "stm32f10x.h"

//  &= ~ 用来清0
//  |=  用来写1

#define YHMINI 1
#define YHIOT  0

void soft_delay( unsigned int count )
{
	for(; count!=0; count--);
}

int main(void)
{
#if YHMINI
  /* 配置RCC寄存器，使能GPIO口的时钟 */
	*(unsigned int *)0X40021018 |= (1<<4);
	
		/* 配置CRL寄存器，配置为推挽输出 */
	GPIOC_CRL |= ( 1<<(4*2) );
	
	/* 配套ODR寄存器 */
	GPIOC_ODR &= ~( 1<<2 );
	
	while(1)
	{
		GPIOC_ODR &= ~( 1<<2 );
		soft_delay(0xfffff);
		
		GPIOC_ODR |= ( 1<<2 );
		soft_delay(0xfffff);
	}	
	
#elif YHIOT
	
		/* 配置RCC寄存器，使能GPIO口的时钟 */
	*(unsigned int *)0X40021018 |= (1<<3);

	
	/* 配置CRL寄存器，配置为推挽输出 */
	GPIOB_CRL |= ( 1<<(4*0) );
	
	/* 配套ODR寄存器 */
	GPIOB_ODR &= ~( 1<<0 );
	
	while(1)
	{
		GPIOB_ODR &= ~( 1<<0 );
		soft_delay(0xfffff);
		
		GPIOB_ODR |= ( 1<<0 );
		soft_delay(0xfffff);
	}	
#endif
}

void SystemInit(void)
{
	/* 函数体为空，目的是为了骗过编译器不报错 */
}




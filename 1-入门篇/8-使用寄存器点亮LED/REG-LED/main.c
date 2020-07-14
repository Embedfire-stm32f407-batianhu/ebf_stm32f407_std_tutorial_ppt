#include "stm32f10x.h"

//  &= ~ ������0
//  |=  ����д1

#define YHMINI 1
#define YHIOT  0

void soft_delay( unsigned int count )
{
	for(; count!=0; count--);
}

int main(void)
{
#if YHMINI
  /* ����RCC�Ĵ�����ʹ��GPIO�ڵ�ʱ�� */
	*(unsigned int *)0X40021018 |= (1<<4);
	
		/* ����CRL�Ĵ���������Ϊ������� */
	GPIOC_CRL |= ( 1<<(4*2) );
	
	/* ����ODR�Ĵ��� */
	GPIOC_ODR &= ~( 1<<2 );
	
	while(1)
	{
		GPIOC_ODR &= ~( 1<<2 );
		soft_delay(0xfffff);
		
		GPIOC_ODR |= ( 1<<2 );
		soft_delay(0xfffff);
	}	
	
#elif YHIOT
	
		/* ����RCC�Ĵ�����ʹ��GPIO�ڵ�ʱ�� */
	*(unsigned int *)0X40021018 |= (1<<3);

	
	/* ����CRL�Ĵ���������Ϊ������� */
	GPIOB_CRL |= ( 1<<(4*0) );
	
	/* ����ODR�Ĵ��� */
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
	/* ������Ϊ�գ�Ŀ����Ϊ��ƭ�������������� */
}




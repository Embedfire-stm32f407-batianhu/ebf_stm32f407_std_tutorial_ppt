#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

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
  GPIO_InitTypeDef GPIO_InitStruct;
	/* ����RCC�Ĵ�����ʹ��GPIO�ڵ�ʱ�� */
	*(unsigned int *)0X40021018 |= (1<<4);
	
		/* ����CRL�Ĵ���������Ϊ������� */
	//GPIOC->CRL |= ( 1<<(4*2) );
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHZ;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	while(1)
	{
		//GPIOC->ODR &= ~( 1<<2 );
		GPIO_RetsetBits( GPIOC,GPIO_Pin_2);
		soft_delay(0xfffff);
		
		//GPIOC->ODR |= ( 1<<2 );
		GPIO_SetBits( GPIOC,GPIO_Pin_2);
		soft_delay(0xfffff);
	}	
	
#elif YHIOT
	 GPIO_InitTypeDef GPIO_InitStruct;
		/* ����RCC�Ĵ�����ʹ��GPIO�ڵ�ʱ�� */
	*(unsigned int *)0X40021018 |= (1<<3);

	
	/* ����CRL�Ĵ���������Ϊ������� */
	//GPIOB->CRL |= ( 1<<(4*0) );
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHZ;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	while(1)
	{
		//GPIOB->ODR &= ~( 1<<0 );
		GPIO_RetsetBits( GPIOB,GPIO_Pin_0);
		soft_delay(0xfffff);
		
		//GPIOB->ODR |= ( 1<<0 );
		GPIO_SetBits( GPIOB,GPIO_Pin_0);
		soft_delay(0xfffff);
	}	
#endif
}

void SystemInit(void)
{
	/* ������Ϊ�գ�Ŀ����Ϊ��ƭ�������������� */
}




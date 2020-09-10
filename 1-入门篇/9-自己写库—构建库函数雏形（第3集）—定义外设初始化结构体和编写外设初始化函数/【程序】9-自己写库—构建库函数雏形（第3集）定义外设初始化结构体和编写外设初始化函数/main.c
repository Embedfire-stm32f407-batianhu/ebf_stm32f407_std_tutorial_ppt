#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

/* �Լ�д�⡪�����⺯������ */

/*
 * ע������
 * Ҫ�� Options for target ѡ������� Use MicroLIB�����ѡ��
 * ��������ִ��C�ļ������main����
 */

void delay( unsigned int count )
{
	for( ; count != 0; count-- );
}

int main(void)
{
#if 0 
	/* ��һ������GPIO�˿�ʱ�� */
	RCC_AHB1ENR |= (1<<5);
	
	/* �ڶ���������GPIOΪ��� */
	GPIOF_MODER &= ~( 3<<(2*6) );
	GPIOF_MODER |= ( 1<<(2*6) );
	
	/* ����������GPIO���0����1��ODR�Ĵ�������BSRR�Ĵ��� */	
	GPIOF_ODR |= (1<<6);
	
	while(1)
 {
	 GPIOF_ODR &= ~(1<<6);
	 delay(0x0fffff);
	 GPIOF_ODR |= (1<<6);
	 delay(0x0fffff);
 }

#elif 0  /* ��������ļĴ����ṹ�� */
 
	/* ��һ������GPIO�˿�ʱ�� */
	RCC_AHB1ENR |= (1<<5);
	
	/* �ڶ���������GPIOΪ��� */
	GPIOF->MODER &= ~( 3<<(2*6) );
	GPIOF->MODER |= ( 1<<(2*6) );
	
	/* ����������GPIO���0����1��ODR�Ĵ�������BSRR�Ĵ��� */	
	GPIOF->ODR |= (1<<6);
	
	while(1)
 {
	 GPIOF->ODR &= ~(1<<6);
	 delay(0x0fffff);
	 GPIOF->ODR |= (1<<6);
	 delay(0x0fffff);
 }


#elif 0  /* ��������ĳ�ʼ���ṹ��ͱ�д����ĳ�ʼ������ */
 
	/* ��һ������GPIO�˿�ʱ�� */
	RCC_AHB1ENR |= (1<<5);
	
	/* �ڶ���������GPIOΪ��� */
	GPIOF->MODER &= ~( 3<<(2*6) );
	GPIOF->MODER |= ( 1<<(2*6) );
	
	/* ����������GPIO���0����1��ODR�Ĵ�������BSRR�Ĵ��� */	
	GPIOF->ODR |= (1<<6);
	
	while(1)
 {
	 GPIO_ResetBits(GPIOF,GPIO_Pin_6);
	 delay(0x0fffff);
	 GPIO_SetBits(GPIOF,GPIO_Pin_6);
	 delay(0x0fffff);
 }  

#elif 1  /* ��д�˿ڵĸ�λ����λ���� */
 
	/* ��һ������GPIO�˿�ʱ�� */
	RCC_AHB1ENR |= (1<<5);
	
//	/* �ڶ���������GPIOΪ��� */
//	GPIOF->MODER &= ~( 3<<(2*6) );
//	GPIOF->MODER |= ( 1<<(2*6) );
 
// c89 ���﷨��ʽ�����Ǳ��������ڽ���������
// c99 
//{
	GPIO_InitTypeDef  GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOF, &GPIO_InitStruct);
 
//}
 
	/* ����������GPIO���0����1��ODR�Ĵ�������BSRR�Ĵ��� */	
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
	/* ������Ϊ�գ�Ŀ����Ϊ��ƭ�������������� */
}





















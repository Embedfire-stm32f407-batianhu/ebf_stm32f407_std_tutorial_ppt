#include "stm32f10x.h"

#define YHMINI 0
#define YHIOT  1

void soft_delay(unsigned int count)
{
	for( ;count!=0;count-- );
}

int main( void )
{
#if YHMINI
		// �� GPIOB �˿ڵ�ʱ��
	*( unsigned int * )0x40021018 |=  ( (1) << 4 );
	
	// ����IO��Ϊ���
	*( unsigned int * )0x40011000 |=  ( (1) << (4*2) );
	
	// ���� ODR �Ĵ���
	*( unsigned int * )0x4001100C &= ~(1<<2);	
	
	while(1)
	{
		/* �� */	
		*( unsigned int * )0x4001100C &= ~(1<<2);
		soft_delay(0xfffff);
		
		/* �� */	
		*( unsigned int * )0x4001100C |= (1<<2);
		soft_delay(0xfffff);
	}

#elif YHIOT
			// �� GPIOB �˿ڵ�ʱ��
	*( unsigned int * )0x40021018 |=  ( (1) << 3 );
	
	// ����IO��Ϊ���
	*( unsigned int * )0x40010C00 |=  ( (1) << (4*0) );
	
	// ���� ODR �Ĵ���
	*( unsigned int * )0x40010C0C &= ~(1<<0);
	
	while(1)
	{
		/* �� */	
		*( unsigned int * )0x40010C0C &= ~(1<<0);
		soft_delay(0xfffff);
		
		/* �� */	
		*( unsigned int * )0x40010C0C |= (1<<0);
		soft_delay(0xfffff);
	}	
#endif
}



void SystemInit(void)
{
	/* ������Ϊ�գ�Ϊ����ƭ�������������� */
}

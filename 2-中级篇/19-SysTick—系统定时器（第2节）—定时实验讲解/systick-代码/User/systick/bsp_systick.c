#include "bsp_systick.h"

__IO u32 TimingDelay;

void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
}

/**
  * @brief   ms��ʱ����
  * @param  
  *		@arg 
  * @retval  ��
  */
void Delay_ms(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	while(TimingDelay != 0);
}


void SysTick_Delay_Ms( __IO uint32_t ms)
{
	uint32_t i;	
	SysTick_Config(SystemCoreClock/1000);
	
	for(i=0;i<ms;i++)
	{
		// ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1
		// ����1ʱ����ȡ��λ����0
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	// �ر�SysTick��ʱ��
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}





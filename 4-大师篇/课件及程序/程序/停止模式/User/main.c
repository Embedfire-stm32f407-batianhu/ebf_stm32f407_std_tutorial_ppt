/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "./led/bsp_led.h"  
#include "./key/bsp_exti.h"



void sysclk_reconfig(void);


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	//�ջ��ѵ�ʱ��״̬
	uint8_t pr_clock_sources = 0;
	RCC_ClocksTypeDef pr_clock_freq;
	
	//�������ú��ʱ��״̬
	uint8_t clock_sources = 0;
	RCC_ClocksTypeDef clock_freq;
	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	EXTI_Key_Config();
	
	LED_GPIO_Config();
	
	//�ϵ��Ĭ��״̬
	LED2_ON;
	LED2_ON;

	
	/* ����һ���ַ��� */
	printf("ֹͣģʽ��ʾ\n\n\n\n");
		LED2_ON;
		LED1_ON;
		
		
  while(1)
	{	
		

		
		printf("\r\n��ʼwhileѭ��");
				
		printf("\r\nֹͣǰ����Ϣ");
		
		printf("\r\n����ֹͣ״̬");
		
		PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);
		
		//��ȡ�ջ��ѵ�ʱ��״̬
		pr_clock_sources = RCC_GetSYSCLKSource();		
		RCC_GetClocksFreq(&pr_clock_freq);

		//��������ϵͳʱ��
		sysclk_reconfig();
		
		
		//��ȡ����������ϵͳʱ�Ӻ��״̬
		clock_sources = RCC_GetSYSCLKSource();		
		RCC_GetClocksFreq(&clock_freq);
		
		
		
		printf("\r\n�ջ��ѵ�ʱ��״̬");
		printf("\r\npr_clock_sources = 0x%x",pr_clock_sources);
		printf("\r\npr_clock_freq.SYSCLK_Frequency = %d",pr_clock_freq.SYSCLK_Frequency);

		printf("\r\n��������ϵͳʱ�Ӻ��״̬");
		printf("\r\nclock_sources = 0x%x",clock_sources);
		printf("\r\nclock_freq.SYSCLK_Frequency = %d",clock_freq.SYSCLK_Frequency);

		
//		LED2_OFF;
//		LED1_OFF;
		
		printf("\r\n���Ѻ����Ϣ");
		
		printf("\r\n������������״̬");

		
	}	
}

//��������ϵͳʱ��
void sysclk_reconfig(void)
{
	RCC_HSEConfig(RCC_HSE_ON);
	
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) != SET);
	
	
	RCC_PLLCmd(ENABLE);
	
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);
	
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
	while(RCC_GetSYSCLKSource() != 0x08);

}

/*********************************************END OF FILE**********************/

/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ƶ����ˮ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include "stm32f4xx.h"

/* ����������ͷ�ļ��İ���������ʲô��ͬ */
#include "./led/bsp_led.h"
#include "bsp_key.h"


void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();
	
	KEY_GPIO_Config();

	/* ����ɨ�� */
	while (1)
	{
		if( KEY_Scan(GPIOA,GPIO_Pin_0) == KEY_ON  )
		{
			LED1_TOGGLE;
		}
		
		if( KEY_Scan(GPIOC,GPIO_Pin_13) == KEY_ON  )
		{
			LED2_TOGGLE;
		}
	}
}


//  �����ߴ���Ŀ���ֲ��
//  ���ǰѸ�Ӳ����ص�IO���ú궨����ʵ��








void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/


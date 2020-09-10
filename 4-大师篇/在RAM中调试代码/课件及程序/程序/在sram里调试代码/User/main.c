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
#include "./led/bsp_led.h"

void Delay(__IO u32 nCount); 


//char * p = 0x20000000;
//*p = 0x12;

//char * p2 = 0x8000000;

//*p2 = 0x32;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();
	
	LED_RED;

	/* ����LED�� */
	while (1)
	{
//		LED1( ON );			 // �� 
//		Delay(0xFFFFFF);
//		LED1( OFF );		  // ��

//		LED2( ON );			// �� 
//		Delay(0xFFFFFF);
//		LED2( OFF );		  // ��

//		LED3( ON );			 // �� 
//		Delay(0xFFFFFF);
//		LED3( OFF );		  // ��	

//		/*������ʾ ������������� ��ɫ*/
//		LED_RED;
//		Delay(0xFFFFFF);
//		
//		LED_GREEN;
//		Delay(0xFFFFFF);
//		
//		LED_BLUE;
//		Delay(0xFFFFFF);
//		
//		LED_YELLOW;
//		Delay(0xFFFFFF);
//		
//		LED_PURPLE;
//		Delay(0xFFFFFF);
//				
//		LED_CYAN;
//		Delay(0xFFFFFF);
//		
//		LED_WHITE;
//		Delay(0xFFFFFF);
//		
//		LED_RGBOFF;
//		Delay(0xFFFFFF);
	}
}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/


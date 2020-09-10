/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   SRAMӦ������
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
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h" 
#include "./lcd/bsp_ili9806_lcd.h"	  
    

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{ 	
	LED_GPIO_Config();
	LED_BLUE;
	
	/* ���ô���1Ϊ��115200 8-N-1 */
	Debug_USART_Config();  
	
	LCD_Init();
	
	printf ( "\r\nҰ��lcd����\r\n" );	
	
	printf("\r\ndata = 0x%x cmd= 0x%x",LCD_DATA_ADDR,LCD_DATA_CMD);
	
	printf("\r\nlcd id = 0x%x",LCD_Get_ID());
	
	LCD_Draw_Rect(0,480,0,854,BLACK);
	
	LCD_Draw_Rect(10,10,50,150,RED);
  
	while(1)
	{

	}
}



void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/*********************************************END OF FILE**********************/


/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   SRAM应用例程
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h" 
#include "./lcd/bsp_ili9806_lcd.h"	  
    

/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{ 	
	LED_GPIO_Config();
	LED_BLUE;
	
	/* 配置串口1为：115200 8-N-1 */
	Debug_USART_Config();  
	
	LCD_Init();
	
	printf ( "\r\n野火lcd测试\r\n" );	
	
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


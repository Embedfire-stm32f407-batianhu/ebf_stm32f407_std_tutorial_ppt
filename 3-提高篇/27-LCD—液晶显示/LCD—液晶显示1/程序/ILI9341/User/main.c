 /**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   华邦 8M串行flash测试，并将测试信息通过串口1在电脑的超级终端中打印出来
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"
#include "./lcd/bsp_ili9341_lcd.h"


// 函数原型声明
void Delay(__IO uint32_t nCount);

/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无
 */
int main(void)
{ 	
	LED_GPIO_Config();
	
	/* 配置串口为：115200 8-N-1 */
	USART_Config();
	printf("\r\n 这是一个LCD实验 \r\n");
	
	ILI9341_Init();
	
	
	printf("\r\n读取到的ID =%x",ILI9341_Read_ID());
	
//	ILI9341_Open_Window(0,0,240,320);
	
	ILI9341_Draw_Point(10,10,RED);
	
	ILI9341_Draw_Rect(0,100,100,100,RED);

	while(1);  
}

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

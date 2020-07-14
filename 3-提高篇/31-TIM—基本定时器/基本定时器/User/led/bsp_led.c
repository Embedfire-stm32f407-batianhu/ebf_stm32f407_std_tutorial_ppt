
// bsp  board support package 板级支持包

#include "./led/bsp_led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitTStruct;
	/* 第一步：打开外设的时钟 */
	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK|LED2_GPIO_CLK, ENABLE);
	
	/* 第二步：配置外设初始化结构体 */
	GPIO_InitTStruct.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_InitTStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitTStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	/* 第三步：调用外设初始化函数，把配置好的结构体成员写到寄存器里面 */
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitTStruct);
	GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
	
	GPIO_InitTStruct.GPIO_Pin = LED2_GPIO_PIN;
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitTStruct);
	GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
}


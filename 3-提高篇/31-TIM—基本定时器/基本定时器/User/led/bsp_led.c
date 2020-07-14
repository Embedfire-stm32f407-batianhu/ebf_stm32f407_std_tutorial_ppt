
// bsp  board support package �弶֧�ְ�

#include "./led/bsp_led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitTStruct;
	/* ��һ�����������ʱ�� */
	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK|LED2_GPIO_CLK, ENABLE);
	
	/* �ڶ��������������ʼ���ṹ�� */
	GPIO_InitTStruct.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_InitTStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitTStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	/* �����������������ʼ�������������úõĽṹ���Աд���Ĵ������� */
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitTStruct);
	GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
	
	GPIO_InitTStruct.GPIO_Pin = LED2_GPIO_PIN;
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitTStruct);
	GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
}


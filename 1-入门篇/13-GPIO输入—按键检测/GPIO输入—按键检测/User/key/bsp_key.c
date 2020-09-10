#include "bsp_key.h"


void KEY_GPIO_Config(void)
{	
	/* ��һ������GPIO��ʱ�� */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);
	
	/* �ڶ���������һ��GPIO��ʼ���ṹ�� */
	GPIO_InitTypeDef GPIO_InitStruct;
	
  /* ������������GPIO��ʼ���ṹ��ĳ�Ա */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;	
	//GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;		
	/* ���Ĳ�������GPIO��ʼ�������������úõĽṹ��ĳ�Ա�Ĳ���д��Ĵ��� */
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	/* ������������GPIO��ʼ���ṹ��ĳ�Ա */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;	
	//GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;		
	/* ���Ĳ�������GPIO��ʼ�������������úõĽṹ��ĳ�Ա�Ĳ���д��Ĵ��� */
	GPIO_Init(GPIOC, &GPIO_InitStruct);	
	
}


uint8_t KEY_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	if( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)== KEY_ON )
	{
		while( GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)== KEY_ON );
			return KEY_ON;
	}
	else return KEY_OFF;
		
}



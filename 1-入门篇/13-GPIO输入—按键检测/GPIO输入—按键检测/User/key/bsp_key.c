#include "bsp_key.h"


void KEY_GPIO_Config(void)
{	
	/* 第一步：开GPIO的时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);
	
	/* 第二步：定义一个GPIO初始化结构体 */
	GPIO_InitTypeDef GPIO_InitStruct;
	
  /* 第三步：配置GPIO初始化结构体的成员 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;	
	//GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;		
	/* 第四步：调用GPIO初始化函数，把配置好的结构体的成员的参数写入寄存器 */
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	/* 第三步：配置GPIO初始化结构体的成员 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;	
	//GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;		
	/* 第四步：调用GPIO初始化函数，把配置好的结构体的成员的参数写入寄存器 */
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



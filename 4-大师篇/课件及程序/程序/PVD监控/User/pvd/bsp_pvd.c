/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   重定向c库printf函数到usart端口
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火STM32 F103-MINI 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "./pvd/bsp_pvd.h"

 
 /**
  * @brief  PVD  配置,工作参数配置
  * @param  无
  * @retval 无
  */
void PVD_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	//使能时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
  //配置优先级
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn; //配置PVD中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
	
	//配置中断源
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;	
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升沿下降沿都产生中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

	
	//配置为等级5，下降沿2.58V产生中断
	PWR_PVDLevelConfig(PWR_PVDLevel_2V7);
	PWR_PVDCmd(ENABLE);
}

